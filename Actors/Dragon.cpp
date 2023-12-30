//Copyright � 2023 Pluz21(TVL).All rights reserved.
#include "Dragon.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DragonCanvas/Components/MoveComponent.h"
#include "ProjectileManager.h"
#include "DragonCanvas/World/CustomGameMode.h"

#include "Projectile.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DragonCanvas/Components/Grabber.h"
#include "DragonCanvas/Components/HealthComponent.h"
#include "DragonCanvas/Components/ManaComponent.h"
#include "DragonCanvas/Components/AttackComponent.h"

#include "DragonCanvas/UI/MainMenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ADragon::ADragon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Dragon Constructor!"));

	spawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	springArm = CreateDefaultSubobject<USpringArmComponent>("Springarm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	attackCompo = CreateDefaultSubobject<UAttackComponent>("attackCompo");
	grabber = CreateDefaultSubobject<UGrabber>("Grabber");
	physicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");
	healthCompo = CreateDefaultSubobject<UHealthComponent>("healthCompo");
	manaCompo = CreateDefaultSubobject<UManaComponent>("manaCompo");

	projectileSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Sounds/Player_Sounds/Shoot_Sound_Meta.Shoot_Sound_Meta")).Object;
	spawnPoint->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	springArm->SetupAttachment(RootComponent);

	AddOwnedComponent(grabber);
	AddOwnedComponent(physicsHandle);
	AddOwnedComponent(healthCompo);
	AddOwnedComponent(manaCompo);
	

}



// Called every frame
void ADragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called when the game starts or when spawned
void ADragon::BeginPlay()
{
	Super::BeginPlay();
	//onProjectileReachedTarget.AddDynamic(this, &ADragon::LineTraceDisplacement);
	Init();
	
}

void ADragon::Init()
{

	gameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>(); // Grab game mode
	if (!gameMode)return;
	projectileManager = gameMode->GetProjectileManager();
	if (!projectileManager)return;
	onCurrentProjectileMatReceived.AddDynamic(this, &ADragon::TestMatReceived);
	//onCurrentProjectileMatReceived.AddDynamic(this, &ADragon::ScrollDownSelectProjectile);
	
	world = GetWorld();
	playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController)return;

	InitInput();
	InitEvents();

	currentAmmo = maxAmmo;
	UpdateMinDistanceToSelfDestruct();

}

void ADragon::InitInput()
{
	ULocalPlayer* _myPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!_myPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _myPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_inputSystem)return;
	_inputSystem->AddMappingContext(mappingContext, 0);
	//UE_LOG(LogTemp, Warning, TEXT("Init inputs"));
	//playerController->bShowMouseCursor = true;

}

void ADragon::InitEvents()
{
	onLineTraceCreated.AddDynamic(this, &ADragon::FireBreath);

	projectileManager->GetOnMatAcquired().AddDynamic(this, &ADragon::UpdateCurrentProjectileMat);
	projectileManager->GetOnMatAlreadyExists().AddDynamic(this, &ADragon::UpdateCurrentProjectileMat);
	onProjectileShot.AddDynamic(this, &ADragon::PlayProjectileSound);
	
}

void ADragon::UpdateCurrentProjectileMat(UMaterialInterface* _mat)
{


	//allProjectileMats.Add(_mat);
	if (projectileManager->MatExists(_mat, allProjectileMats))return;
	allProjectileMats.EmplaceAt(0, _mat);
	currentProjectileMat = allProjectileMats[currentProjectileIndex];
	//onCurrentProjectileMatReceived.Broadcast(_mat);

}

void ADragon::Move(const FInputActionValue& _value)
{
	if (!canUseMoveInputs)return;

	if (!inputToMove)return;
	float _delta = GetWorld()->DeltaTimeSeconds;
	const FVector _fwd = GetActorForwardVector();
	const FVector2D _movementValue = _value.Get<FVector2D>(); //* _delta * moveSpeed
	const float _forwardMovementValue = _movementValue.X * _delta * moveSpeed;
	forwardInputValue = _movementValue.X;
	AddMovementInput(_fwd, _forwardMovementValue);

	const FVector _rght = GetActorRightVector();
	rightInputValue = _movementValue.Y;
	const float _rightMovementValue = _movementValue.Y * _delta * moveSpeed;
	AddMovementInput(_rght, _rightMovementValue);
}

void ADragon::RotateYaw(const FInputActionValue& _value)
{
	if (!canUseMoveInputs)return;

	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _rotateValue = _value.Get<float>() * _delta * rotateSpeed;
	rotateInputValue = _rotateValue;
	AddControllerYawInput(_rotateValue);
}

void ADragon::RotatePitch(const FInputActionValue& _value)
{
	
	if (!canUseMoveInputs)return;

	float _delta = GetWorld()->DeltaTimeSeconds;
	const float _rotateValue = _value.Get<float>() * _delta * rotateSpeed;
	rotateInputValue = _rotateValue;
	FRotator _currentRotation = springArm->GetComponentRotation();
	float _newPitch = FMath::Clamp(_currentRotation.Pitch + _rotateValue, minPitchRotation, maxPitchRotation);

	// Set the new rotation for the SpringArm
	FRotator _newArmRotation = FRotator(_newPitch, _currentRotation.Yaw, _currentRotation.Roll);
	springArm->SetWorldRotation(_newArmRotation);
	//AddControllerPitchInput(-_rotateValue);
	
}

void ADragon::Action()
{
	if (!canUseMoveInputs)return;

	//coneTraceCompo->ConeTrace();
	//targetLocation = coneTraceCompo->GetLineTraceEnd();
	if (allProjectileMats.Num() <= 0)return;
	SphereTrace();
	onLineTraceCreated.Broadcast();

}

void ADragon::ScrollUpSelectProjectile()
{
	if (!canUseMoveInputs)return;

	if (!allProjectileMats.IsValidIndex(currentProjectileIndex))return;
	float _minRange = allProjectileMats.Num() - 1 ;
	currentProjectileIndex = FMath::Clamp(currentProjectileIndex + 1, 0, _minRange);
	UpdateProjectileMaterial();
	DebugText("ScrollUp");


}

void ADragon::ScrollDownSelectProjectile()
{
	if (!canUseMoveInputs)return;

	if (!allProjectileMats.IsValidIndex(currentProjectileIndex))return;
	float _minRange = allProjectileMats.Num() - 1;
	currentProjectileIndex = FMath::Clamp(currentProjectileIndex -1, 0, _minRange);
	UpdateProjectileMaterial();
	DebugText("ScrollDown");

}

void ADragon::UpdateProjectileMaterial()
{
	if (!projectileToSpawn)return;
	AProjectile* _projectileRef = projectileToSpawn.GetDefaultObject();
	UStaticMeshComponent* _projectileMesh = _projectileRef->
		GetComponentByClass<UStaticMeshComponent>();
	//UMaterialInterface* _projectileMaterial = _projectileMesh->GetMaterial(0)->GetMaterial();
	_projectileMesh->SetMaterial(0, allProjectileMats[currentProjectileIndex]);
	onCurrentProjectileMatReceived.Broadcast(allProjectileMats[currentProjectileIndex]); // returns current mat about to shoot
	allProjectileMats.Sort();
}

void ADragon::OpenMainMenu()
{
	onMenuOpened.Broadcast();
	GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Black, TEXT("OpeningMenu"));

}

void ADragon::TestMatReceived(UMaterialInterface* _matReceived)
{
	UE_LOG(LogTemp, Warning, TEXT("Mat received EVENT! received -> %s!"), *_matReceived->GetName());

}
void ADragon::FireBreath()
{
	if (manaCompo->isOutOfMana || manaCompo->currentMana <= manaCompo->projectileManaCost)return;
	spawnPointLocation = spawnPoint->GetComponentLocation();	
	FVector _location;
	FRotator _rotation;					
	playerController->GetPlayerViewPoint(_location,_rotation);
	FVector _fwdVector = _rotation.Vector();
	locationOnLineTraceSpawn = _fwdVector;

	//DebugText("Doing Action");
	if (!(projectileToSpawn))
	{
		GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Black, TEXT("Empty subclass projectile"));
		return;
	}
	if (!projectileToSpawn)return;

	if (!attackCompo)return;
	AProjectile* _spawnedProjectile = attackCompo->SpawnProjectile(spawnPointLocation,GetOwner());
	if (!_spawnedProjectile)return;
	manaCompo->RemoveMana(manaCompo->projectileManaCost);    
	_spawnedProjectile->
		projectileManager->AddItem(_spawnedProjectile);
	float _size = projectileManager->GetAllProjectilesSize();
	for (int i = 0; i < _size; i++)
	{
		
		_spawnedProjectile->SetLaunchTime();
		_spawnedProjectile->SetMaxDistance(sphereTracedistance-100);
		_spawnedProjectile->SetTargetLocation(targetLocation);
		_spawnedProjectile->SetForwardVector(_fwdVector);
		_spawnedProjectile->SetCanMove(true);

	}
	onProjectileShot.Broadcast();

	

	
}


void ADragon::SphereTrace()
{

	if (!IsValid(GetOwner()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Failed to find owner"));
		return;
	}
	FVector _location;
	FRotator _rotation;
	playerController->GetPlayerViewPoint(_location, _rotation);

	//DrawDebugSphere(GetWorld(), _location,
		//100, 25, FColor::Yellow, true, -1, 0, 3);
	//FVector _startLocation = _location;
	FVector _startLocation = GetSpawnLocation();
	FRotator _ownerRotation = GetActorRotation();
	//FVector _forwardVector = GetActorForwardVector();
	FVector _forwardVector = _rotation.Vector();


	//UE_LOG(LogTemp, Error, TEXT("startLocation %s "),*_startLocation.ToString());

	FVector _endLocation = _startLocation + (_forwardVector * (sphereTracedistance + coneTraceRadius));
	//DrawDebugLine(world, _startLocation, _endLocation, FColor::Blue, true, -1, 0, 3);

	targetLocation = _endLocation;
	//UE_LOG(LogTemp, Error, TEXT("DRAGON ENDLOCATION %s "), *_endLocation.ToString());
	DrawDebugSphere(GetWorld(), _endLocation,
		200, 25, FColor::Black, false, -1, 0, 3);
	FCollisionQueryParams _collisionParams;
	_collisionParams.AddIgnoredActor(GetOwner());
	TArray<FHitResult> _allHits;
	FQuat _quat = FQuat(GetActorRotation());
	FHitResult _hitResult;
	bool _hit = GetWorld()->LineTraceSingleByChannel(
		_hitResult, _location, _endLocation,
		_coneTraceChannel, _collisionParams
	);
	hitResult = _hitResult;
	
}

void ADragon::LineTraceDisplacement(UWorld* _world, const FHitResult& _hitResult)
{
	//if (!_hitResult.GetActor() || !_hitResult.GetActor()->IsValidLowLevelFast())return;

	//if (!IsValid(_hitResult.GetActor()))return;
	//DrawDebugSphere(_world, _hitResult.Location, 10, 20, FColor::Cyan, true, -1, 0, 3);
	//UE_LOG(LogTemp, Error, TEXT("The FireBreath hit: %s"), *_hitResult.GetActor()->GetName());
	//AActor* _hitActor = _hitResult.GetActor();
	//FVector _hitActorLocation = _hitActor->GetActorLocation();
	////working displacement
	//FVector _displacedLocation = _hitActor->GetActorLocation() + FVector(locationOnLineTraceSpawn * lineTraceEffectMultiplier);
	//_hitResult.GetActor()->SetActorLocation(_displacedLocation);

	//// Desutrction tag
	//if (_hitActor->ActorHasTag("ExplodeOnProjectileHit"))
	//{

	//	UE_LOG(LogTemp, Warning, TEXT("BLOWING UP"), *_hitResult.GetActor()->GetName())
	//	_hitActor->Destroy();
	//	
	//}
}
void ADragon::StartLineTraceAction()
{
	LineTraceDisplacement(world, hitResult);
	//UE_LOG(LogTemp, Warning, TEXT("DRAGON EVENT CALLED THROUGH  PROJECTILE"));

}




void ADragon::DebugText(FString _string)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"),*_string);

}


// Called to bind functionality to input
void ADragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* _myInputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!_myInputCompo)
	{
		DebugText("Failed to cast to input");
	}
	
	_myInputCompo->BindAction(inputToMove, ETriggerEvent::Triggered, this, &ADragon::Move);
	_myInputCompo->BindAction(inputToRotateYaw, ETriggerEvent::Triggered, this, &ADragon::RotateYaw);
	_myInputCompo->BindAction(inputToPitch, ETriggerEvent::Triggered, this, &ADragon::RotatePitch);
	_myInputCompo->BindAction(inputToAction, ETriggerEvent::Triggered, this, &ADragon::Action);
	_myInputCompo->BindAction(inputToScrollUpSelectProjectile, ETriggerEvent::Triggered, this, &ADragon::ScrollUpSelectProjectile);
	_myInputCompo->BindAction(inputToScrollDownSelectProjectile, ETriggerEvent::Triggered, this, &ADragon::ScrollDownSelectProjectile);
	
	_myInputCompo->BindAction(inputToOpenMenu, ETriggerEvent::Triggered, this, &ADragon::OpenMainMenu);

}

void ADragon::UpdateMinDistanceToSelfDestruct()
{
	minDistanceToSelfDestruct = coneTraceRadius / 2;
}

//Audio

void ADragon::PlaySound(USoundBase* _audioToPlay)
{
	UGameplayStatics::PlaySound2D(GetWorld(), _audioToPlay);

}
void ADragon::PlayProjectileSound()
{
	PlaySound(projectileSound);
}



//float ADragon::IncreaseTime(float _current, float _max)
//	{
//	//if (!canStartAlphaCount)return _current;
//	_current += GetWorld()->DeltaTimeSeconds;
//		if (_current >= _max)
//		{
//			_current = 0;
//
//			return _current;
//		}
//		return _current;
//	}








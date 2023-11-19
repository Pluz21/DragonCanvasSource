
#include "Dragon.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "MoveComponent.h"
#include "ProjectileManager.h"
#include "CustomGameMode.h"

#include "Projectile.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADragon::ADragon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Dragon Constructor!"));

	spawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	springArm = CreateDefaultSubobject<USpringArmComponent>("Springarm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	spawnPoint->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	springArm->SetupAttachment(RootComponent);
	

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
	onLineTraceCreated.AddDynamic(this, &ADragon::FireBreath);
	Init();
	
}

void ADragon::Init()
{
	gameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>(); // Grab game mode
	if (!gameMode)return;
	projectileManager = gameMode->GetProjectileManager();
	if (!projectileManager)return;

	world = GetWorld();
	playerController = GetWorld()->GetFirstPlayerController();
	InitInput();
	InitCameraLimit();
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
	UE_LOG(LogTemp, Warning, TEXT("Init inputs"));
}

void ADragon::InitCameraLimit()
{
	
}

void ADragon::Move(const FInputActionValue& _value)
{
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
	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _rotateValue = _value.Get<float>() * _delta * rotateSpeed;
	rotateInputValue = _rotateValue;
	AddControllerYawInput(_rotateValue);
}

void ADragon::RotatePitch(const FInputActionValue& _value)
{
	

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
	//coneTraceCompo->ConeTrace();
	//targetLocation = coneTraceCompo->GetLineTraceEnd();
	SphereTrace();
	onLineTraceCreated.Broadcast();

}

void ADragon::FireBreath()
{

	spawnPointLocation = spawnPoint->GetComponentLocation();
	//FVector _fwdVector = GetActorForwardVector();
	
	FVector _location;
	FRotator _rotation;
	playerController->GetPlayerViewPoint(_location,_rotation);
	FVector _fwdVector = _rotation.Vector();
	locationOnLineTraceSpawn = _fwdVector;

	DebugText("Doing Action");
	if (!(projectileToSpawn))
	{
		GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Black, TEXT("Empty subclass projectile"));
		return;
	}
	//AProjectile* _spawnedProjectile = attackCompo->SpawnProjectile(spawnPointLocation,this);
	if (!projectileToSpawn)return;
	AProjectile* _spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(projectileToSpawn, spawnPointLocation, FRotator::ZeroRotator);
	if (!_spawnedProjectile)return;
		projectileManager->AddItem(_spawnedProjectile);
	float _size = projectileManager->GetAllProjectilesSize();
	for (int i = 0; i < _size; i++)
	{
		//float EstimatedTravelTime = 
		//	DistanceTraveled / MoveSpeed;
		//float DelayTime = FMath::Max(0.0f, EstimatedTravelTime - (GetWorld()->GetTimeSeconds() - LaunchTime));

		//GetWorld()->GetTimerManager().SetTimer(EffectTimerHandle, this, &YourClass::ApplyEffect, DelayTime, false);
		
		// TODO call only one main function in projectile;
		_spawnedProjectile->SetLaunchTime();
		_spawnedProjectile->SetMaxDistance(sphereTracedistance-100);
		//UE_LOG(LogTemp, Warning, TEXT("MaxDistance : %f"), _spawnedProjectile->maxDistance);

		_spawnedProjectile->SetTargetLocation(targetLocation);
		_spawnedProjectile->SetForwardVector(_fwdVector);
		_spawnedProjectile->SetCanMove(true);
		_spawnedProjectile->SetOwner(this);
		
		//TO DO 

		//{
		//	// Perform your line trace and set HitLocation and bLineTraceHit accordingly
		//	// ...

		//	// Calculate delay based on the estimated travel time
		//	float EstimatedTravelTime = DistanceTraveled / MoveSpeed;
		//	float DelayTime = FMath::Max(0.0f, EstimatedTravelTime - (GetWorld()->GetTimeSeconds() - LaunchTime));

		//	// Start a timer to apply the effect after a delay
		//	GetWorld()->GetTimerManager().SetTimer(EffectTimerHandle, this, &YourClass::ApplyEffect, DelayTime, false);
		//}

	}
	

	
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
	DrawDebugLine(world, _startLocation, _endLocation, FColor::Blue, true, -1, 0, 3);

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

	if (!IsValid(_hitResult.GetActor()))return;
	DrawDebugSphere(_world, _hitResult.Location, 10, 20, FColor::Cyan, true, -1, 0, 3);
	UE_LOG(LogTemp, Error, TEXT("The FireBreath hit: %s"), *_hitResult.GetActor()->GetName());
	AActor* _hitActor = _hitResult.GetActor();
	FVector _hitActorLocation = _hitActor->GetActorLocation();
	//working displacement
	FVector _displacedLocation = _hitActor->GetActorLocation() + FVector(locationOnLineTraceSpawn * lineTraceEffectMultiplier);
	_hitResult.GetActor()->SetActorLocation(_displacedLocation);

	// Desutrction tag
	if (_hitActor->ActorHasTag("ExplodeOnProjectileHit"))
	{

		UE_LOG(LogTemp, Warning, TEXT("BLOWING UP"), *_hitResult.GetActor()->GetName())
		_hitActor->Destroy();
		
	}
}
void ADragon::StartLineTraceAction()
{
	LineTraceDisplacement(world, hitResult);
	UE_LOG(LogTemp, Warning, TEXT("DRAGON EVENT CALLED THROUGH  PROJECTILE"));

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


}

void ADragon::UpdateMinDistanceToSelfDestruct()
{
	minDistanceToSelfDestruct = coneTraceRadius / 2;
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








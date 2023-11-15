
#include "Dragon.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "MoveComponent.h"

#include "Projectile.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetSystemLibrary.h"

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
	onLineTraceCreated.AddDynamic(this, &ADragon::FireBreath);
	Init();
	
}

void ADragon::Init()
{
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
	FVector _fwdVector = GetActorForwardVector();
	DebugText("Doing Action");
	if (!(projectileToSpawn))
	{
		GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Black, TEXT("Empty subclass projectile"));
		return;
	}
	//AProjectile* _spawnedProjectile = attackCompo->SpawnProjectile(spawnPointLocation,this);
	AProjectile* _spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(projectileToSpawn, spawnPointLocation, FRotator::ZeroRotator);
	allProjectiles.Add(_spawnedProjectile);
	float _size = allProjectiles.Num();
	for (int i = 0; i < _size; i++)
	{
		if (_spawnedProjectile)
		{
		_spawnedProjectile->SetTargetLocation(targetLocation);
		_spawnedProjectile->SetForwardVector(_fwdVector);
		_spawnedProjectile->SetCanMove(true);
		_spawnedProjectile->SetOwner(this);
		//UE_LOG(LogTemp, Warning, TEXT("Spawned Projectile Owner: %s"), *_spawnedProjectile->GetOwner()->GetName());

		}
	

	}
}

void ADragon::SphereTrace()
{

	if (!IsValid(GetOwner()))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Failed to find owner"));
		return;
	}
	FVector _startLocation = GetActorLocation();
	FRotator _ownerRotation = GetActorRotation();
	FVector _forwardVector = GetActorForwardVector();



	//UE_LOG(LogTemp, Error, TEXT("startLocation %s "),*_startLocation.ToString());

	FVector _endLocation = _startLocation + (_forwardVector * (sphereTracedistance + coneTraceRadius));
	targetLocation = _endLocation;
	//UE_LOG(LogTemp, Error, TEXT("DRAGON ENDLOCATION %s "), *_endLocation.ToString());
	DrawDebugSphere(GetWorld(), _endLocation,
		200, 25, FColor::Black, false, -1, 0, 3);
	FCollisionQueryParams _ignoreSelfParam;
	_ignoreSelfParam.AddIgnoredActor(GetOwner());

	TArray<FHitResult> _allHits;
	FQuat _quat = FQuat(GetActorRotation());

	bool _hit = GetWorld()->SweepMultiByChannel(_allHits, _startLocation,
		_endLocation, _quat,
		_coneTraceChannel, FCollisionShape::MakeSphere(coneTraceRadius),
		_ignoreSelfParam);
	if (_hit)
	{
		for (int i = 0; i < _allHits.Num(); i++)

		{
			UE_LOG(LogTemp, Warning, TEXT("The FireBreath hit: %s"), *_allHits[i].GetActor()->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing hit by FireBreath"));


	}

	DrawDebugSphere(GetWorld(), _startLocation,
		coneTraceRadius + sphereTracedistance, 25, FColor::Orange, false, -1, 0, 3);
}

void ADragon::SetMaximumPitch()
{
	
}



void ADragon::DebugText(FString _string)
{
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


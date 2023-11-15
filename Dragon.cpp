
#include "Dragon.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "AttackComponent.h"
#include "MoveComponent.h"
#include "ConeLineTrace.h"

#include "Projectile.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ADragon::ADragon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	springArm = CreateDefaultSubobject<USpringArmComponent>("Springarm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	attackCompo = CreateDefaultSubobject<UAttackComponent>("attackCompo");
	coneTraceCompo = CreateDefaultSubobject<UConeLineTrace>("coneTraceCompo");
	
	spawnPoint->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	springArm->SetupAttachment(RootComponent);
	AddOwnedComponent(attackCompo);
	AddOwnedComponent(coneTraceCompo);

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
	InitInput();
	Init();
	
}

void ADragon::Init()
{
	world = GetWorld();
	currentAmmo = maxAmmo;
	playerController = GetWorld()->GetFirstPlayerController();
}

void ADragon::InitInput()
{
	ULocalPlayer* _myPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!_myPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _myPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_inputSystem)return;
	_inputSystem->AddMappingContext(mappingContext, 0);
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
	AddControllerPitchInput(_rotateValue);
	
}

void ADragon::Action()
{
	FireBreath();
	coneTraceCompo->ConeTrace();

}

void ADragon::FireBreath()
{
	spawnPointLocation = spawnPoint->GetComponentLocation();
	FVector _fwdVector = GetActorForwardVector();
	DebugText("Doing Action");
	if (!(attackCompo->projectileRef))
	{
		GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Black, TEXT("Empty subclass projectile"));
		return;
	}
	AProjectile* _spawnedProjectile = attackCompo->SpawnProjectile(spawnPointLocation);
	allProjectiles.Add(_spawnedProjectile);
	float _size = allProjectiles.Num();
	for (int i = 0; i < _size; i++)
	{
		_spawnedProjectile->SetForwardVector(_fwdVector);
		_spawnedProjectile->SetCanMove(true);
		

	}
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


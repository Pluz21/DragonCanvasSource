// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "HealthPickUp.h"
#include "DragonCanvas/Actors/Dragon.h"
#include "DragonCanvas/Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AHealthPickUp::AHealthPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");
	capsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("capsuleCollider");
	soundToPlay = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Sounds/Health_Pickup_sound.Health_Pickup_sound")).Object;

	meshCompo->SetupAttachment(RootComponent);
	capsuleCollider->SetupAttachment(meshCompo);
}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AHealthPickUp::ManageOverlap);
	bool _isBound = OnActorBeginOverlap.IsBound();
	
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
}

void AHealthPickUp::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	if (!_overlapped || !_overlap)return;
	UE_LOG(LogTemp, Warning, TEXT("Overlapping with %s"), *_overlap->GetName());

	ADragon* _dragonRef = Cast<ADragon>(_overlap);
	if (!_dragonRef)return;
	_dragonRef->healthCompo->AddHealth(healthToAdd);
	_overlapped->Destroy();
	PlaySound(soundToPlay);
}

void AHealthPickUp::Rotate()
{
	if (!canRotate) return;


	float _rotateValue = rotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator _currentRotation = GetActorRotation();
	FRotator _newRotation = FRotator(0, _rotateValue, 0);

	SetActorRotation(_currentRotation + _newRotation);
}

void AHealthPickUp::PlaySound(USoundBase* _audioToPlay)
{
	if (!_audioToPlay)return;
	UGameplayStatics::PlaySound2D(GetWorld(), _audioToPlay);
}


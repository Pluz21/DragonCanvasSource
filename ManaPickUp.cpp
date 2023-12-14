// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "ManaPickUp.h"
#include "Dragon.h"
#include "ManaComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AManaPickUp::AManaPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");
	capsuleCollider = CreateDefaultSubobject<UCapsuleComponent>("capsuleCollider");
	meshCompo->SetupAttachment(RootComponent);
	capsuleCollider->SetupAttachment(meshCompo);
}

// Called when the game starts or when spawned
void AManaPickUp::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

// Called every frame
void AManaPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();

}

void AManaPickUp::Init()
{
	OnActorBeginOverlap.AddDynamic(this, &AManaPickUp::ManageOverlap);
	bool _isBound = OnActorBeginOverlap.IsBound();
	UE_LOG(LogTemp, Warning, TEXT("Init ManaPickUp : %d"), _isBound);


}

void AManaPickUp::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	if (!_overlapped || !_overlap)return;
	UE_LOG(LogTemp, Warning, TEXT("Overlapping with %s"), *_overlap->GetName());
	
	ADragon* _dragonRef = Cast<ADragon>(_overlap);
	if (!_dragonRef)return; 
	_dragonRef->manaCompo->AddMana(manaToAdd);
	_overlapped->Destroy();
}

void AManaPickUp::Rotate()
{
	if (!canRotate) return;


	float _rotateValue = rotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator _currentRotation = GetActorRotation();
	FRotator _newRotation = FRotator(0, _rotateValue, 0);

	SetActorRotation(_currentRotation + _newRotation);
}


// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Actors/Gun.h"
#include "DragonCanvas/Actors/Dragon.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	gunMesh = CreateDefaultSubobject<UStaticMeshComponent>("gunMesh");
	gunSubMesh = CreateDefaultSubobject<UStaticMeshComponent>("gunSubMesh");
	materialChangerMesh = CreateDefaultSubobject<UStaticMeshComponent>("materialChangerMesh");
	
	gunMesh->SetupAttachment(RootComponent);
	gunSubMesh->SetupAttachment(gunMesh);
	materialChangerMesh->SetupAttachment(gunSubMesh);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

void AGun::Init()
{
	InitPlayerRef();
	InitEvents();
	gunSubMesh->SetVisibility(false,true);
	//GetOnCurrentProjectileMatReceived()
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate(materialChangerMesh);
}

void AGun::InitPlayerRef()
{
	if (!GetWorld()->GetFirstPlayerController())return;
	ADragon* _playerRef = Cast<ADragon>(GetWorld()->GetFirstPlayerController()->
		GetPawn());
	playerRef = _playerRef;

}

void AGun::InitEvents()
{
	if (!playerRef)return;
	playerRef->GetOnCurrentProjectileMatReceived().AddDynamic(this, &AGun::UpdateBarrelMaterial);
	onBarrelMaterialReceived.AddDynamic(this, &AGun::UpdateBarrelVisibility);
	onBarrelMaterialReceived.AddDynamic(this, &AGun::SetCanRotate);
	
}

void AGun::UpdateBarrelMaterial(UMaterialInterface* _matToApply)
{
	if (!_matToApply)return;
	materialChangerMesh->SetMaterial(0,_matToApply);
	UE_LOG(LogTemp, Warning, TEXT("UpdateBarrel called"));
	onBarrelMaterialReceived.Broadcast();

}

void AGun::UpdateBarrelVisibility()
{
	if (!playerRef)return;
	if (!gunSubMesh->GetVisibleFlag())
	{
		gunSubMesh->SetVisibility(true,true);

	}
	
}

void AGun::SetCanRotate()
{
	canRotate = true;
}

void AGun::Rotate(UStaticMeshComponent* _meshToRotate)
{
	if (!canRotate)return;
	float _rotateSpeed = rotateSpeed * GetWorld()->DeltaTimeSeconds;


	FRotator _currentRotation = _meshToRotate->GetComponentRotation();
	FRotator _newRotation = FRotator(0, _rotateSpeed, _rotateSpeed);
	UE_LOG(LogTemp, Warning, TEXT("Rotate called"));

	_meshToRotate->SetWorldRotation(_currentRotation + _newRotation);
}


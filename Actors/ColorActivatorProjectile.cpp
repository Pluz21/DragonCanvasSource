//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "ColorActivatorProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "DragonCanvas/MaterialCheckerComponent.h"
#include "DragonCanvas/HiddenActors.h"
#include "Projectile.h"

// THIS CLASS IS THE ONE THAT ALLOWS ACTORS TO CHANGE TO THE COLOR OF THE PROJECTILE
AColorActivatorProjectile::AColorActivatorProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");
	materialChecker = CreateDefaultSubobject<UMaterialCheckerComponent>("materiaChecker");
	meshCompo->SetupAttachment(RootComponent);
	AddOwnedComponent(materialChecker);

}

// Called when the game starts or when spawned
void AColorActivatorProjectile::BeginPlay()
{
	Super::BeginPlay();
	Init();
	//initialMat = meshCompo->CreateDynamicMaterialInstance(0);
}

// Called every frame
void AColorActivatorProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorActivatorProjectile::Init()
{
	OnActorBeginOverlap.AddDynamic(this, &AColorActivatorProjectile::ManageOverlap);
	onMaterialReceived.AddDynamic(this, &AColorActivatorProjectile::RevealHiddenActors);
	initialCollisionSetting = meshCompo->GetCollisionEnabled();
	meshCompo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AColorActivatorProjectile::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	//Super::ManageOverlap(_overlapped, _overlap);

	if (!_overlap || !_overlapped) return;
	if (!_overlap->IsA(AProjectile::StaticClass()))return;
	if (canCheckMat)
	{
		meshCompo->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		meshCompo->SetCollisionEnabled(initialCollisionSetting);
		UStaticMeshComponent* _projectileMeshComponent = _overlap->
			FindComponentByClass<UStaticMeshComponent>();

		int _size = materialChecker->GetAllMatsSize();
		for (int i = 0; i < _size; i++)
		{
			if (_projectileMeshComponent->GetMaterial(0) == materialChecker->GetAllMatsToCheck()[i])
			{
			ReceiveColor(_overlap);
			onMaterialReceived.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("matToCheck is true : mattocheck = %s"), *allMatsToCheck[i]->GetName());

			}
			
		}

	}
	else
	{
		ReceiveColor(_overlap);
	}
	


}

void AColorActivatorProjectile::ReceiveColor(AActor* _targetToGetColorFrom)
{
	UStaticMeshComponent* _projectileMesh = _targetToGetColorFrom->GetComponentByClass < UStaticMeshComponent >();
	UMaterialInterface* _projectileMat = _projectileMesh->GetMaterial(0);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *_projectileMat->GetName());
	meshCompo->SetMaterial(0, _projectileMat);

}

void AColorActivatorProjectile::RevealHiddenActors()
{
	UE_LOG(LogTemp, Error, TEXT("REVEAL HIDDEN ACTORS CALLED"));
	int _size = allHiddenActors.Num();
	for (int i = 0; i < _size; i++)
	{
		if (allHiddenActors[i] == nullptr)return;
		allHiddenActors[i]->GetComponentByClass<UStaticMeshComponent>()->
			SetVisibility(true,true);

	}
}




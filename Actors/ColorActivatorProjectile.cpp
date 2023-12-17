//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "ColorActivatorProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "DragonCanvas/MaterialCheckerComponent.h"
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
	OnActorBeginOverlap.AddDynamic(this, &AColorActivatorProjectile::ManageOverlap);
	//initialMat = meshCompo->CreateDynamicMaterialInstance(0);
}

// Called every frame
void AColorActivatorProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorActivatorProjectile::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	//Super::ManageOverlap(_overlapped, _overlap);

	if (!_overlap || !_overlapped) return;
	if (!_overlap->IsA(AProjectile::StaticClass()))return;
	if (canCheckMat)
	{
		UStaticMeshComponent* _projectileMeshComponent = _overlap->
			FindComponentByClass<UStaticMeshComponent>();
			int _size = allMatsToCheck.Num();
	for (int i = 0; i < _size; i++)
	{
		if (_projectileMeshComponent->GetMaterial(0) == allMatsToCheck[i])
		ReceiveColor(_overlap);
		UE_LOG(LogTemp, Warning, TEXT("matToCheck is true : mattocheck = %s"), *matToCheck.GetName());
			
	}
	//if(_projectileMeshComponent->GetMaterial(0) )
	//	if (_projectileMeshComponent->GetMaterial(0) == matToCheck)
		/*else
		{
		UE_LOG(LogTemp, Warning, TEXT("matToCheck is false : mattocheck = %s"), *matToCheck.GetName());
		}*/

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




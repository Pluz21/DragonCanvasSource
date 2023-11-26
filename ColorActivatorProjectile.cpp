// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorActivatorProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
AColorActivatorProjectile::AColorActivatorProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");

	meshCompo->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AColorActivatorProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AColorActivatorProjectile::ManageOverlap);
	initialMat = meshCompo->CreateDynamicMaterialInstance(0);
	
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
	if(_overlap->IsA(AProjectile::StaticClass()))
	ReceiveColor(_overlap);
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));

}

void AColorActivatorProjectile::ReceiveColor(AActor* _projectile)
{
	UStaticMeshComponent* _projectileMesh = _projectile->GetComponentByClass < UStaticMeshComponent >();
	UMaterialInterface* _projectileMat = _projectileMesh->GetMaterial(0);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *_projectileMat->GetName());
	meshCompo->SetMaterial(0, _projectileMat);

}
//}void AColorActivatorProjectile::ReceiveColor()
//{
//	/*UStaticMeshComponent* _projectileMesh = _projectile->GetComponentByClass < UStaticMeshComponent >();
//	UMaterialInterface* _projectileMat = _projectileMesh->GetMaterial(0);
//	UE_LOG(LogTemp, Warning, TEXT("%s"), *_projectileMat->GetName());
//	meshCompo->SetMaterial(0, _projectileMat);*/
//
//
//	//if (canReceiveColor)
//	
//
//}



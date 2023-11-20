// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorActivator.h"
#include "Dragon.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


// Sets default values
AColorActivator::AColorActivator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");

	meshCompo->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AColorActivator::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AColorActivator::ManageOverlap);
	Init();
	
}

// Called every frame
void AColorActivator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
void AColorActivator::Init()
{
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	TSubclassOf<AProjectile> _projectileRef = _dragonRef->GetProjectileToSpawn();
	dragonProjectileRef = _projectileRef;
}


void AColorActivator::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping with "));
	if (!_overlap || !_overlapped) return;
	UStaticMeshComponent* _targetMesh = _overlap->GetComponentByClass<UStaticMeshComponent>();
	UMaterialInterface* _targetMatInterface =  _targetMesh->GetMaterial(0);
	UMaterial* _targetMat = _targetMatInterface->GetMaterial();
	_targetMesh->SetMaterial(0,matToApply);
	GiveColor();

	
	//_targetMat->SetMaterial(matToApply);
}

void AColorActivator::GiveColor()
{
	if (!dragonProjectileRef)return;
	AProjectile* _projectileRef = dragonProjectileRef.GetDefaultObject();
	
	 UStaticMeshComponent* _projectileMesh = _projectileRef->
					GetComponentByClass<UStaticMeshComponent>();

	 UMaterial* _projectileMaterial = _projectileMesh->GetMaterial(0)->GetMaterial();
	 _projectileMesh->SetMaterial(0,matToApply);

}



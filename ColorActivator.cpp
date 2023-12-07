// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorActivator.h"
#include "Dragon.h"
#include "PickUps.h"
#include "ProjectileTriggerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"


// Sets default values
AColorActivator::AColorActivator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>("root");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("baseMesh");
	secondMesh = CreateDefaultSubobject<UStaticMeshComponent>("secondMesh");
	triggerCompo = CreateDefaultSubobject<UProjectileTriggerComponent>("trigger");
	baseMesh->SetupAttachment(root);
	secondMesh->SetupAttachment(baseMesh);
	AddOwnedComponent(triggerCompo);
}

// Called when the game starts or when spawned
void AColorActivator::BeginPlay()
{
	Super::BeginPlay();
	onMaterialReceived.AddDynamic(this, &AColorActivator::Test);
	onMaterialReceived.AddDynamic(this, &AColorActivator::ApplyMatToApply);
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
	if (!secondMesh || !baseMesh)return;
	UMaterialInterface* _secondMeshMat = secondMesh->GetMaterial(0);
	if (!_secondMeshMat)return;
	baseMesh->SetMaterial(0, _secondMeshMat);
	onMaterialReceived.Broadcast(_secondMeshMat);
}




void AColorActivator::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	if (!_overlap || !_overlapped) return;

	if (_overlap->IsA(APickUps::StaticClass()) && _overlap->ActorHasTag("Grabbed"))
	{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping with %s"), *_overlap->GetName());
	GiveColor();
	if (!triggerCompo)return; 
	triggerCompo->SnapTarget(_overlap);
	//ProjectileTriggerComponent->Activate 
	}
	
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

void AColorActivator::Test(UMaterialInterface* _mat)
{

	UE_LOG(LogTemp, Warning, TEXT("mat test is %s"), *_mat->GetName());
}

void AColorActivator::ApplyMatToApply(UMaterialInterface* _mat)
{
	if (!_mat)return;
	matToApply = secondMesh->CreateDynamicMaterialInstance(0, _mat);
}



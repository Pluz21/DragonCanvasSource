//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "ColorActivatorProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "DragonCanvas/Components/MaterialCheckerComponent.h"
#include "DragonCanvas/Actors/HiddenActors.h"
#include "UObject/ConstructorHelpers.h"
#include "Projectile.h"

// THIS CLASS IS THE ONE THAT ALLOWS ACTORS TO CHANGE TO THE COLOR OF THE PROJECTILE
AColorActivatorProjectile::AColorActivatorProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");
	materialChecker = CreateDefaultSubobject<UMaterialCheckerComponent>("materiaChecker");
	onRevealSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Sounds/Interaction_Sounds/RevealSoundSource.RevealSoundSource")).Object;
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
	onReveal.AddDynamic(this, &AColorActivatorProjectile::PlaySound);
	onReveal.AddDynamic(this, &AColorActivatorProjectile::SetIsRevealed);
	
	//FRevealedEvent::FDelegate _lambdaDelegate	
	/*_lambdaDelegate.AddLambda([this]() {
		PlayRevealSound(onRevealSound); 
		});
	onReveal.Add(_lambdaDelegate);*/

	initialCollisionSetting = meshCompo->GetCollisionEnabled();
	meshCompo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AColorActivatorProjectile::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	//Super::ManageOverlap(_overlapped, _overlap);

	if (!_overlap || !_overlapped) return;
	if (!_overlap->IsA(AProjectile::StaticClass()))return;
	if (isRevealed)return;
	{
		if(materialChecker->ActorMaterialCheck(_overlap))
		{
			meshCompo->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			meshCompo->SetCollisionEnabled(initialCollisionSetting);
			ReceiveColor(_overlap);
			onMaterialReceived.Broadcast();
			onReveal.Broadcast();


		}
			
	}
}

void AColorActivatorProjectile::ReceiveColor(AActor* _targetToGetColorFrom)
{
	UStaticMeshComponent* _projectileMesh = _targetToGetColorFrom->GetComponentByClass < UStaticMeshComponent >();
	UMaterialInterface* _projectileMat = _projectileMesh->GetMaterial(0);
	meshCompo->SetMaterial(0, _projectileMat);

}

void AColorActivatorProjectile::RevealHiddenActors()
{
	int _size = allHiddenActors.Num();
	for (int i = 0; i < _size; i++)
	{
		if (allHiddenActors[i] == nullptr)return;
		allHiddenActors[i]->GetComponentByClass<UStaticMeshComponent>()->
			SetVisibility(true,true);

	}
}

void AColorActivatorProjectile::SetIsRevealed()
{
	isRevealed = true;
}

void AColorActivatorProjectile::PlayRevealSound(USoundBase* _soundSource)
{
	if (!_soundSource)return;
	UGameplayStatics::PlaySound2D(GetWorld(), _soundSource);
	UE_LOG(LogTemp, Error, TEXT("REVEAL HIDDEN ACTORS SOUND CALLED"));

}

void AColorActivatorProjectile::PlaySound()
{
	PlayRevealSound(onRevealSound);
	UE_LOG(LogTemp, Error, TEXT("REVEAL HIDDEN ACTORS SOUND CALLED"));

}





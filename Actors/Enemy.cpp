//Copyright � 2023 Pluz21(TVL).All rights reserved.

#include "Enemy.h"
#include "DragonCanvas/Components/MoveComponent.h"
#include "DragonCanvas/Actors/Dragon.h"
#include "DragonCanvas/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"




// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>("root");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("baseMesh");
	secondMesh = CreateDefaultSubobject<UStaticMeshComponent>("secondMesh");
	moveCompo = CreateDefaultSubobject<UMoveComponent>("moveCompo");
	soundToPlay = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Sounds/Enemy_Hit_sound.Enemy_Hit_sound")).Object;
	baseMesh->SetupAttachment(root);
	secondMesh->SetupAttachment(baseMesh);
	AddOwnedComponent(moveCompo);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}



void AEnemy::Init()
{
	SetLifeSpan(20);  // TODO Make variable
	playerRef = moveCompo->GetChaseTarget();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!moveCompo)return;
	moveCompo->ChasePlayer();
	SelfDestroy();

}

bool AEnemy::CheckDistance()
{
	if (!playerRef)return false;
	float _distance = FVector::Dist(playerRef->GetActorLocation(), GetActorLocation());
	if(_distance < minDistanceAllowed)
		return true;
	return false;
}

void AEnemy::SelfDestroy()
{
	if (CheckDistance())
	{
		if (!playerRef)return;   // Enemy will join on top of you
		Destroy(); // Play Animation
		if (playerRef->healthCompo->isDead)return;
		ApplyDamage();
		PlaySound(soundToPlay);
		UE_LOG(LogTemp, Warning, TEXT("You got hit by a Flamito!"));

	}
	// TO DO 
	// EnemyManager->RemoveEnemy(this);
	// Add explosion effect
	// Add health loss to player
}

void AEnemy::ApplyDamage()
{
	playerRef->healthCompo->RemoveHealth(damageToApply);
}

void AEnemy::PlaySound(USoundBase* _audioToPlay)
{
	if (!_audioToPlay)return;
	UGameplayStatics::PlaySound2D(GetWorld(), _audioToPlay);

}



//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "Enemy.h"
#include "DragonCanvas/Components/MoveComponent.h"
#include "DragonCanvas/Actors/Dragon.h"
#include "DragonCanvas/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DragonCanvas/MaterialCheckerComponent.h"
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
	materialCheckerCompo = CreateDefaultSubobject<UMaterialCheckerComponent>("MaterialChecker");
	hitPlayerSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Game/Sounds/Enemy_Hit_sound.Enemy_Hit_sound")).Object;
	onDeathSound = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Game/Sounds/Enemy_breaking")).Object;
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
	SetLifeSpan(lifeSpan);  // TODO Make variable
	playerRef = moveCompo->GetChaseTarget();
	//OnDestroyed.AddDynamic(this, &AEnemy::ManageOnDeath);
	onDeath.AddDynamic(this, &AEnemy::ManageOnDeath);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!moveCompo)return;
	moveCompo->ChasePlayer();
	SelfDestroy();
	currentTime = IncreaseTime(currentTime, maxTime);

}

bool AEnemy::CheckDistance()
{
	if (!playerRef || hasBeenhit == true)return false;
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
		PlayHitSound(hitPlayerSound);
		UE_LOG(LogTemp, Warning, TEXT("You got hit by an enemy!"));

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

void AEnemy::PlayHitSound(USoundBase* _audioToPlay)
{
	if (!_audioToPlay)return;
	UGameplayStatics::PlaySound2D(GetWorld(), _audioToPlay);

}

void AEnemy::PlayDeathSound(USoundBase* _audioToPlay)
{
	if (!_audioToPlay || hasBeenhit)return;
	UGameplayStatics::PlaySound2D(GetWorld(), _audioToPlay);
}


float AEnemy::IncreaseTime(float _current, float _max)
{
	/*if (!canStartDestroytimer)return _current;
	currentTime = _current + GetWorld()->DeltaTimeSeconds;
	if (currentTime >= maxTime)
	{
		currentTime = 0;
		Destroy();
		return _current;
	}

	*/
	return _current;
}

void AEnemy::SetCanStartDestroyTimer(bool _value)
{
	//canStartDestroytimer = _value;
}

void AEnemy::ManageOnDeath()
{
	PlayDeathSound(onDeathSound);
	UE_LOG(LogTemp, Warning, TEXT("SoundPLayed!"));

}




//Copyright © 2023 Pluz21(TVL).All rights reserved.
#include "Projectile.h"
#include "Dragon.h"

#include "DragonCanvas/World/CustomGameMode.h"
#include "ProjectileManager.h"
#include "Enemy.h"
#include "BossEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DragonCanvas/MaterialCheckerComponent.h"
#include "DragonCanvas/Components/MoveComponent.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("mymesh");
	meshCompo->SetupAttachment(RootComponent);
	moveCompo = CreateDefaultSubobject<UMoveComponent>("moveCompo");
	AddOwnedComponent(moveCompo);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Init();

}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	deltaSeconds = GetWorld()->DeltaTimeSeconds;
	CheckDistance(targetLocation);
	SelfMove(forwardVector);
	moveCompo->Rotate();// or call moveCompo->Move();
}

void AProjectile::Init()
{
	EventsInit();
	gameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();

	if (!gameMode)return;
	projectileManager = gameMode->GetProjectileManager();

	//projectileManager->AddItem(this); // Not necessary. Safety extra call but already called on spawn from Dragon
	actorSpawnLocation = GetActorLocation();
	forwardVector = GetActorForwardVector();
	moveSpeed = moveCompo->GetMoveSpeed(); // MoveSpeed will always be set through the component
	
	SetLifeSpan(lifeSpan);

}

void AProjectile::EventsInit()
{
	OnActorBeginOverlap.AddDynamic(this, &AProjectile::ManageOverlap);
	onTargetReached.AddDynamic(this, &AProjectile::SelfDestruct);
	onCanMove.AddDynamic(this, &AProjectile::FindEndLocation);
	onProjectileCreated.Broadcast();

}

void AProjectile::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	

	if (_overlap && (_overlap != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAPPING PROJECTILE "));
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("FAILED OVERLAPCALL"));
	ManageEnemyHit(_overlap);
	ManageBossEnemyHit(_overlap);

	onEnemyHit.Broadcast();
	
	ManageDestroyTagHit(_overlap);
	ManageCanMoveHit(_overlap);
	

}


void AProjectile::SelfMove(const FVector& _actorForwardVector)
{
	if (canMove)
	{
	moveCompo->SelfMove(forwardVector);
	onCanMove.Broadcast();
	}

}

void AProjectile::SetCanMove(bool _value)
{
	canMove = _value;
}

void AProjectile::SelfDestruct()
{
	projectileManager->RemoveItem(this);
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("DESTRUCTION"));

}

void AProjectile::ManageBossEnemyHit(AActor* _actor)
{
	if (_actor->IsA(ABossEnemy::StaticClass()))
	{
		ABossEnemy* _bossEnemy = Cast<ABossEnemy>(_actor);
		if (!_bossEnemy) return;
		if (!_bossEnemy->GetCanBeDestroyed()) return;
		UMaterialCheckerComponent* _matChecker1 = _bossEnemy->GetMaterialCheckerComponent();
		int _size = _matChecker1->GetAllMatsSize();
		UMaterialCheckerComponent* _matChecker2 = _bossEnemy->GetMaterialCheckerComponent2();
		int _size2 = _matChecker2->GetAllMatsSize();

		TArray<UStaticMeshComponent*> _allStaticMeshes;
		TArray<UStaticMeshComponent*> _allStaticMeshesFromSecondMesh;
		UStaticMeshComponent* _baseMesh = _bossEnemy->GetBaseMesh();
		UStaticMeshComponent* _secondMesh = _bossEnemy->GetSecondMesh();
		UStaticMeshComponent* _thirdMesh = _bossEnemy->GetThirdMesh();
		_allStaticMeshes = FindAllChildMeshes(_baseMesh, _secondMesh, _thirdMesh);
		_allStaticMeshesFromSecondMesh = FindAllChildMeshes(_secondMesh);
		
		for (int i = 0; i < _size; i++)
		{
			UMaterialInterface* _matToApply = meshCompo->
				GetMaterial(0);
			// 
			if (_matToApply == _matChecker2->allMatsToCheck[i] && _secondMesh->GetMaterial(0) != _matChecker2->allMatsToCheck[i]) // testing with the fire arm
			{
				_bossEnemy->SetSecondMeshMaterial(_matToApply); // parent
				_bossEnemy->SetMeshMaterialChildIncluded(_allStaticMeshesFromSecondMesh, _matToApply);
				ApplyHitEffect(_secondMesh);
				ApplyHitEffect(_allStaticMeshesFromSecondMesh);
				_bossEnemy->GetOnHit().Broadcast(); // mat to apply will return true even after destruction
				//_bossEnemy->moveCompo->SetChaseSpeed(0);
				//_bossEnemy->SetLifeSpan(enemyLifeSpan);
				//ApplyHitEffect(_allStaticMeshes);  // Dismantles static meshes
				//_bossEnemy->GetOnDeath().Broadcast();
				//_bossEnemy->SetHasBeenHit(true);
				//onEnemyHit.Broadcast();
			}
		}
	}


}

void AProjectile::ManageEnemyHit(AActor* _actor)
{
	if (_actor->IsA(ABossEnemy::StaticClass()))return;
	AEnemy* _enemy = Cast<AEnemy>(_actor);
	if (!_enemy)return;
	UMaterialCheckerComponent* _matChecker = _enemy->GetMaterialCheckerComponent();
	int _size = _matChecker->GetAllMatsSize();

	TArray<UStaticMeshComponent*> _allStaticMeshes;
	UStaticMeshComponent* _baseMesh = _enemy->GetBaseMesh();
	_allStaticMeshes = FindAllChildMeshes(_baseMesh);
	for (int i = 0; i < _size; i++)
	{
		UMaterialInterface* _matToApply = meshCompo->
			GetMaterial(0);
		if (_matToApply == _matChecker->allMatsToCheck[i])
		{
			_enemy->SetBaseMeshMaterial(_matToApply);
			_enemy->moveCompo->SetChaseSpeed(0);
			_enemy->SetLifeSpan(enemyLifeSpan);
			ApplyHitEffect(_allStaticMeshes);  // Dismantles static meshes
			_enemy->GetOnDeath().Broadcast();
			_enemy->SetHasBeenHit(true);
			onEnemyHit.Broadcast();
		}
	}

}

void AProjectile::ManageDestroyTagHit(AActor* _actor)
{
	if (_actor->ActorHasTag("Destroy"))
	{
		_actor->Destroy();
		SelfDestruct();
	}

}
void AProjectile::ManageCanMoveHit(AActor* _actor)
{
	if (_actor->ActorHasTag("CanMove"))
	{
		FVector _overlapLocation = _actor->GetActorLocation();
		FVector _displacedLocation = _overlapLocation + forwardVector * 200;
		_actor->SetActorLocation(_displacedLocation);
		SelfDestruct();
	}


}


void AProjectile::FindEndLocation()
{
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	//targetLocation = _dragonRef->GetProjectileTargetLocation();
	//lineTraceDistance = _dragonRef->GetSphereTraceDistance();
	minDistanceToSelfDestruct = _dragonRef->GetMinDistanceToSelfDestruct();
	//UE_LOG(LogTemp, Warning, TEXT("targetlocaiton is %s"), *targetLocation.ToString());
	onTargetAcquired.Broadcast();

}

void AProjectile::CheckDistance(FVector& _targetLocation)
{
	/*if (hasTarget) 
	{*/

	float _distanceToLineTraceEndLocation = FVector::Dist(GetActorLocation(), _targetLocation);
	
	//UE_LOG(LogTemp, Warning, TEXT("targetLocation : %s"), *targetLocation.ToString());

	if (_distanceToLineTraceEndLocation <= minDistanceToSelfDestruct)// || Overlapped )
	{
		onTargetReached.Broadcast(); // Calling destruct
	}
	//}
}

void AProjectile::CallLineTraceDisplacement()
{	

	//canActivateLineTraceEffect = true;

	//ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	//_dragonRef->StartLineTraceAction();
}

TArray<UStaticMeshComponent*> AProjectile::FindAllChildMeshes(UStaticMeshComponent*& _parentMesh)
{
	TArray<USceneComponent*> _allSceneCompos;
	_allSceneCompos = _parentMesh->GetAttachChildren();
	TArray<UStaticMeshComponent*> _allStaticMeshes;
	for (USceneComponent* _childCompo : _allSceneCompos)  // FOREACH DIDNT WORK HERE
	{
		UStaticMeshComponent* _mesh = Cast<UStaticMeshComponent>(_childCompo);
		_allStaticMeshes.Add(_mesh);

	}
	return _allStaticMeshes;
}

TArray<UStaticMeshComponent*> AProjectile::FindAllChildMeshes(UStaticMeshComponent*& _parentMesh, UStaticMeshComponent*& _parentMesh2, UStaticMeshComponent*& _parentMesh3)
{
	TArray<USceneComponent*> _allSceneCompos;
	_allSceneCompos = _parentMesh->GetAttachChildren(),_parentMesh2->GetAttachChildren(),
		_parentMesh3->GetAttachChildren();
	TArray<UStaticMeshComponent*> _allStaticMeshes;
	for (USceneComponent* _childCompo : _allSceneCompos)  // FOREACH DIDNT WORK HERE
	{
		UStaticMeshComponent* _mesh = Cast<UStaticMeshComponent>(_childCompo);
		_allStaticMeshes.Add(_mesh);

	}
	return _allStaticMeshes;
}

void AProjectile::ApplyHitEffect(TArray<UStaticMeshComponent*> _allStaticMeshesToHit)
{
	int _size = _allStaticMeshesToHit.Num();
	for (int i = 0; i < _size; i++)
	{
		_allStaticMeshesToHit[i]->SetSimulatePhysics(true);
		_allStaticMeshesToHit[i]->SetMassOverrideInKg(NAME_None, 0.01f);
	}
}

void AProjectile::ApplyHitEffect(UStaticMeshComponent* _staticMeshToAffect)
{
	_staticMeshToAffect->SetSimulatePhysics(true);
	_staticMeshToAffect->SetMassOverrideInKg(NAME_None, 0.01f);
}

void AProjectile::UpdateOverlapPhysics(AActor*& _actorToActivatePhysicsOn)
{
	meshCompo->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	//meshCompo->SetCollisionEnabled(initialCollisionSetting);
//	initialCollisionSetting = meshCompo->GetCollisionEnabled();

}







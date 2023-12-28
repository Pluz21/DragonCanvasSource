// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "BossEnemy.h"
#include "DragonCanvas/Actors/Projectile.h"
#include "DragonCanvas/MaterialCheckerComponent.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"

#include "DragonCanvas/Components/MoveComponent.h"

ABossEnemy::ABossEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	thirdMesh = CreateDefaultSubobject<UStaticMeshComponent>("thirdMesh");
	fourthMesh = CreateDefaultSubobject<UStaticMeshComponent>("fourthMesh");
	fifthMesh = CreateDefaultSubobject<UStaticMeshComponent>("fifthMesh");

	pawnSensor = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensor");

	baseMesh->SetupAttachment(root);
	secondMesh->SetupAttachment(root);
	thirdMesh->SetupAttachment(root);
	fourthMesh->SetupAttachment(root);
	fifthMesh->SetupAttachment(root);

	AddOwnedComponent(pawnSensor);
}

void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BossEnemyGameLogic();
	

}

void ABossEnemy::Init()
{
	onMeshLoss.AddDynamic(this, &ABossEnemy::PlayMeshLossSound);
	onAllMeshesLost.AddDynamic(this, &ABossEnemy::ManageDeathEvent);
	secondMesh->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnSecondMeshOverlapBegin);
	thirdMesh->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnThirdMeshOverlapBegin);
	fourthMesh->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnFourthMeshOverlapBegin);
	fifthMesh->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnFifthMeshOverlapBegin);

	pawnSensor->OnSeePawn.AddDynamic(this, &ABossEnemy::SetTarget);
	initialLocation = GetActorLocation();
	initialRotation = GetActorRotation();
	OverlapEventManager();  // AddDynamic overlap to all meshes
	SetAllMeshes();
	SetLifeSpan(500); 
	InitAI();

}



void ABossEnemy::InitAI()
{
	bossAIController = Cast<AAIController>(GetController());

}
void ABossEnemy::BossEnemyGameLogic()
{
	CheckAllMeshes();
	AIBehaviourLogic();
}
void ABossEnemy::CheckAllMeshes()
{
	if (allMeshes.Num() <= 0)
	{
		onAllMeshesLost.Broadcast();
	}

}
void ABossEnemy::AIBehaviourLogic()
{
	if (target)
	{
		ChasePlayer();
	}
	else
	{
		ReturnToInitialLocation();
	}
	Detect();
	CheckReturnedToInitialLocation();
	RotateToPlayer();
	CheckIsInRange();
}

void ABossEnemy::SetAllMeshes()
{
	allMeshes.Add(secondMesh); allMeshes.Add(thirdMesh); allMeshes.Add(fourthMesh); allMeshes.Add(fifthMesh);

}

void ABossEnemy::RemoveMesh(int _index)
{
	allMeshes.RemoveAt(_index);
}

void ABossEnemy::PlayMeshLossSound()
{
	PlaySound(onMeshLossSound);

}

void ABossEnemy::PlayDeathSound()
{
	PlaySound(onBossDeathSound);
}

void ABossEnemy::ManageDeathEvent()
{
	baseMesh->SetSimulatePhysics(true);
	baseMesh->SetMassOverrideInKg(NAME_None,2000);

	moveCompo->SetChaseSpeed(0);
	PlayDeathSound();
	onAllMeshesLost.Clear();

	SetLifeSpan(3);
	UE_LOG(LogTemp, Warning, TEXT("ManageDeath Event called"));

}

void ABossEnemy::ManageAllMeshesOverlap(UPrimitiveComponent* _overlappedCompo, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	int _meshIndex = INDEX_NONE;
	int _size = allMeshes.Num();
	for (int i = 0; i < _size; i++)
	{
		if (allMeshes[i] == _overlappedCompo)
		{
			_meshIndex = i;
			break;
		}
	}
}

void ABossEnemy::OverlapEventManager()
{
	int _size = allMeshes.Num();
	for (int i = 0; i < _size; i++)
	{
		UStaticMeshComponent* _overlappedMesh = allMeshes[i];
		if (!_overlappedMesh)return;
		
		FMeshData meshData;
		meshData.canBeDestroyed = false;
		allMeshData.Add(meshData);
		_overlappedMesh->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::ManageAllMeshesOverlap);
		
	}
}


void ABossEnemy::OnSecondMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleMeshOverlap(OtherActor, 0);// Since we remove the index after hitting
									//	we can always call the first 
}

void ABossEnemy::OnThirdMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleMeshOverlap(OtherActor, 0); 
}

void ABossEnemy::OnFourthMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleMeshOverlap(OtherActor, 0);

}

void ABossEnemy::OnFifthMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	HandleMeshOverlap(OtherActor, 0);

}

void ABossEnemy::HandleMeshOverlap(AActor* _otherActor, int _meshIndex)
{
	AProjectile* _projectileRef = Cast<AProjectile>(_otherActor);
	if (!materialCheckerCompo || !_projectileRef)return;
	if (materialCheckerCompo->GetAllMatsSize() <= 0) return;
	// INDEX OF ALLMATS IS HARD CODED
	// TO DO - Replace the function ManageBossEnemyHit in 
	// projectile.cpp with ApplyMaterialToMatchingMesh?
	// FindChildMeshes Function should be in Enemy.cpp
	if (_projectileRef->GetCurrentProjectileMat() == materialCheckerCompo->allMatsToCheck[_meshIndex])// testing with the fire arm
	{
		canDestroySecondMesh = true;
		_projectileRef->GetOnCorrectProjectileMeshOverlap().Broadcast(this);
		UE_LOG(LogTemp, Warning, TEXT("%i Mesh Overlap Event Triggered!"), _meshIndex);
	}// Broadcast
}



void ABossEnemy::ApplyMaterialToMatchingMesh(UMaterialInterface* _matToApply)
{
	////AProjectile* _projectileRef = Cast<AProjectile>(OtherActor);
	//UMaterialCheckerComponent* matChecker = GetMaterialCheckerComponent();

	//if (!matChecker)
	//{
	//	// Handle the case where matChecker is not available.
	//	return;
	//}

	//TArray<UStaticMeshComponent*> allMeshes = GetAllMeshes();
	//int32 size = matChecker->GetAllMatsSize();

	//for (int32 i = 0; i < size; ++i)
	//{
	//	if (i < allMeshes.Num() && i < matChecker->allMatsToCheck.Num())
	//	{
	//		UMaterialInterface* matFromChecker = matChecker->allMatsToCheck[i];
	//		UStaticMeshComponent* currentMesh = allMeshes[i];

	//		if (matToApply == matFromChecker && currentMesh->GetMaterial(0) != matFromChecker)
	//		{
	//			TArray<UStaticMeshComponent*> allChildMeshes = FindAllChildMeshes(currentMesh);

	//			SetMeshMaterialAtIndex(allMeshes, i, matToApply);
	//			SetMeshMaterialChildIncluded(allChildMeshes, matToApply);

	//			ApplyHitEffect(currentMesh);
	//			ApplyHitEffect(allChildMeshes[0]);  // Assuming there's only one child mesh, adjust as needed.

	//			GetOnHit().Broadcast();
	//			RemoveMesh(i);
	//			matChecker->allMatsToCheck.RemoveAt(i);
	//			GetOnMeshLoss().Broadcast();

	//			--i;
	//		}
	//	}
	//	else
	//	{
	//		// Handle the case where index is out of bounds.
	//		return;
	//	}
	//}
}

void ABossEnemy::ChasePlayer()
{
		moveCompo->BossChasePlayer();
		moveCompo->SetChaseSpeed(0.2f);

}
void ABossEnemy::ReturnToInitialLocation()
{
		moveCompo->MoveToLocation(initialLocation);
		moveCompo->SetChaseSpeed(3);
}
void ABossEnemy::SetTarget(APawn* _pawn)
{
	target = _pawn;
	lastTarget = _pawn;
	UE_LOG(LogTemp, Warning, TEXT("Target is : %s"), *_pawn->GetName());
	onTargetSet.Broadcast(true);
}
void ABossEnemy::Chase()
{
	return;
}


void ABossEnemy::Detect()
{
	if (!target)return;
	const bool _canSee = pawnSensor->CouldSeePawn(target);
	if (!_canSee)
		target = nullptr;
}
void ABossEnemy::CheckReturnedToInitialLocation()
{
	float _distance = FVector::Dist(GetActorLocation(), initialLocation);
	//	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), _distance);
	if (_distance >= 170)
	{
		canRotateTowardsPlayer = false;

	}
	else
	canRotateTowardsPlayer = true;


}

void ABossEnemy::CheckIsInRange()
{
	if (!target) return;
	float _distance = FVector::Dist(GetActorLocation(), target->GetActorLocation());
	if (_distance <= range)
		onEnterRange.Broadcast();

}

void ABossEnemy::RotateToPlayer()
{
	if (!lastTarget)return;
	if (!canRotateTowardsPlayer)return;
	float _speed = GetWorld()->DeltaTimeSeconds * rotateBackSpeed;
	FVector _directionToPlayer = lastTarget->GetActorLocation() - GetActorLocation();
	FRotator _rotationToPlayer = _directionToPlayer.Rotation();
	FRotator _interpolatedRotation = FMath::RInterpTo(GetActorRotation(), _rotationToPlayer, _speed , 10.f);
	SetActorRotation(_interpolatedRotation);

}








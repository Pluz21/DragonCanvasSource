// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "BossEnemy.h"
//#include "DragonCanvas/Components/MoveComponent.h"

// Sets default values
ABossEnemy::ABossEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//materialCheckerCompo2 = CreateDefaultSubobject<UMaterialCheckerComponent>("MaterialChecker2");
	thirdMesh = CreateDefaultSubobject<UStaticMeshComponent>("thirdMesh");
	fourthMesh = CreateDefaultSubobject<UStaticMeshComponent>("fourthMesh");
	fifthMesh = CreateDefaultSubobject<UStaticMeshComponent>("fifthMesh");

	baseMesh->SetupAttachment(root);
	secondMesh->SetupAttachment(root);
	thirdMesh->SetupAttachment(root);
	fourthMesh->SetupAttachment(root);
	fifthMesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

// Called every frame
void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (allMeshes.Num() <= 0)
		onAllMeshesLost.Broadcast();


}

void ABossEnemy::Init()
{
	onMeshLoss.AddDynamic(this, &ABossEnemy::PlayMeshLossSound);
	onAllMeshesLost.AddDynamic(this, &ABossEnemy::ManageDeathEvent);
	SetAllMeshes();

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
	UE_LOG(LogTemp, Warning, TEXT("ManageDeath Event called"));

}


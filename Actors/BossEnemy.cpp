// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "BossEnemy.h"

// Sets default values
ABossEnemy::ABossEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	materialCheckerCompo2 = CreateDefaultSubobject<UMaterialCheckerComponent>("MaterialChecker2");
	thirdMesh = CreateDefaultSubobject<UStaticMeshComponent>("thirdMesh");
	baseMesh->SetupAttachment(root);
	secondMesh->SetupAttachment(root);
	thirdMesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


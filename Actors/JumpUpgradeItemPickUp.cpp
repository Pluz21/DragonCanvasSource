// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Actors/JumpUpgradeItemPickUp.h"
#include "DragonCanvas/Actors/Dragon.h"

#include "DragonCanvas/Components/UpgradeComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AJumpUpgradeItemPickUp::AJumpUpgradeItemPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJumpUpgradeItemPickUp::BeginPlay()
{
	Super::BeginPlay();
	JumpUpgradeInit();
}


// Called every frame
void AJumpUpgradeItemPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJumpUpgradeItemPickUp::JumpUpgradeInit()
{
	UE_LOG(LogTemp, Warning, TEXT("Upgrade init called"));
	
	//onInit.AddDynamic(this, &AJumpUpgradeItemPickUp::PlayAudio);
//	onOverlapFinished.AddDynamic(this, &AJumpUpgradeItemPickUp::StopPlayAudio);
	//onInit.Broadcast();

}

void AJumpUpgradeItemPickUp::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	Super::ManageOverlap(_overlapped, _overlap);

	ADragon* _dragonRef = Cast<ADragon>(_overlap);
	if (!_dragonRef || !_dragonRef->upgradeComponent)return;
	_dragonRef->upgradeComponent->SetHasJumpUpgrade(true);
	

}

void AJumpUpgradeItemPickUp::StopPlayAudio()
{
	/*hummingSound = nullptr;
	
	onOverlapFinished.Clear();*/
	UE_LOG(LogTemp, Warning, TEXT("stop audio called"));
}

void AJumpUpgradeItemPickUp::PlayAudio()
{
	UE_LOG(LogTemp, Warning, TEXT("Play audio called"));

	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), hummingSound, GetActorLocation());
}


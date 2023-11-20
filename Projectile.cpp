// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Dragon.h"

#include "CustomGameMode.h"
#include "ProjectileManager.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "MoveComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Projectile Constructor!"));

	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("mymesh");
	meshCompo->SetupAttachment(RootComponent);
	moveCompo = CreateDefaultSubobject<UMoveComponent>("moveCompo");
	//coneLineTraceCompo = CreateDefaultSubobject<UConeLineTrace>("coneTraceCompohere");
	AddOwnedComponent(moveCompo);
	//AddOwnedComponent(coneLineTraceCompo);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AProjectile::ManageOverlap);
	onTargetReached.AddDynamic(this, &AProjectile::SelfDestruct);
	onCanMove.AddDynamic(this, &AProjectile::FindEndLocation);
	Init();

}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	deltaSeconds = GetWorld()->DeltaTimeSeconds;
	CheckDistance(targetLocation);
	SelfMove(forwardVector);
	moveCompo->Rotate();
	// or call 
	//moveCompo->Move();

}

void AProjectile::Init()
{
	gameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	if (!gameMode)return;
	projectileManager = gameMode->GetProjectileManager();
	if (projectileManager)return;
	projectileManager->AddItem(this);

	actorSpawnLocation = GetActorLocation();
	forwardVector = GetActorForwardVector();
	//SetLifeSpan(lifeSpan);
	moveSpeed = moveCompo->GetMoveSpeed(); // MoveSpeed will always be set through the component

}

void AProjectile::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	

	if (_overlap && (_overlap != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAPPING"));
		onTargetReached.Broadcast(); // Calls SelfDestruct
	}
	else 
		UE_LOG(LogTemp, Warning, TEXT("FAILED OVERLAPCALL"));


	if (_overlap->ActorHasTag("DestroyProjectileAndSelfDestruct"))
	{
		 _overlap->Destroy();
		onTargetReached.Broadcast(); // Calls SelfDestruct
	}
	if (_overlap->ActorHasTag("CanMove"))
	{
		FVector _overlapLocation = _overlap->GetActorLocation();
		FVector _displacedLocation = _overlapLocation + forwardVector * 200;
		_overlap->SetActorLocation(_displacedLocation);
	}
	

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
	//CallLineTraceDisplacement();
	projectileManager->RemoveItem(this);
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("DESTRUCTION"));

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




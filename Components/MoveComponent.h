//Copyright � 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveComponent.generated.h"
class AProjectile;
class ADragon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONCANVAS_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();
	UPROPERTY(EditAnywhere)
	float deltaSeconds;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> ownerRef;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ADragon> playerRef;
	

	//Movement variables
	UPROPERTY(EditAnywhere)
	float chaseSpeed = 1.f;
	UPROPERTY(EditAnywhere)
	float moveSpeed = 100.f;
	UPROPERTY(EditAnywhere)
	float rotateSpeed = 2000.f;   //Projectile rotateSpeed

	UPROPERTY(EditAnywhere)
	float bossHeightOffset = 250;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Init();

	void MoveAndFollow();
	void SelfMove(const FVector& _actorForwardVector);
	void ChasePlayer();
	void BossChasePlayer();
	void Rotate();

	float GetMoveSpeed() { return moveSpeed; }
	void SetMoveSpeed(float _newMoveSpeed) { moveSpeed = _newMoveSpeed; }
	void SetChaseSpeed(float _newChaseSpeed) { chaseSpeed = _newChaseSpeed; }
	ADragon* GetChaseTarget() { return playerRef; }
		
};

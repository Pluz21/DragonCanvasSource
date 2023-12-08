//Copyright © 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"
class UMoveComponent;
class ADragon;
UCLASS()
class DRAGONCANVAS_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> root;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> baseMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> secondMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMoveComponent> moveCompo;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<ADragon> playerRef;
	
	UPROPERTY(EditAnywhere)
	float minDistanceAllowed = 150.f; 
	UPROPERTY(EditAnywhere)
	int damageToApply = 1;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init();

	bool CheckDistance();

	UFUNCTION(BlueprintCallable)
	void SelfDestroy();

	UFUNCTION(BlueprintCallable)
	void ApplyDamage();
};

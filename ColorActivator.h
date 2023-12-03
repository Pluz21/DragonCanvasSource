// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileTriggerComponent.h"
#include "ColorActivator.generated.h"
class AProjectile;
class ADragon;
class APickUps;
UCLASS()
class DRAGONCANVAS_API AColorActivator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorActivator();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> dragonProjectileRef;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> root;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileTriggerComponent> triggerCompo;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> projectileMeshRef;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> projectileMatRef;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> matToApply;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void ManageOverlap(AActor* _overlapped, AActor* _overlap);
	void GiveColor();

	void Init();
};

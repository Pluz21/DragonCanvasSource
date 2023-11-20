// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorActivator.generated.h"
class AProjectile;
class ADragon;
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
	TObjectPtr<UStaticMeshComponent> meshCompo;

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
	void ManageOverlap(AActor* _overlap, AActor* _overlapped);
	void GiveColor();

	void Init();
};

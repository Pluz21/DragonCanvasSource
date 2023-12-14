// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DragonCanvas/Components/ProjectileTriggerComponent.h"
#include "ColorActivator.generated.h"
class AProjectile;
class ADragon;
class APickUps;
class AColorActivator;
class AProjectileManager;
class ACustomGameMode;

UCLASS()
class DRAGONCANVAS_API AColorActivator : public AActor
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMaterialReceived, UMaterialInterface*, matReceived);
	UPROPERTY()
	FMaterialReceived onMaterialReceived;
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorActivator();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> dragonProjectileRef;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> root;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> baseMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> secondMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UProjectileTriggerComponent> triggerCompo;

	//Projectile 
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> projectileMeshRef;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> projectileMatRef;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInstance> matToApply; // This is the one to add to the projectile manager
	UPROPERTY(EditAnywhere)
	TObjectPtr<ACustomGameMode> gameMode;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AProjectileManager> projectileManager;

	UPROPERTY(EditAnywhere)
	bool isSpawner = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Init();
	void InitGameMode();
	UFUNCTION()
	virtual void ManageOverlap(AActor* _overlapped, AActor* _overlap);
	void GiveColor();
	UFUNCTION()
	void Test(UMaterialInterface* _mat);
	UFUNCTION()
	void ApplyMatToApply(UMaterialInterface* _mat);
	void SetIsSpawner(bool _value) { isSpawner = _value; }
	bool GetIsSpawner() { return isSpawner; }
	UProjectileTriggerComponent* GetTriggerCompo() { return triggerCompo; }
	UFUNCTION(BlueprintCallable,BlueprintPure)
	UMaterialInterface* GetMatToApply() { return matToApply; }
	UFUNCTION(BlueprintCallable)
	void SetMatToApply(UMaterialInstance* _mat) { matToApply = _mat; }
	



};

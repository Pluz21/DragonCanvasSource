//Copyright � 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorActivatorProjectile.generated.h"

class UMaterialCheckerComponent; 
UCLASS()
class DRAGONCANVAS_API AColorActivatorProjectile : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> matToCheck;
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> allMatsToCheck;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialCheckerComponent> materialChecker;
	UPROPERTY(EditAnywhere)
	float InterpolationSpeed = 0.5f;
	UPROPERTY(EditAnywhere)
	float TargetParameterValue = 1.0f;
	
	UPROPERTY(EditAnywhere)
	bool canCheckMat = false;


public:	
	// Sets default values for this actor's properties
	AColorActivatorProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime);
	UFUNCTION()
	void ManageOverlap(AActor* overlapped, AActor* _overlap);
	void ReceiveColor(AActor* _projectile);
};

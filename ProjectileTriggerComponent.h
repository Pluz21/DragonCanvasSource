// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileTriggerComponent.generated.h"

class ADragon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONCANVAS_API UProjectileTriggerComponent : public UActorComponent
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSnapEvent, AActor*, actorSnapped);
	UPROPERTY()
	FSnapEvent onSnap;

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileTriggerComponent();
	UPROPERTY()
	TObjectPtr<ADragon> dragonRef; 
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> mat;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> targetMat;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void SnapTarget(AActor*& _targetActor);
	void Init();
	UFUNCTION()
	void Test(AActor* _snappedActor);
	bool MaterialChecker(AActor*& _targetToCheck);
	UMaterialInterface* GetMatInterface() { return mat; }
	UFUNCTION()
	FSnapEvent OnSnap() { return onSnap; }
};

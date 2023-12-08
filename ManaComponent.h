// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONCANVAS_API UManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManaComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxMana = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentMana = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float manaRegenRate = 5;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float manaCost = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isOutOfMana = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init();

	UFUNCTION(BlueprintCallable)
	void IdleManaRegen();
	UFUNCTION(BlueprintCallable)
	void AddMana(float _value);
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentMana() { return currentMana; }
	UFUNCTION(BlueprintCallable)
	float GetManaRegenRate() { return manaRegenRate; }
	UFUNCTION(BlueprintCallable)
	void SetManaRegenRate(float _newRegenRate) { manaRegenRate = _newRegenRate; }

	UFUNCTION(BlueprintCallable)
	void SetOutOfMana();
};

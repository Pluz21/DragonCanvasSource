// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONCANVAS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	//Health variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxHealth = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int currentHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isDead = false;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Init();

	UFUNCTION(BlueprintCallable)
	void AddHealth(int _value);
		
	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth() { return currentHealth; }

	UFUNCTION(BlueprintCallable)
	void SetIsDead(bool _value);
};

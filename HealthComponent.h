//Copyright © 2023 Pluz21(TVL).All rights reserved.
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

	// Colors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor currentColor = FLinearColor(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor highHealthColor = FLinearColor(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor midHealthColor = FLinearColor(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor lowHealthColor = FLinearColor(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor criticalHealthColor = FLinearColor(0,0,0);

	

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
	void SetMaxHealth(int _value) { maxHealth = _value; }

	UFUNCTION(BlueprintCallable)
	void SetIsDead(bool _value);
	
	UFUNCTION(BlueprintCallable)
	void SetHealthColor();
};

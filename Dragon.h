// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Dragon.generated.h"

class AProjectile;
class UAttackComponent;
class UConeLineTrace;
UCLASS()
class DRAGONCANVAS_API ADragon : public ACharacter
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLineTraceCreated);
	UPROPERTY(EditAnywhere)
	FLineTraceCreated onLineTraceCreated;
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADragon();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWorld> world;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> camera;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConeLineTrace> coneTraceCompo;

	UPROPERTY(EditAnywhere)
	TArray<AProjectile*> allProjectiles;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> spawnPoint;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APlayerController> playerController;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAttackComponent> attackCompo;
	// inputs
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> inputToMove;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> inputToRotateYaw;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> inputToPitch;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> inputToAction;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> mappingContext = nullptr;
	/*UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> projectileToSpawn;*/

	//input variables

	UPROPERTY(EditAnywhere)
	float moveSpeed = 500.f;
	UPROPERTY(EditAnywhere)
	float rotateSpeed = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float forwardInputValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rightInputValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotateInputValue;

	// spawn variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "10", ClampMin = "10", UIMax = "100", ClampMax = "100"))
	float maxAmmo = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector spawnPointLocation;

	UPROPERTY(EditAnywhere)
	FVector targetLocation; 
	
	//camera
	UPROPERTY(EditAnywhere)
	float maxCameraPitch = 20;
	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Init();
	void InitInput();

	//Inputs
	void Move(const FInputActionValue& _value);
	void RotateYaw(const FInputActionValue& _value);
	void RotatePitch(const FInputActionValue& _value);
	void Action();
	//Dragon actions
	UFUNCTION() void FireBreath();
	// camera
	void SetMaximumPitch();

	// attack compo needs
	FVector  GetSpawnLocation() { return spawnPointLocation; }
	
	//Projectile
	float GetCurrentAmmo() { return currentAmmo; }

	//Debug
	void DebugText(FString _string);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

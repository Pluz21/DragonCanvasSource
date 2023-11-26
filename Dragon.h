// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Dragon.generated.h"

class UGrabber;
class ACustomGameMode;
class AProjectileManager;
class AProjectile;
UCLASS()
class DRAGONCANVAS_API ADragon : public ACharacter
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLineTraceCreated);
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileReachedTarget, UWorld*, world, FHitResult, result);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectileReachedTarget);
	


	UPROPERTY(EditAnywhere)
	FLineTraceCreated onLineTraceCreated;
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FProjectileReachedTarget onProjectileTargetReached;
	// Sets default values for this character's properties
	ADragon();

	UPROPERTY(EditAnywhere)
	TObjectPtr<ACustomGameMode> gameMode;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AProjectileManager> projectileManager;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWorld> world;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> camera;

	UPROPERTY(EditAnywhere)
	TArray<AProjectile*> allProjectiles;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> spawnPoint;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APlayerController> playerController;
	UPROPERTY(EditAnywhere)
	FHitResult hitResult;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGrabber> grabber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPhysicsHandleComponent> physicsHandle;


	
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
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> projectileToSpawn;

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
	float launchTime;
	UPROPERTY(EditAnywhere)
	FVector spawnedInitialLocation;
	UPROPERTY(EditAnywhere)
	FVector targetLocation; 
	UPROPERTY(EditAnywhere)
	FVector locationOnLineTraceSpawn; 
	
	//camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minPitchRotation = -65;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxPitchRotation = 40;
	
	
	//Debug
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> _coneTraceChannel;


	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float sphereTracedistance = 3000;

	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float coneTraceRadius = 300;
	
	UPROPERTY(EditAnywhere)
	float minDistanceToSelfDestruct;
	UPROPERTY(EditAnywhere)
	bool canSelfDestruct = false;
	
	UPROPERTY(EditAnywhere)
	float currentTime = 0;
	UPROPERTY(EditAnywhere)
	float maxTime = 2;
	
	UPROPERTY(EditAnywhere)
	bool canStartAlphaCount = false;

	//Actions
	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float lineTraceEffectMultiplier = 200;
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Init();
	void InitInput();

	void InitCameraLimit();

	//Inputs
	void Move(const FInputActionValue& _value);
	void RotateYaw(const FInputActionValue& _value);
	void RotatePitch(const FInputActionValue& _value);
	void Action();
	//Dragon actions

	//Debug
	void SphereTrace();
	// attack compo needs
	
	//Projectile
	float GetCurrentAmmo() { return currentAmmo; }

	//Debug
	void DebugText(FString _string);

public:	
	UFUNCTION() void FireBreath();
	// Called every frame
	FVector  GetSpawnLocation() { return spawnPoint->GetComponentLocation(); }
	FVector GetProjectileTargetLocation() { return targetLocation; }
	float GetSphereTraceDistance() { return sphereTracedistance; }
	float GetMinDistanceToSelfDestruct() { return minDistanceToSelfDestruct; }
	TArray<AProjectile*> GetAllProjectiles() { return allProjectiles; }
	TSubclassOf<AProjectile>GetProjectileToSpawn() { return projectileToSpawn; }

	UFUNCTION() void LineTraceDisplacement(UWorld* _world, const FHitResult& _hitResult);
	UFUNCTION() void StartLineTraceAction();
	
	UFUNCTION()
	FProjectileReachedTarget& GetOnProjectileReachedTarget() { return onProjectileTargetReached; }
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateMinDistanceToSelfDestruct();

	void SetStartAlphaCount();
	float IncreaseTime(float _current, float _max);
	FVector Lerperoo(const FVector& _start, const FVector& _end);
};

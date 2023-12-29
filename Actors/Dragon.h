//Copyright � 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Dragon.generated.h"

class ACustomGameMode;
class UGrabber;
class UHealthComponent;
class UManaComponent;
class UAttackComponent;

class AProjectileManager;
class AProjectile;

UCLASS()
class DRAGONCANVAS_API ADragon : public ACharacter
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLineTraceCreated);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectileShotEvent);
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProjectileReachedTarget, UWorld*, world, FHitResult, result);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectileReachedTarget);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentProjectileMatEvent, UMaterialInterface*, mat);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenMenuEvent);

	UPROPERTY(BlueprintAssignable)
	FCurrentProjectileMatEvent onCurrentProjectileMatReceived;

	UPROPERTY()
	FProjectileShotEvent onProjectileShot;

	UPROPERTY()
	FLineTraceCreated onLineTraceCreated;
	
	UPROPERTY()
	FProjectileReachedTarget onProjectileTargetReached;
	
	UPROPERTY(BlueprintAssignable)
	FOpenMenuEvent onMenuOpened;

	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADragon();
	UPROPERTY()
	TObjectPtr<UWorld> world;

	UPROPERTY()
	TObjectPtr<ACustomGameMode> gameMode;
	UPROPERTY()
	TObjectPtr<AProjectileManager> projectileManager;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> spawnPoint;
	UPROPERTY()
	TObjectPtr<APlayerController> playerController;

#pragma region Components

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAttackComponent> attackCompo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UGrabber> grabber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPhysicsHandleComponent> physicsHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UHealthComponent> healthCompo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UManaComponent> manaCompo;

#pragma endregion Components 


	
	UPROPERTY(EditAnywhere)
	FHitResult hitResult;


#pragma region Inputs
	// inputs Movement
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputMappingContext> mappingContext = nullptr;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputMappingContext> menuMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToMove;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToRotateYaw;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToPitch;
	// inputs Movement
	// inputs Interactions
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToAction;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToScrollUpSelectProjectile;
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToScrollDownSelectProjectile;
	// inputs Interactions
	// inputs Menu
	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UInputAction> inputToOpenMenu;
	
	// inputs Menu

	//input variables

	UPROPERTY(EditAnywhere)
	float moveSpeed = 500.f;
	UPROPERTY(EditAnywhere)
	float rotateSpeed = 20.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inputs")
	float forwardInputValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inputs")
	float rightInputValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inputs")
	float rotateInputValue;

#pragma endregion Inputs

#pragma region Spawn
	// spawn variables
	UPROPERTY(EditAnywhere, Category = "ProjectileSelection")
	TSubclassOf<AProjectile> projectileToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "ProjectileSelection")
	TObjectPtr<UMaterialInterface> currentProjectileMat;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "ProjectileSelection")
	TArray<UMaterialInterface*> allProjectileMats;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ProjectileSelection")
	int currentProjectileIndex = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector spawnPointLocation;

	UPROPERTY(VisibleAnywhere)
	FVector spawnedInitialLocation;

#pragma endregion Spawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "10", ClampMin = "10", UIMax = "100", ClampMax = "100"))
	float maxAmmo = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currentAmmo;


	UPROPERTY(EditAnywhere, Category = "LineTrace")
	FVector targetLocation;
	UPROPERTY(EditAnywhere, Category = "LineTrace")
	FVector locationOnLineTraceSpawn;

	//camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Camera Settings")
	float minPitchRotation = -65;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Camera Settings")
	float maxPitchRotation = 40;


	//Debug
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> _coneTraceChannel;


	// Audio
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> projectileSound;

	//Not in use
	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float lineTraceEffectMultiplier = 200;
	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float sphereTracedistance = 3000;

	UPROPERTY(EditAnywhere, Category = "LineTrace")
	float coneTraceRadius = 300;

	UPROPERTY(EditAnywhere)
	float minDistanceToSelfDestruct;
	UPROPERTY(EditAnywhere)
	bool canSelfDestruct = false;



protected:
	virtual void BeginPlay() override;
	void Init();
	void InitInput();
	void InitEvents();
	UFUNCTION()
	void UpdateCurrentProjectileMat(UMaterialInterface* _mat);

	//Inputs
	void Move(const FInputActionValue& _value);
	void RotateYaw(const FInputActionValue& _value);
	void RotatePitch(const FInputActionValue& _value);
	void Action();
	void ScrollUpSelectProjectile();
	void ScrollDownSelectProjectile();
	void UpdateProjectileMaterial();

	// Interface 
	void OpenMainMenu();
	UFUNCTION()
	void TestMatReceived(UMaterialInterface* _matReceived);
	//Dragon actions
	//Debug
	void SphereTrace();
	// attack compo needs

	//Projectile
	float GetCurrentAmmo() { return currentAmmo; }

	//Debug
	void DebugText(FString _string);

	// Audio
	void PlaySound(USoundBase* _audioToPlay);
	UFUNCTION()
	void PlayProjectileSound();

public:
	UFUNCTION() void FireBreath();
	// Called every frame
	FVector  GetSpawnLocation() { return spawnPoint->GetComponentLocation(); }
	FVector GetProjectileTargetLocation() { return targetLocation; }
	float GetSphereTraceDistance() { return sphereTracedistance; }
	float GetMinDistanceToSelfDestruct() { return minDistanceToSelfDestruct; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<AProjectile>GetProjectileToSpawn() { return projectileToSpawn; }

	UFUNCTION() void LineTraceDisplacement(UWorld* _world, const FHitResult& _hitResult);
	UFUNCTION() void StartLineTraceAction();

	// Event getters
	UFUNCTION()
	FProjectileReachedTarget& GetOnProjectileReachedTarget() { return onProjectileTargetReached; }
	UFUNCTION()
	FCurrentProjectileMatEvent& GetOnCurrentProjectileMatReceived() { return onCurrentProjectileMatReceived; }
	UFUNCTION()
	FOpenMenuEvent& GetOnMenuOpened() { return onMenuOpened; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentProjectileIndex() { return currentProjectileIndex; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UMaterialInterface*> GetAllProjectileMats() { return allProjectileMats; };
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetAllProjectileMatsSize() { return allProjectileMats.Num(); };

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void UpdateMinDistanceToSelfDestruct();

	void SetStartAlphaCount();
	float IncreaseTime(float _current, float _max);
	FVector Lerperoo(const FVector& _start, const FVector& _end);
};

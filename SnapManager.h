//Copyright © 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnapManager.generated.h"

UCLASS()
class DRAGONCANVAS_API ASnapManager : public AActor
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSnapDelegate,
		AActor*, snappedActor);
	UPROPERTY()
	FSnapDelegate onSnap;

	GENERATED_BODY()

	
	
public:	
	// Sets default values for this actor's properties
	ASnapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Snap")
	void NotifySnap(AActor* _snappedActor);
	UFUNCTION()
	FSnapDelegate& OnSnap() { return onSnap; }

};

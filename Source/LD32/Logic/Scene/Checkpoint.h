// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

/**
 * 
 */
UCLASS()
class LD32_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:
	ACheckpoint(const class FObjectInitializer &objectInitializer);

protected:

	UFUNCTION()
	void OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:

	UPROPERTY(VisibleAnyWhere, Category = Behaviour)
	class UBoxComponent *collider;	
};

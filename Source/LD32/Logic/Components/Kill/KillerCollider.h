// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "KillerCollider.generated.h"

/**
 * 
 */
UCLASS()
class LD32_API UKillerCollider : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	UKillerCollider(const class FObjectInitializer &objectInitializer);


protected:
	UFUNCTION()
	virtual void OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	
	
};

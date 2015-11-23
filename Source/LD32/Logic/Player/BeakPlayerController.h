// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BeakPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LD32_API ABeakPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABeakPlayerController(const class FObjectInitializer &objectInitializer);

	virtual void BeginPlay() override;

	void saveCheckpoint(FVector position){positionCheckpoint = position;}

	void loadCheckpoint();
	

protected:

private:
	
	FVector positionCheckpoint;
	
};

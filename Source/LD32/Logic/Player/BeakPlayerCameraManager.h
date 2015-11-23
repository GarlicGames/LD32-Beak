// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "BeakPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class LD32_API ABeakPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ABeakPlayerCameraManager(const class FObjectInitializer &objectInitializer);

	virtual void BeginPlay() override;

	void init();

protected:

	virtual void Tick(float deltaTime) override;


private:

	class ACameraActor *playerCamara;

	AActor *target;

	float offsetMoveCameraXRight;
	float offsetMoveCameraXLeft;

	float offsetMoveCameraZUp;
	float offsetMoveCameraZDown;

	float minVelInter;

	
	
	
};

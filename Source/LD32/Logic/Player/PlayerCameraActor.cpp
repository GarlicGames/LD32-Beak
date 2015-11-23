// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "PlayerCameraActor.h"


APlayerCameraActor::APlayerCameraActor(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer)
{

	//CameraComponent->RelativeLocation = FVector(-135, 0, 65);
	UCameraComponent *camera(GetCameraComponent());
	camera->PostProcessSettings.bOverride_AutoExposureMaxBrightness = true;
	camera->PostProcessSettings.bOverride_AutoExposureMinBrightness = true;
	camera->PostProcessSettings.AutoExposureMaxBrightness = 1.f;
	camera->PostProcessSettings.AutoExposureMinBrightness = 1.f;
	camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	//camera->ProjectionMode = ECameraProjectionMode::Perspective;
	camera->OrthoWidth = 1800;

}


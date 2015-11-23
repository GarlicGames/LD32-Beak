// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "BeakPlayerController.h"

#include "BeakPlayerCameraManager.h"

#include "Logic/MainCharacter.h"

ABeakPlayerController::ABeakPlayerController(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer)

{
	PlayerCameraManagerClass = ABeakPlayerCameraManager::StaticClass();

}
void ABeakPlayerController::BeginPlay()
{
	Super::BeginPlay();

	positionCheckpoint = GetPawn()->GetActorLocation();
}

void ABeakPlayerController::loadCheckpoint()
{
	AMainCharacter *character = dynamic_cast<AMainCharacter*>(GetPawn());

	ABeakPlayerCameraManager *camera = dynamic_cast<ABeakPlayerCameraManager*>(PlayerCameraManager);
	if (character && camera) {
		character->SetActorLocation(positionCheckpoint);
		camera->init();
		character->reStart();

	}

}


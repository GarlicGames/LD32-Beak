// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "LD32GameMode.h"

#include "Logic/Player/BeakPlayerController.h"

ALD32GameMode::ALD32GameMode(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprints/BP_Character.BP_Character_C'"));
	if (PlayerPawnObject.Class != nullptr) {
		DefaultPawnClass = PlayerPawnObject.Class;
	}

	PlayerControllerClass = ABeakPlayerController::StaticClass();



}

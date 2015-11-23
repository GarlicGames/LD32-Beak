// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "Checkpoint.h"

#include <Logic/Physics/Physics.h>

#include "Logic/Player/BeakPlayerController.h"

#include "Logic/MainCharacter.h"

ACheckpoint::ACheckpoint(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	collider(objectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "collider"))
{
	RootComponent = collider;

	collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapEnter);

	collider->SetCollisionProfileName(TRANSFORMABLE_PROFILE);
}

void ACheckpoint::OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ABeakPlayerController *player = dynamic_cast<ABeakPlayerController*>(GetWorld()->GetFirstPlayerController());
	AMainCharacter *character = nullptr;
	if (OtherActor) {
		character = dynamic_cast<AMainCharacter*>(OtherActor);
	}
	if (player && character && character->isAlive()) {
		player->saveCheckpoint(this->GetTransform().GetLocation());
		collider->OnComponentBeginOverlap.RemoveDynamic(this, &ACheckpoint::OnOverlapEnter);
	}
}
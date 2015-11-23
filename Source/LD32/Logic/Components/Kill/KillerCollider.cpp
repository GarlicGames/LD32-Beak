// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "KillerCollider.h"


#include "Logic/MainCharacter.h"

#include <Logic/Physics/Physics.h>

UKillerCollider::UKillerCollider(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer)
{
	this->OnComponentBeginOverlap.AddDynamic(this, &UKillerCollider::OnOverlapEnter);

	this->SetCollisionProfileName(TRANSFORMABLE_PROFILE);
}

void UKillerCollider::OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) {
		AMainCharacter *character = dynamic_cast<AMainCharacter*>(OtherActor);
		if (character) {
			character->kill();
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "ConveyorBelt.h"

#include <Logic/Physics/Physics.h>

#include <Paper2DClasses.h>

#include "Logic/MainCharacter.h"

//const TCHAR* LOG_CONVEYORBELT = _T("AConveyorBelt ->");

// Sets default values
AConveyorBelt::AConveyorBelt(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	sprite(objectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, "Sprite")),
	collider(objectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "ConveyorBeltCollider")),
	direction(-1),
	velocity(200)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = sprite;

	collider->AttachParent = RootComponent;

	collider->OnComponentBeginOverlap.AddDynamic(this, &AConveyorBelt::OnOverlapEnter);
	collider->OnComponentEndOverlap.AddDynamic(this, &AConveyorBelt::OnOverlapExit);

	collider->SetCollisionProfileName(TRANSFORMABLE_PROFILE);

	

}

// Called when the game starts or when spawned
void AConveyorBelt::BeginPlay()
{
	Super::BeginPlay();

	float playRate = (velocity *0.2f) / 200;

	sprite->SetPlayRate(playRate);

	sprite->PlayFromStart();

	if (direction > 0) {
		sprite->Reverse();
	}
}

// Called every frame
void AConveyorBelt::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (character) {
		character->setHandicapMoveX(direction*velocity);
	}

}


void AConveyorBelt::OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) {
		character = dynamic_cast<AMainCharacter*>(OtherActor);
	}
}

void AConveyorBelt::OnOverlapExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	character = nullptr;
}

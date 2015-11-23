// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "KillerObject.h"

#include <Paper2DClasses.h>

#include "Logic/Components/Kill/KillerCollider.h"
#include "Logic/Components/Kill/MoveTransform.h"


// Sets default values
AKillerObject::AKillerObject(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	killerSprite(objectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, "KillerSprite")),
	collider(objectInitializer.CreateDefaultSubobject<UKillerCollider>(this, "KillCollider")),
	moveRail(objectInitializer.CreateDefaultSubobject<UMoveTransform>(this, "MoveRail")),
	moveSupport(objectInitializer.CreateDefaultSubobject<UMoveTransform>(this, "MoveSupport")),
	spriteSupport(objectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, "SpriteSupport")),
	spriteRail(objectInitializer.CreateDefaultSubobject<UPaperSpriteComponent>(this, "SpriteRail"))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = spriteRail;

	spriteSupport->AttachParent = spriteRail;

	killerSprite->AttachParent = spriteSupport;

	collider->AttachParent = killerSprite;


	moveRail->setTransformToMove(spriteRail);
	moveSupport->setTransformToMove(spriteSupport);

	spriteSupport->SetMobility(EComponentMobility::Movable);
	spriteRail->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AKillerObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKillerObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//sprite->Get (FVector(0, 0, 200));
}

void AKillerObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	moveRail->RegisterComponent();
	moveRail->SetActive(true);

	moveSupport->RegisterComponent();
	moveSupport->SetActive(true);
}

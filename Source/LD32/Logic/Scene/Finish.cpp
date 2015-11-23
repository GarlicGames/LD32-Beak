// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "Finish.h"

#include <Logic/Physics/Physics.h>

#include "Logic/MainCharacter.h"

AFinish::AFinish(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	collider(objectInitializer.CreateDefaultSubobject<UBoxComponent>(this, "collider"))
{
	RootComponent = collider;

	collider->OnComponentBeginOverlap.AddDynamic(this, &AFinish::OnOverlapEnter);

	collider->SetCollisionProfileName(TRANSFORMABLE_PROFILE);
}

// Called when the game starts or when spawned
void AFinish::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFinish::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFinish::OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{



}


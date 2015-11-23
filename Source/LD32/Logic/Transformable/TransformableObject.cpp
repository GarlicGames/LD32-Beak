// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "TransformableObject.h"

#include <Logic/Physics/Physics.h>

#include <Paper2DClasses.h>

#include "Logic/MainCharacter.h"

#include "Common/GamePlayEnums.h"

//const TCHAR* LOG_TRANSFORMABLEOBJECT = _T("ATransformableObject ->");

// Sets default values
ATransformableObject::ATransformableObject(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	collider(objectInitializer.CreateDefaultSubobject<UBoxComponent>(this,"BiteCollider")),
	//sprite(objectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, "Sprite")),
	skill(ESpecialSkill::NONE)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	RootComponent = collider;

	//collider->AttachParent = RootComponent;

	collider->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ATransformableObject::OnOverlapEnter);
	collider->OnComponentEndOverlap.AddDynamic(this, &ATransformableObject::OnOverlapExit);

	collider->SetCollisionProfileName(TRANSFORMABLE_PROFILE);

}

// Called when the game starts or when spawned
void ATransformableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATransformableObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATransformableObject::OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if ( OtherActor) {
		character = dynamic_cast<AMainCharacter*>(OtherActor);
		if (character) {
			character->setAviableTransformable(this);
			character->setSpecialSkill(skill);
		}	
	}
}
void ATransformableObject::OnOverlapExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (character) {
		character->setSpecialSkill(ESpecialSkill::NONE);
		character->removeAviableTransformable();
	}
	character = nullptr;
}

void ATransformableObject::setSkill(ESpecialSkill skill)
{
	//UE_LOG(LogClass, Log, _T("%s BITE"), LOG_TRANSFORMABLEOBJECT);
	if (this->skill == skill) {
		this->skill = ESpecialSkill::NONE;
	}
	else {
		this->skill = skill;
	}

	setColor();
	if (character) {
		character->setSpecialSkill(this->skill);
	}
}

void ATransformableObject::setColor()
{
	TArray<USceneComponent*> list;
	RootComponent->GetChildrenComponents(true, list);

	for (auto Iter(list.CreateConstIterator()); Iter; Iter++) {

		UPaperFlipbookComponent* sprite = dynamic_cast<UPaperFlipbookComponent*>(*Iter);
		if (sprite) {

			switch (skill) {
			case ESpecialSkill::EXTRA_FORCE:
				sprite->SetSpriteColor(FLinearColor::Red);
				break;
			case ESpecialSkill::EXTRA_JUMP:
				sprite->SetSpriteColor(FLinearColor::Green);
				break;
			case ESpecialSkill::EXTRA_SPEED:
				sprite->SetSpriteColor(FLinearColor::Blue);
				break;
			case ESpecialSkill::NONE:
				sprite->SetSpriteColor(FLinearColor::White);
				break;
			}
		}
		
		

	}
}


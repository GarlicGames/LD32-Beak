// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KillerObject.generated.h"

UCLASS()
class LD32_API AKillerObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillerObject(const class FObjectInitializer &objectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	virtual void PostInitializeComponents() override;

private:

	UPROPERTY(VisibleAnyWhere, Category = Sprite)
	class UPaperSpriteComponent *spriteRail;

	UPROPERTY(VisibleAnyWhere, Category = Sprite)
	class UPaperFlipbookComponent *killerSprite;

	UPROPERTY(VisibleAnyWhere, Category = Sprite)
	class UPaperSpriteComponent *spriteSupport;
	

	UPROPERTY(VisibleAnyWhere, Category = Behaviour)
	class UKillerCollider *collider;

	UPROPERTY(VisibleAnyWhere, Category = Behaviour)
	class UMoveTransform *moveRail;

	UPROPERTY(VisibleAnyWhere, Category = Behaviour)
	class UMoveTransform *moveSupport;

	
};

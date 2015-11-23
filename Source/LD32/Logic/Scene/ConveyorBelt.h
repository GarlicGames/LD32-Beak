// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ConveyorBelt.generated.h"

UCLASS()
class LD32_API AConveyorBelt : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConveyorBelt(const class FObjectInitializer &objectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:

	UFUNCTION()
		void OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(VisibleAnywhere, Category = Sprite)
	class UPaperFlipbookComponent *sprite;

	UPROPERTY(VisibleAnyWhere, Category = Behaviour)
	class UBoxComponent *collider;
	
	UPROPERTY(EditAnyWhere, Category = Behavior)
	float direction;

	UPROPERTY(EditAnyWhere, Category = Behavior)
	float velocity;

	class AMainCharacter *character;

};

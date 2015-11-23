// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TransformableObject.generated.h"

enum class ESpecialSkill;
UCLASS()
class LD32_API ATransformableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransformableObject(const class FObjectInitializer &objectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void setSkill(ESpecialSkill skill);

protected:

	UFUNCTION()
	void OnOverlapEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(VisibleAnyWhere, Category = Behaviour)
	class UBoxComponent *collider;

	ESpecialSkill skill;

	class AMainCharacter *character;

	void setColor();
	
	
};

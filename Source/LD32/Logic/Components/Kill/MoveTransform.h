// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "MoveTransform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LD32_API UMoveTransform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveTransform(const class FObjectInitializer &objectInitializer);

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void setTransformToMove(USceneComponent *transToMove){this->transToMove = transToMove;}

protected:


private:

	USceneComponent  *transToMove;

	FVector initPos;

	FVector finalPos;

	UPROPERTY(EditAnyWhere, Category = Behaviour)
	FVector distanceToMove;

	UPROPERTY(EditAnyWhere, Category = Behaviour)
	float  speedGoing;

	UPROPERTY(EditAnyWhere, Category = Behaviour)
	float  speedReturning;
		
	bool going;


	FVector Interpolate(FVector from, FVector to, float speed, float DeltaTime);
};

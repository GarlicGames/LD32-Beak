// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "MoveTransform.h"


//const TCHAR* LOG_MOVE_TRANSFORM = _T("UMoveTransformComponent ->");
// Sets default values for this component's properties
UMoveTransform::UMoveTransform(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	going(true),
	speedGoing(500),
	speedReturning(100),
	distanceToMove(0, 0, 200)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveTransform::InitializeComponent()
{
	Super::InitializeComponent();

	if (transToMove) {
		initPos = transToMove->RelativeLocation;
		finalPos = initPos + distanceToMove;
	}
	
}


// Called every frame
void UMoveTransform::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (transToMove) {
		if (going) {
			transToMove->SetRelativeLocation(Interpolate(transToMove->RelativeLocation, finalPos, speedGoing, DeltaTime));
		}
		else {
			transToMove->SetRelativeLocation(Interpolate(transToMove->RelativeLocation, initPos, speedReturning, DeltaTime));
		}

		
	}
}

FVector UMoveTransform::Interpolate(FVector from, FVector to, float speed, float DeltaTime)
{
	FVector pos;
	pos.X = FMath::FInterpConstantTo(from.X, to.X, DeltaTime, speed);
	pos.Y = FMath::FInterpConstantTo(from.Y, to.Y, DeltaTime, speed);
	pos.Z = FMath::FInterpConstantTo(from.Z, to.Z, DeltaTime, speed);

	if (pos == to) {
		going = !going;
	}

	return pos;
}
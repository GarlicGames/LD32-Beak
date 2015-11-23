// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "HenMovementComponent.h"

#include <Logic/MainCharacter.h>

//const TCHAR* LOG_HEN_MOVEMENT = _T("UHenMovementComponent ->");

UHenMovementComponent::UHenMovementComponent(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	extraSpeed(2.2), extraJump(300),
	movement(0, 0, 0),
	increaseWalk(25),
	maxWalk(600), handicapMove(0)
{

}

AMainCharacter* UHenMovementComponent::GetCharacterOwner() const
{
	return dynamic_cast<AMainCharacter*>(Super::GetCharacterOwner());
}

bool UHenMovementComponent::DoJump(bool bReplayingMoves)
{
	
	bool ret = Super::DoJump(bReplayingMoves);

	if (ret && GetCharacterOwner()->isExtraJump()) {
		Velocity.Z += extraJump;
	}
	Velocity.X = movement.X;

	return ret;
}

void UHenMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
	
	Velocity.X = movement.X;

	if (GetCharacterOwner()->isExtraSpeed()) {
		Velocity.X *= extraSpeed;
	}

	Velocity.X += handicapMove;
	
	/*float lastVelX = Velocity.X;

	Velocity.X += handicapMove;*/

	Super::PhysWalking(deltaTime, Iterations);

	//UE_LOG(LogClass, Log, _T("%s Vel %f "), LOG_HEN_MOVEMENT, Velocity.X);

	//Velocity.X = 0;
	handicapMove = 0;
}

void UHenMovementComponent::move(const float value)
{

	if (abs(movement.X) < maxWalk) {
		movement.X += value * increaseWalk;
	}
	else {
		movement.X = maxWalk * value;
	}


}

void UHenMovementComponent::stop()
{
	movement.X = 0;
}
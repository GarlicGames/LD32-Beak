// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "HenMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LD32_API UHenMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:

	UHenMovementComponent(const class FObjectInitializer &objectInitializer);

	void move(const float value);
	void stop();
	void setHandicapMove(float move){handicapMove = move;}

protected:

	virtual bool DoJump(bool bReplayingMoves) override;

	virtual void PhysWalking(float deltaTime, int32 Iterations) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float extraSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float extraJump;

	UPROPERTY(EditDefaultsOnly, Category = Behaviour)
	float increaseWalk;

	UPROPERTY(EditDefaultsOnly, Category = Behaviour)
	float maxWalk;

	FVector movement;
	float handicapMove;
	
	class AMainCharacter* GetCharacterOwner() const;
};

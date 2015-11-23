// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperCharacter.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
enum class ESpecialSkill;
UCLASS()
class LD32_API AMainCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:

	AMainCharacter(const class FObjectInitializer &objectInitializer);

	FVector GetVelocity()const override;

	void setHandicapMoveX(float velocity);

	bool isExtraSpeed();

	bool isExtraJump();

	void setSpecialSkill(ESpecialSkill skill);

	void setAviableTransformable(class ATransformableObject *transformable);
	void removeAviableTransformable();

	void kill();

	virtual void Falling() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void reStart();

	bool isAlive(){return !dead;}

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

private:

//Jump
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *idleJumpSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *runJumpSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *jumpJumpSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *biteJumpSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *fallingJumpSprite;

//Speed
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *idleSpeedSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *runSpeedSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *jumpSpeedSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *biteSpeedSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *fallingSpeedSprite;

//Force
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *idleForceSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *runForceSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *jumpForceSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *biteForceSprite;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *fallingForceSprite;


	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	class UPaperFlipbook *deadSprite;


	ESpecialSkill specialSkill;
	ESpecialSkill selectedSkill;

	bool bPressedBite;

	bool dead;

	class ATransformableObject *aviableTransformable;

	class UHenMovementComponent* GetCharacterMovement() const;	

	UFUNCTION()
	void MoveRight(float value);

	void lookRight();

	void lookLeft();

	UFUNCTION()
	void OnStartJump();

	UFUNCTION()
	void OnStopJump();

	UFUNCTION()
	void SelectedSpeed();

	UFUNCTION()
	void SelectedJump();

	UFUNCTION()
	void SelectedForce();

	UFUNCTION()
	void OnStartBite();

	UFUNCTION()
	void OnStopBite();

	void reStartSpriteLoop();

	void setIdle();

	void setRun();

	void setBite();

	void setJump();

	void setFalling();

	bool isJumpingSprite();

	bool isFallingSprite();
};

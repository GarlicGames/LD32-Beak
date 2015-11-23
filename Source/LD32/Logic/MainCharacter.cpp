// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "MainCharacter.h"

#include "Components/Character/HenMovementComponent.h"

#include "Common/GamePlayEnums.h"

#include <Paper2DClasses.h>

#include "PaperFlipbookComponent.h"

#include "Logic/Transformable/TransformableObject.h"

#include "Logic/Player/BeakPlayerController.h"

AMainCharacter::AMainCharacter(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer.SetDefaultSubobjectClass<UHenMovementComponent>(ACharacter::CharacterMovementComponentName)),
	specialSkill(ESpecialSkill::NONE), selectedSkill(ESpecialSkill::EXTRA_JUMP), aviableTransformable(nullptr), bPressedBite(false),
	dead(false)
{

	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	GetCapsuleComponent()->SetLockedAxis(ELockedAxis::Y);
	
	GetCharacterMovement()->ConstrainLocationToPlane(FVector(0, 1, 0));
}


UHenMovementComponent* AMainCharacter::GetCharacterMovement() const
{
	return dynamic_cast<UHenMovementComponent*>(Super::GetCharacterMovement());
}



void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	inputComponent->BindAxis("Right", this, &AMainCharacter::MoveRight);

	inputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMainCharacter::OnStartJump);
	inputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMainCharacter::OnStopJump);

	inputComponent->BindAction("SelectedSpeed", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectedSpeed);
	inputComponent->BindAction("SelectedJump", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectedJump);
	inputComponent->BindAction("SelectedForce", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectedForce);

	inputComponent->BindAction("Bite", EInputEvent::IE_Pressed, this, &AMainCharacter::OnStartBite);
	inputComponent->BindAction("Bite", EInputEvent::IE_Released, this, &AMainCharacter::OnStopBite);
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector position = RootComponent->GetComponentLocation();
	position.Y = 0;
	RootComponent->SetWorldLocation(position);
}

void AMainCharacter::MoveRight(float value)
{
	if (Controller != nullptr && !dead) {
		UHenMovementComponent *movement = GetCharacterMovement();
		UPaperFlipbookComponent *sprite = GetSprite();

		if (value != 0.0f ) {
			//AddMovementInput(FVector(value - handicapMove, 0.0f, 0.0f));
			movement->move(value);

			if (movement->IsMovingOnGround() && !bPressedJump && value != 0.f) {
				if (!bPressedBite || (bPressedBite && !sprite->IsPlaying())) {
					setRun();
					reStartSpriteLoop();
				}
			}

			if (value > 0.f) {
				lookRight();
			}
			else if (value < 0.f) {
				lookLeft();
			}
		}
		else {
			if (movement->IsMovingOnGround() && !bPressedJump ) {
				if (!bPressedBite || (bPressedBite && !sprite->IsPlaying())) {
					setIdle();
					reStartSpriteLoop();
				}
				
			}
			movement->stop();
		}
	}
}

void AMainCharacter::lookRight()
{
	GetSprite()->SetRelativeRotation(FRotator(0, 0, 0));
}

void AMainCharacter::lookLeft()
{
	GetSprite()->SetRelativeRotation(FRotator(0, -180, 0));
}

void AMainCharacter::OnStartJump()
{
	if (dead) {
		ABeakPlayerController *controller = dynamic_cast<ABeakPlayerController*>(GetController());
		controller->loadCheckpoint();
		return;
	}
	bPressedJump = true;
	setJump();
	GetSprite()->SetLooping(false);
}

void AMainCharacter::OnStopJump()
{
	bPressedJump = false;
}

void AMainCharacter::SelectedSpeed()
{
	selectedSkill = ESpecialSkill::EXTRA_SPEED;
	if (isFallingSprite() || isJumpingSprite()) {
		setFalling();
	}
}

void AMainCharacter::SelectedJump()
{
	selectedSkill = ESpecialSkill::EXTRA_JUMP;
	if (isFallingSprite() || isJumpingSprite()) {
		setFalling();
	}
}

void AMainCharacter::SelectedForce()
{
	selectedSkill = ESpecialSkill::EXTRA_FORCE;
	if (isFallingSprite() || isJumpingSprite()) {
		setFalling();
	}
}

void AMainCharacter::OnStartBite()
{
	if (!GetCharacterMovement()->IsMovingOnGround() || dead) {
		return;
	}
	bPressedBite = true;
	if (aviableTransformable) {
		aviableTransformable->setSkill(selectedSkill);
	}
	setBite();
	GetSprite()->SetLooping(false);
}

void AMainCharacter::OnStopBite()
{
	bPressedBite = false;
}

void AMainCharacter::reStartSpriteLoop()
{
	UPaperFlipbookComponent *sprite = GetSprite();
	if (!sprite->IsPlaying()) {
		sprite->Play();
		sprite->SetLooping(true);
	}
}

FVector AMainCharacter::GetVelocity() const
{
	return GetCharacterMovement()->Velocity;
}

void AMainCharacter::setHandicapMoveX(float velocity)
{
	GetCharacterMovement()->setHandicapMove(velocity);
}

bool AMainCharacter::isExtraSpeed()
{
	return specialSkill == ESpecialSkill::EXTRA_SPEED;
}

bool AMainCharacter::isExtraJump()
{
	return specialSkill == ESpecialSkill::EXTRA_JUMP;
}

void AMainCharacter::setSpecialSkill(ESpecialSkill skill)
{
	specialSkill = skill;
}

void AMainCharacter::setIdle()
{
	UPaperFlipbookComponent *sprite = GetSprite();
	switch (selectedSkill) {
		case ESpecialSkill::EXTRA_FORCE:
			sprite->SetFlipbook(idleForceSprite);
			break;
		case ESpecialSkill::EXTRA_JUMP:
			sprite->SetFlipbook(idleJumpSprite);
			break;
		case ESpecialSkill::EXTRA_SPEED:
			sprite->SetFlipbook(idleSpeedSprite);
			break;

	}
}
void AMainCharacter::setRun()
{
	switch (selectedSkill) {
		case ESpecialSkill::EXTRA_FORCE:
			GetSprite()->SetFlipbook(runForceSprite);
			break;
		case ESpecialSkill::EXTRA_JUMP:
			GetSprite()->SetFlipbook(runJumpSprite);
			break;
		case ESpecialSkill::EXTRA_SPEED:
			GetSprite()->SetFlipbook(runSpeedSprite);
			break;

	}
}
void AMainCharacter::setBite()
{
	switch (selectedSkill) {
		case ESpecialSkill::EXTRA_FORCE:
			GetSprite()->SetFlipbook(biteForceSprite);
			break;
		case ESpecialSkill::EXTRA_JUMP:
			GetSprite()->SetFlipbook(biteJumpSprite);
			break;
		case ESpecialSkill::EXTRA_SPEED:
			GetSprite()->SetFlipbook(biteSpeedSprite);
			break;
	}
}

void AMainCharacter::setJump()
{
	switch (selectedSkill) {
		case ESpecialSkill::EXTRA_FORCE:
			GetSprite()->SetFlipbook(jumpForceSprite);
			break;
		case ESpecialSkill::EXTRA_JUMP:
			GetSprite()->SetFlipbook(jumpJumpSprite);
			break;
		case ESpecialSkill::EXTRA_SPEED:
			GetSprite()->SetFlipbook(jumpSpeedSprite);
			break;
	}
}

void AMainCharacter::setFalling()
{
	switch (selectedSkill) {
		case ESpecialSkill::EXTRA_FORCE:
			GetSprite()->SetFlipbook(fallingForceSprite);
			break;
		case ESpecialSkill::EXTRA_JUMP:
			GetSprite()->SetFlipbook(fallingJumpSprite);
			break;
		case ESpecialSkill::EXTRA_SPEED:
			GetSprite()->SetFlipbook(fallingSpeedSprite);
			break;
	}
}
bool AMainCharacter::isJumpingSprite()
{
	UPaperFlipbookComponent *sprite = GetSprite();

	return sprite->GetFlipbook() == jumpForceSprite || sprite->GetFlipbook() == jumpJumpSprite || sprite->GetFlipbook() == jumpSpeedSprite;
}


void AMainCharacter::setAviableTransformable(class ATransformableObject *transformable)
{
	this->aviableTransformable = transformable;
}

void AMainCharacter::removeAviableTransformable()
{
	this->aviableTransformable = nullptr;
}

void AMainCharacter::kill()
{
	if (dead) {
		return;
	}
	dead = true;
	GetCharacterMovement()->stop();
	UPaperFlipbookComponent *sprite = GetSprite();
	sprite->SetFlipbook(deadSprite);
	sprite->PlayFromStart();
	sprite->SetLooping(false);
	
}

void AMainCharacter::Falling()
{
	if (!isJumpingSprite() && !dead) {
		setFalling();
	}
}

bool AMainCharacter::isFallingSprite()
{
	UPaperFlipbookComponent *sprite = GetSprite();

	return sprite->GetFlipbook() == fallingForceSprite || sprite->GetFlipbook() == fallingJumpSprite || sprite->GetFlipbook() == fallingSpeedSprite;
}

void AMainCharacter::reStart()
{
	dead = false;
	setIdle();
}
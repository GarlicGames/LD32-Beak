// Fill out your copyright notice in the Description page of Project Settings.

#include "LD32.h"
#include "BeakPlayerCameraManager.h"

#include "PlayerCameraActor.h"

ABeakPlayerCameraManager::ABeakPlayerCameraManager(const class FObjectInitializer &objectInitializer)
	:Super(objectInitializer),
	offsetMoveCameraXRight(0.f),
	offsetMoveCameraXLeft(200.f),
	offsetMoveCameraZUp(150.f),
	offsetMoveCameraZDown(0.f),
	minVelInter(100.f)

{

	/*SetActorRelativeLocation(FVector(0, -20, 0));
	bIsOrthographic = true;
	SetOrthoWidth(1800);*/

	PrimaryActorTick.bCanEverTick = true;

	SetTickGroup(ETickingGroup::TG_PostPhysics);

}

void ABeakPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	init();

}
void ABeakPlayerCameraManager::init()
{

	this->target = GetOwningPlayerController()->GetPawn();
	if (this->target) {
		FVector location(this->target->GetActorLocation());

		location.Y += 500.f;
		location.Z += offsetMoveCameraZUp;

		location.X += offsetMoveCameraXLeft;


		if (!playerCamara) {
			playerCamara = GetWorld()->SpawnActor<APlayerCameraActor>(location, FRotator(0, -90, 0));
		}
		else {
			playerCamara->SetActorLocation(location);
		}

	}

	SetViewTarget(playerCamara);
}


void ABeakPlayerCameraManager::Tick(float deltaTime)
{
	FVector location(this->target->GetActorLocation());
	FVector cameraLocation(playerCamara->GetActorLocation());
	location.Y = cameraLocation.Y;
	location.X += offsetMoveCameraXLeft;
	location.Z += offsetMoveCameraZUp;

	if (location.X >= cameraLocation.X - offsetMoveCameraXLeft && location.X <= cameraLocation.X + offsetMoveCameraXRight) {
		location.X = cameraLocation.X;
	}

	if (location.Z >= cameraLocation.Z - offsetMoveCameraZDown && location.Z <= cameraLocation.Z + offsetMoveCameraZUp) {
		location.Z = cameraLocation.Z;
	}
	/*FMinimalViewInfo viewData;
	playerCamara->GetCameraComponent()->GetCameraView(deltaTime, viewData);*/
	FVector targetVel(target->GetVelocity());
	//int speed = FMath::Max( abs(targetVel.X), abs(targetVel.Z));

	
	location.X = FMath::FInterpConstantTo(cameraLocation.X, location.X, deltaTime, FMath::Max(minVelInter, abs(targetVel.X)));

	location.Z = FMath::FInterpConstantTo(cameraLocation.Z, location.Z, deltaTime, FMath::Max(minVelInter, abs(targetVel.Z)));

	playerCamara->SetActorLocation(location);
	//playerCamara->SetActorLocation((FMath::VInterpTo(cameraLocation, location, deltaTime, FMath::Min(3,FMath::Max(speed, 100) / 100) )));
}


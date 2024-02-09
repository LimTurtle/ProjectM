// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "MyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API AMyPlayer : public ACreature
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneComp;
	UPROPERTY(VisibleAnywhere)
	FVector MousePoint;

public:
	AMyPlayer();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void KeyboardUpDown(float value);
	void KeyboardRightLeft(float value);
	void MouseUpDown(float value);
	void MouseRightLeft(float value);

	void Attack();

	FVector GetMousePoint();
};

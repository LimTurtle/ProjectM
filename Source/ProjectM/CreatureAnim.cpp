// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureAnim.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayer.h"

void UCreatureAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UCreatureAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Movement))
	{
		IsFalling = Movement->IsFalling();

		Velocity = Movement->Velocity;

		if (Velocity.Size2D() > 5.f) ShouldMove = true;
		else ShouldMove = false;
	}

}

UCharacterMovementComponent* UCreatureAnim::GetMovement()
{
	return Movement;
}

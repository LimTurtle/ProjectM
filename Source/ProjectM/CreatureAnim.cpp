// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayer.h"

void UCreatureAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Character = Cast<AMyPlayer>(Pawn);
		if (IsValid(Character))
		{
			Movement = Character->GetCharacterMovement();
		}
	}
}

void UCreatureAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Movement))
	{
		IsFalling = Movement->IsFalling();

		Velocity = Movement->Velocity;
		NormVelocity = Velocity.GetSafeNormal();
		if (Velocity.Size2D() > 5.f) ShouldMove = true;
		else ShouldMove = false;
	}

}

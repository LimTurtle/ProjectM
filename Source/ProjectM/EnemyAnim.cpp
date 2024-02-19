// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "MyEnemy.h"

void UEnemyAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Character = Cast<AMyEnemy>(Pawn);
		if (IsValid(Character))
		{
			Movement = Character->GetCharacterMovement();
		}
	}
}

void UEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		FVector UnrotatedVector = Character->GetActorRotation().UnrotateVector(Velocity);
		NormVelocity = UnrotatedVector.GetSafeNormal();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnim.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyPlayer.h"

void UPlayerAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	//if (IsValid(Movement))
	//{
	//	Movement->bOrientRotationToMovement = false;
	//}
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		LookRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), Character->GetMousePoint());
		FRotator CharacterRotation = Character->GetActorRotation();
		//CharacterRotation.Yaw = FMath::FInterpTo(CharacterRotation.Yaw, LookRotation.Yaw, DeltaSeconds, 50.f);
		CharacterRotation.Yaw = LookRotation.Yaw;
		Character->GetCapsuleComponent()->SetWorldRotation(CharacterRotation);
		if (Velocity != FVector::ZeroVector)
		{
			FVector UnrotatedVector = Character->GetCapsuleComponent()->GetComponentRotation().UnrotateVector(Velocity);
			NormVelocity = UnrotatedVector.GetSafeNormal();
		}
	}
}

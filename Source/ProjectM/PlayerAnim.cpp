// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "MyPlayer.h"
#include "PlayerAnim.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		//LookRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), Character->GetMousePoint());
		//FRotator CharacterRotation = Character->GetActorRotation();
		//CharacterRotation.Yaw = FMath::FInterpTo(CharacterRotation.Yaw, LookRotation.Yaw, DeltaSeconds, 50.f);
		//Character->SetActorRotation(CharacterRotation);
	}
}

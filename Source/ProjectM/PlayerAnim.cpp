// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnim.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyPlayer.h"

UPlayerAnim::UPlayerAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/Animations/AM_Attack.AM_Attack'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

void UPlayerAnim::NativeBeginPlay()
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
	
	if (IsValid(Movement))
	{
		Movement->bOrientRotationToMovement = false;
	}

	OnMontageEnded.AddDynamic(this, &UPlayerAnim::OnAttackMontageEnded);
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character))
	{
		LookRotation = UKismetMathLibrary::FindLookAtRotation(Character->GetCapsuleComponent()->GetComponentLocation(), Character->GetMousePoint());
		FRotator CharacterRotation = Character->GetActorRotation();
		//CharacterRotation.Yaw = FMath::FInterpTo(CharacterRotation.Yaw, LookRotation.Yaw, DeltaSeconds, 50.f);
		CharacterRotation.Yaw = LookRotation.Yaw;
		Character->GetCapsuleComponent()->SetWorldRotation(CharacterRotation);

		FVector UnrotatedVector = Character->GetCapsuleComponent()->GetComponentRotation().UnrotateVector(Velocity);
		NormVelocity = UnrotatedVector.GetSafeNormal();
	}
}

void UPlayerAnim::PlayAttackMontage()
{
	if (IsValid(AttackMontage))
	{
		if (!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage);
			IsAttacking = true;
		}
	}
}

void UPlayerAnim::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

bool UPlayerAnim::GetIsAttacking()
{
	return IsAttacking;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyEnemy.h"

UEnemyAnim::UEnemyAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> NAM(TEXT("/Script/Engine.AnimMontage'/Game/Animations/AM_EnemyNearAttack.AM_EnemyNearAttack'"));
	if (NAM.Succeeded())
	{
		NearAttackMontage = NAM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FAM(TEXT("/Script/Engine.AnimMontage'/Game/Animations/AM_FarAttack.AM_FarAttack'"));
	if (FAM.Succeeded())
	{
		//UE_LOG(LogTemp, Log, TEXT("FarAttack Init"));
		FarAttackMontage = FAM.Object;
	}
}

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
			Movement->bUseControllerDesiredRotation = true;
			Movement->bOrientRotationToMovement = false;

			Character->bUseControllerRotationYaw = false;
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

void UEnemyAnim::PlayNearAttackMontage()
{
	if (IsValid(Character))
	{
		if (!IsAnyMontagePlaying())
		{
			Montage_Play(NearAttackMontage);
		}
	}
}

void UEnemyAnim::PlayFarAttackMontage()
{
	if (IsValid(Character))
	{
		if (!IsAnyMontagePlaying())
		{
			//UE_LOG(LogTemp, Log, TEXT("FarAttack"));
			Montage_Play(FarAttackMontage);
		}
	}
}

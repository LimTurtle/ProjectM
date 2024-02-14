// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureAnim.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API UPlayerAnim : public UCreatureAnim
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	FRotator LookRotation;
	UPROPERTY(Category = "Animation", VisibleAnywhere)
	UAnimMontage* AttackMontage;
	UPROPERTY(Category = "Animation", VisibleAnywhere)
	bool IsAttacking = false;
public:
	UPlayerAnim();

	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	void PlayAttackMontage();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	bool GetIsAttacking();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureAnim.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API UEnemyAnim : public UCreatureAnim
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class AMyEnemy* Character;
	UPROPERTY(Category = "Animation", VisibleAnywhere)
	UAnimMontage* NearAttackMontage;
	UPROPERTY(Category = "Animation", VisibleAnywhere)
	UAnimMontage* FarAttackMontage;

public:
	UEnemyAnim();

	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	void PlayNearAttackMontage();
	void PlayFarAttackMontage();
};

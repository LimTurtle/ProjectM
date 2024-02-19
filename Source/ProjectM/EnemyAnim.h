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
	
public:
	UPROPERTY(Category = "Animation", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class AMyEnemy* Character;

	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};

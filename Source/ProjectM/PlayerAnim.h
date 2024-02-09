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
	FRotator LookRotation;
public:
	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};

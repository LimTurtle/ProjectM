// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_NearAttackable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API UBTDecorator_NearAttackable : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_NearAttackable();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};

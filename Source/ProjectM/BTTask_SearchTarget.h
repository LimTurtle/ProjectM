// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SearchTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API UBTTask_SearchTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SearchTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FarAttack.h"
#include "EnemyAIController.h"
#include "MyEnemy.h"

UBTTask_FarAttack::UBTTask_FarAttack()
{
	NodeName = TEXT("FarAttack");
}

EBTNodeResult::Type UBTTask_FarAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Pawn = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Pawn)) return EBTNodeResult::Failed;

	Pawn->FarAttack();

	return EBTNodeResult::Succeeded;
}

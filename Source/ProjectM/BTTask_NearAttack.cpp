// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NearAttack.h"
#include "EnemyAIController.h"
#include "MyEnemy.h"

UBTTask_NearAttack::UBTTask_NearAttack()
{
	NodeName = TEXT("NearAttack");
}

EBTNodeResult::Type UBTTask_NearAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Pawn = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!IsValid(Pawn)) return EBTNodeResult::Failed;

	Pawn->NearAttack();

	return EBTNodeResult::Succeeded;
}

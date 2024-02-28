// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_NearAttackable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "MyPlayer.h"

UBTDecorator_NearAttackable::UBTDecorator_NearAttackable()
{
	NodeName = TEXT("NearAttackable");
}

bool UBTDecorator_NearAttackable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto Target = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("Target")));
	if (IsValid(Pawn) && IsValid(Target) && Pawn->GetDistanceTo(Target) <= 500.f) return true;
	return false;
}

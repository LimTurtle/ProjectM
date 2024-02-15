// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SearchTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayer.h"

UBTTask_SearchTarget::UBTTask_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
}

EBTNodeResult::Type UBTTask_SearchTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Target = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Target))
	{
		UE_LOG(LogTemp, Log, TEXT("Find Target"));
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), Target);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Not Find Target"));
	}

	return EBTNodeResult::Failed;
}

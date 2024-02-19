// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "MyPlayer.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("Service_SearchTarget");
	Interval = 0.5f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (IsValid(CurPawn))
	{
		FVector Center = CurPawn->GetActorLocation();
		float SearchDistance = 500.f;

		TArray<FOverlapResult> OverlapResult;

		bool Result = GetWorld()->OverlapMultiByChannel(
			OverlapResult,
			Center,
			FQuat::Identity,
			ECollisionChannel::ECC_Pawn,
			FCollisionShape::MakeSphere(SearchDistance)
		);

		if (Result)
		{
			for (auto& Res : OverlapResult)
			{
				auto Target = Cast<AMyPlayer>(Res.GetActor());
				if (IsValid(Target))
				{
					DrawDebugSphere(GetWorld(), Center, SearchDistance, 10, FColor::Green);
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), Target);
					return;
				}
				else
				{
					DrawDebugSphere(GetWorld(), Center, SearchDistance, 10, FColor::Red);
				}
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), nullptr);
	}
}

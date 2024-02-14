// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"

#include "Components/SkeletalMeshComponent.h"
#include "EnemyAIController.h"

AMyEnemy::AMyEnemy()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	AIControllerClass = AEnemyAIController::StaticClass();
}

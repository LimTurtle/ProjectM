// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CreatureAnim.h"
#include "EnemyAIController.h"
#include "EnemyAnim.h"
#include "FireStorm.h"
#include "Materials/MaterialInterface.h"

AMyEnemy::AMyEnemy()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	GetCapsuleComponent()->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/BattleWizardPolyart/Materials/MaskTintPolyartMatInst02.MaskTintPolyartMatInst02'"));
	if (MI.Succeeded())
	{
		GetMesh()->SetMaterial(0, MI.Object);
	}

	static ConstructorHelpers::FClassFinder<UCreatureAnim> AnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_EnemyAnim.ABP_EnemyAnim_C'"));
	if (AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	AIControllerClass = AEnemyAIController::StaticClass();

	static ConstructorHelpers::FObjectFinder<UBlueprint> FS(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_FireStorm.BP_FireStorm'"));
	if (FS.Succeeded())
	{
		FireStorm = (UClass*)FS.Object->GeneratedClass;
	}
}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	AnimIns = Cast<UEnemyAnim>(GetMesh()->GetAnimInstance());
}

void AMyEnemy::SetAttackTarget(AActor* target)
{
	AttackTarget = target;
}

void AMyEnemy::NearAttack()
{
	if (IsValid(AnimIns))
	{
		AnimIns->PlayNearAttackMontage();

		if (IsValid(AttackTarget))
		{
			FVector TargetLoc = AttackTarget->GetActorLocation();
			TargetLoc.Z = 0.f;
			GetWorld()->SpawnActor<AFireStorm>(FireStorm, TargetLoc, FRotator::ZeroRotator);
			//UE_LOG(LogTemp, Log, TEXT("%f / %f"), TargetLoc.X, TargetLoc.Y);
			//GetWorld()->SpawnActor<AFireStorm>(AFireStorm::StaticClass(), AttackTarget->GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "MyEnemy.h"

#include "BossWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CreatureAnim.h"
#include "EnemyAIController.h"
#include "EnemyAnim.h"
#include "Engine/SkeletalMeshSocket.h"
#include "FireStorm.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "MyGameModeBase.h"
#include "HpBarWidget.h"

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

	auto Weapon = GetWorld()->SpawnActor<ABossWeapon>(ABossWeapon::StaticClass(), GetActorLocation(), GetActorRotation());
	if (IsValid(Weapon))
	{
		auto WeaponSocket = GetMesh()->GetSocketByName(TEXT("WeaponSocket"));
		if (WeaponSocket)
		{
			WeaponSocket->AttachActor(Weapon, GetMesh());
		}
	}

	AnimIns = Cast<UEnemyAnim>(GetMesh()->GetAnimInstance());

	auto Gamemode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Gamemode)
	{
		HpBar = Cast<UHpBarWidget>(Gamemode->CurrentWidget);
		if (HpBar)
		{
			HpBar->BindEnemyHp(this);
		}
	}
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

float AMyEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Hp = Hp - DamageAmount;
	if (Hp < 0.f) Hp = 0.f;
	OnEnemyHpChanged.Broadcast();
	return DamageAmount;
}

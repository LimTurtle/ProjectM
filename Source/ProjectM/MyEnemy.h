// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "MyEnemy.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnEnemyHpChanged)

UCLASS()
class PROJECTM_API AMyEnemy : public ACreature
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class UEnemyAnim* AnimIns;
	UPROPERTY(VisibleAnywhere)
	AActor* AttackTarget;
	UPROPERTY(VisibleAnywhere)
	UClass* FireStorm;
	UPROPERTY(VisibleAnywhere)
	class UHpBarWidget* HpBar;

public:
	AMyEnemy();

	virtual void BeginPlay() override;

	void SetAttackTarget(AActor* target);
	void NearAttack();
	void FarAttack();

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
	void CreatureDead();

	FOnEnemyHpChanged OnEnemyHpChanged;
};

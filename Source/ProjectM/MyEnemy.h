// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "MyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API AMyEnemy : public ACreature
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class UEnemyAnim* AnimIns;

public:
	AMyEnemy();

	virtual void BeginPlay() override;

	void NearAttack();
};

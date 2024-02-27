// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTM_API UHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class AMyPlayer* Player;
	UPROPERTY()
	class AMyEnemy* Enemy;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PlayerHpBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* EnemyHpBar;

public:
	void BindPlayerHp(AMyPlayer* PlayerActor);
	void BindEnemyHp(AMyEnemy* EnemyActor);
	void UpdatePlayerHp();
	void UpdateEnemyHp();
};

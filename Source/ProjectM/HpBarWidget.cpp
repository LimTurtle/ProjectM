// Fill out your copyright notice in the Description page of Project Settings.


#include "HpBarWidget.h"
#include "Components/ProgressBar.h"
#include "MyEnemy.h"
#include "MyPlayer.h"

void UHpBarWidget::BindPlayerHp(AMyPlayer* PlayerActor)
{
	Player = PlayerActor;
	Player->OnPlayerHpChanged.AddUObject(this, &UHpBarWidget::UpdatePlayerHp);
	UpdatePlayerHp();
}

void UHpBarWidget::BindEnemyHp(AMyEnemy* EnemyActor)
{
	Enemy = EnemyActor;
	Enemy->OnEnemyHpChanged.AddUObject(this, &UHpBarWidget::UpdateEnemyHp);
	UpdateEnemyHp();
}

void UHpBarWidget::UpdatePlayerHp()
{
	PlayerHpBar->SetPercent(Player->GetHpRatio());
}

void UHpBarWidget::UpdateEnemyHp()
{
	EnemyHpBar->SetPercent(Enemy->GetHpRatio());
}


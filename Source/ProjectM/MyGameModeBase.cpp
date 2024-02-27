// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "MyPlayer.h"
#include "HpBarWidget.h"


AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMyPlayer> MP(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_MyPlayer.BP_MyPlayer_C'"));

	if (MP.Succeeded())
	{
		DefaultPawnClass = MP.Class;
	}

	static ConstructorHelpers::FClassFinder<UHpBarWidget> HBW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (HBW.Succeeded())
	{
		HUD_Class = HBW.Class;
		CurrentWidget = CreateWidget(GetWorld(), HUD_Class);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

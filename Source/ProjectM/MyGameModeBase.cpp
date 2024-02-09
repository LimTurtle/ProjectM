// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "MyPlayer.h"


AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMyPlayer> MP(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_MyPlayer.BP_MyPlayer_C'"));

	if (MP.Succeeded())
	{
		DefaultPawnClass = MP.Class;
	}
}

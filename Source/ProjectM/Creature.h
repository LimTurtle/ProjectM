// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDead)

UCLASS()
class PROJECTM_API ACreature : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	float MaxHp = 100.f;
	UPROPERTY()
	float Hp = 100.f;

public:
	// Sets default values for this character's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetHpRatio();

	FOnDead OnDead;
};

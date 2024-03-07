// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "MyPlayer.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnPlayerHpChanged)

UCLASS()
class PROJECTM_API AMyPlayer : public ACreature
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	class UPlayerAnim* AnimIns;
	UPROPERTY(VisibleAnywhere)
	class UHpBarWidget* HpBar;
	UPROPERTY(VisibleAnywhere)
	FVector MousePoint;

public:
	AMyPlayer();

public:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void KeyboardUpDown(float value);
	void KeyboardRightLeft(float value);
	void MouseUpDown(float value);
	void MouseRightLeft(float value);

	void Attack();
	void SaveHp();
	void CreatureDead();
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	FVector GetMousePoint();

	FOnPlayerHpChanged OnPlayerHpChanged;
};

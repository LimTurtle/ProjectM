// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireStorm.generated.h"

UCLASS()
class PROJECTM_API AFireStorm : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystem;
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* DefaultRoot;
public:	
	// Sets default values for this actor's properties
	AFireStorm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

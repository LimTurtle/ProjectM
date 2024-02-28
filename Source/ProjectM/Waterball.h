// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waterball.generated.h"

UCLASS()
class PROJECTM_API AWaterball : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* DefaultRoot;
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CollisionMesh;
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileComponent;
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* ParticleSystem;
	UPROPERTY(VisibleAnywhere)
	class UParticleSystem* CollisionParticle;
public:	
	// Sets default values for this actor's properties
	AWaterball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "FireStorm.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFireStorm::AFireStorm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = DefaultRoot;
	RootComponent->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireStorm.P_ky_fireStorm'"));

	if (PS.Succeeded())
	{
		ParticleSystem->SetTemplate(PS.Object);
	}
}

// Called when the game starts or when spawned
void AFireStorm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


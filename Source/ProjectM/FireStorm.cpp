// Fill out your copyright notice in the Description page of Project Settings.


#include "FireStorm.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AFireStorm::AFireStorm()
{
	SetActorHiddenInGame(true);

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

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(RootComponent);
	CapsuleComp->SetRelativeLocation(FVector(0.f, 0.f, 240.f));
	//CapsuleComp->SetRelativeScale3D(FVector(4.25f, 4.25f, 6.25f));
	CapsuleComp->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	CapsuleComp->SetGenerateOverlapEvents(true);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AFireStorm::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void AFireStorm::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {ActorActive(); }, .5f, false);
}

// Called every frame
void AFireStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireStorm::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UE_LOG(LogTemp, Log, TEXT("OverlapBegin"));
		UGameplayStatics::ApplyDamage(OtherActor, 10.f, nullptr, nullptr, NULL);
	}
}

void AFireStorm::ActorActive()
{
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetActorHiddenInGame(false);
	ParticleSystem->Activate();
}



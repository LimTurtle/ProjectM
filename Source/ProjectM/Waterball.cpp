// Fill out your copyright notice in the Description page of Project Settings.


#include "Waterball.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AWaterball::AWaterball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = DefaultRoot;
	RootComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_waterBall.P_ky_waterBall'"));

	if (PS.Succeeded())
	{
		ParticleSystem->SetTemplate(PS.Object);
	}

	CollisionMesh = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CollisionMesh->SetupAttachment(RootComponent);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AWaterball::OnOverlapBegin);
	CollisionMesh->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileComponent->SetUpdatedComponent(RootComponent);
	ProjectileComponent->InitialSpeed = 1500.f;
	ProjectileComponent->MaxSpeed = 1500.f;
	ProjectileComponent->bIsHomingProjectile = false;
	ProjectileComponent->ProjectileGravityScale = 0.f;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> CPS(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_waterBallHit.P_ky_waterBallHit'"));
	if (CPS.Succeeded())
	{
		CollisionParticle = CPS.Object;
	}
}

// Called when the game starts or when spawned
void AWaterball::BeginPlay()
{
	Super::BeginPlay();
	
	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {Destroy(); }, 3.f, false);
}

// Called every frame
void AWaterball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaterball::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		if (ParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollisionParticle, CollisionMesh->GetComponentLocation());
		}
		UGameplayStatics::ApplyDamage(OtherActor, 10.f, ProjectileComponent->GetOwner()->GetInstigatorController(), nullptr, NULL);
		Destroy();
	}
}


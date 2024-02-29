// Fill out your copyright notice in the Description page of Project Settings.


#include "Fireball.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AFireball::AFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	if (SM.Succeeded())
	{
		StaticMesh->SetupAttachment(RootComponent);
		StaticMesh->SetStaticMesh(SM.Object);
		//StaticMesh->SetRelativeRotation(FRotator(0.f, 200.f, 0.f));
		StaticMesh->SetRelativeScale3D(FVector(0.85f, 0.85f, 0.85f));
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/FXVarietyPack/Materials/MI_ky_storm01_fire_nonD1.MI_ky_storm01_fire_nonD1'"));
		if (MI.Succeeded())
		{
			StaticMesh->SetMaterial(0, MI.Object);
		}

		CollisionMesh = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
		CollisionMesh->SetupAttachment(StaticMesh);
		CollisionMesh->SetCapsuleHalfHeight(40.f);
		CollisionMesh->SetCapsuleRadius(15.f);
		CollisionMesh->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
		CollisionMesh->SetRelativeLocation(FVector(-20.f, 10.f, 15.f));
		CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AFireball::OnOverlapBegin);

		ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileComponent->SetUpdatedComponent(RootComponent);
		ProjectileComponent->InitialSpeed = 1500.f;
		ProjectileComponent->MaxSpeed = 1500.f;
		ProjectileComponent->bIsHomingProjectile = false;
		ProjectileComponent->ProjectileGravityScale = 0.f;

		static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_explosion.P_ky_explosion'"));
		if (PS.Succeeded())
		{
			ParticleSystem = PS.Object;
		}
	}
}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();
	
	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {Destroy(); }, 3.f, false);
}

// Called every frame
void AFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireball::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComp)
	{
		if (ParticleSystem)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, CollisionMesh->GetComponentLocation());
		}
		UGameplayStatics::ApplyDamage(OtherActor, 10.f, ProjectileComponent->GetOwner()->GetInstigatorController(), nullptr, NULL);
		Destroy();
	}
}


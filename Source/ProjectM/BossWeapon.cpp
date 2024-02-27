// Fill out your copyright notice in the Description page of Project Settings.


#include "BossWeapon.h"

// Sets default values
ABossWeapon::ABossWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/BattleWizardPolyart/Meshes/MagicStaffs/Staff03SM.Staff03SM'"));
	if (SM.Succeeded())
	{
		StaticMesh->SetStaticMesh(SM.Object);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		StaticMesh->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	}

}

// Called when the game starts or when spawned
void ABossWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/BattleWizardPolyart/Meshes/MagicStaffs/Staff02SM.Staff02SM'"));
	if (SM.Succeeded())
	{
		StaticMesh->SetStaticMesh(SM.Object);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CreatureAnim.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Fireball.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "MyGameModeBase.h"
#include "HpBarWidget.h"
#include "PlayerAnim.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon.h"

#define CAM_LIMIT_DIST 300.f

AMyPlayer::AMyPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM'"));
	
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	//RootComponent = SceneComp;

	GetCapsuleComponent()->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//SpringArm->TargetArmLength = 800.f;
	//SpringArm->SocketOffset = FVector(0.f, -200.f, 800.f);

	//Camera->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 1200.f));

	Camera->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));

	static ConstructorHelpers::FClassFinder<UCreatureAnim> AnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_PlayerAnim.ABP_PlayerAnim_C'"));
	if (AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	auto Weapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), GetActorLocation(), GetActorRotation());
	if (IsValid(Weapon))
	{
		auto WeaponSocket = GetMesh()->GetSocketByName(TEXT("WeaponSocket"));
		if (WeaponSocket)
		{
			WeaponSocket->AttachActor(Weapon, GetMesh());
		}
	}

	AnimIns = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());

	//auto HpWidget = Cast<UHpBarWidget>()
	auto Gamemode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Gamemode)
	{
		HpBar = Cast<UHpBarWidget>(Gamemode->CurrentWidget);
		if (HpBar)
		{
			Hp = 30.f;
			HpBar->BindPlayerHp(this);
		}
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("KeyboardUpDown"), this, &AMyPlayer::KeyboardUpDown);
	PlayerInputComponent->BindAxis(TEXT("KeyboardRightLeft"), this, &AMyPlayer::KeyboardRightLeft);
	//PlayerInputComponent->BindAxis(TEXT("MouseUpDown"), this, &AMyPlayer::MouseUpDown);
	//PlayerInputComponent->BindAxis(TEXT("MouseRightLeft"), this, &AMyPlayer::MouseRightLeft);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AMyPlayer::Attack);

}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MouseLocation;
	FVector MouseDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	FHitResult HitResult;

	FVector Center = MouseLocation;
	FVector Forward = MouseLocation + MouseDirection * 5000.f;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool Result = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Center,
		Forward,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);

	if (Result)
	{
		//DrawDebugLine(GetWorld(), Center, Forward, FColor::Green, false, 3.f);
		FVector TargetPoint = HitResult.ImpactPoint;
		MousePoint = TargetPoint;
		FVector DeltaTarget = TargetPoint - GetCapsuleComponent()->GetComponentLocation();

		if (DeltaTarget.Size2D() > 100.f)
		{
			//Dynamic Camera
			SpringArm->SocketOffset.X = FMath::FInterpTo(SpringArm->SocketOffset.X, DeltaTarget.X, DeltaTime, 3.f);
			SpringArm->SocketOffset.Y = FMath::FInterpTo(SpringArm->SocketOffset.Y, DeltaTarget.Y, DeltaTime, 3.f);
		
			SpringArm->SocketOffset.X = FMath::Clamp(SpringArm->SocketOffset.X, -CAM_LIMIT_DIST, CAM_LIMIT_DIST - 50.f);
			SpringArm->SocketOffset.Y = FMath::Clamp(SpringArm->SocketOffset.Y, -CAM_LIMIT_DIST, CAM_LIMIT_DIST);
		}
	}

	FVector CharacterLocation = GetCapsuleComponent()->GetComponentLocation() + FVector(-500.f, 0.f, 900.f);
	FVector NextCamLocation = FMath::VInterpTo(SpringArm->GetComponentLocation(), CharacterLocation, DeltaTime, 10.f);
	SpringArm->SetWorldLocation(NextCamLocation);
}

void AMyPlayer::KeyboardUpDown(float value)
{
	AddMovementInput(FVector::ForwardVector, value);
}

void AMyPlayer::KeyboardRightLeft(float value)
{
	AddMovementInput(FVector::RightVector, value);
}

void AMyPlayer::MouseUpDown(float value)
{
	AddControllerPitchInput(-value);
}

void AMyPlayer::MouseRightLeft(float value)
{
	AddControllerYawInput(value);
}

void AMyPlayer::Attack()
{
	if (IsValid(AnimIns) && !AnimIns->GetIsAttacking())
	{
		AnimIns->PlayAttackMontage();

		auto Fireball = GetWorld()->SpawnActor<AFireball>(AFireball::StaticClass(), 
			GetCapsuleComponent()->GetComponentLocation() + (GetCapsuleComponent()->GetForwardVector()) * 100.f,
			GetCapsuleComponent()->GetComponentRotation());
	}
}

FVector AMyPlayer::GetMousePoint()
{
	return MousePoint;
}

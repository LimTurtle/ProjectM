// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"

#define CAM_LIMIT_DIST 300.f

AMyPlayer::AMyPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/BattleWizardPolyart/Meshes/WizardSM.WizardSM'"));
	
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 800.f;
	SpringArm->SocketOffset = FVector(0.f, -200.f, 800.f);

	Camera->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));
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
	//RotateYaw = FMath::FInterpTo(RotateYaw, 0.f, DeltaSeconds, 20.0f); // FInterp

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
		FVector DeltaTarget = TargetPoint - GetActorLocation();

		SpringArm->SocketOffset.X = FMath::FInterpTo(SpringArm->SocketOffset.X, DeltaTarget.X, DeltaTime, 3.f);
		SpringArm->SocketOffset.Y = FMath::FInterpTo(SpringArm->SocketOffset.Y, DeltaTarget.Y, DeltaTime, 3.f);

		SpringArm->SocketOffset.X = FMath::Clamp(SpringArm->SocketOffset.X, -CAM_LIMIT_DIST, CAM_LIMIT_DIST);
		SpringArm->SocketOffset.Y = FMath::Clamp(SpringArm->SocketOffset.Y, -CAM_LIMIT_DIST, CAM_LIMIT_DIST);
	}
}

void AMyPlayer::KeyboardUpDown(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyPlayer::KeyboardRightLeft(float value)
{
	AddMovementInput(GetActorRightVector(), value);
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

}

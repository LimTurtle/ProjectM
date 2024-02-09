// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CreatureAnim.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
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

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	GetCapsuleComponent()->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//SpringArm->TargetArmLength = 800.f;
	//SpringArm->SocketOffset = FVector(0.f, -200.f, 800.f);

	//Camera->SetRelativeRotation(FRotator(0.f, -60.f, 0.f));

	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 1200.f));

	Camera->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));

	static ConstructorHelpers::FClassFinder<UCreatureAnim> AnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_PlayerAnim.ABP_PlayerAnim_C'"));
	if (AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
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
		FVector DeltaTarget = TargetPoint - GetActorLocation();

		//Dynamic Camera
		//SpringArm->SocketOffset.X = FMath::FInterpTo(SpringArm->SocketOffset.X, DeltaTarget.X, DeltaTime, 3.f);
		//SpringArm->SocketOffset.Y = FMath::FInterpTo(SpringArm->SocketOffset.Y, DeltaTarget.Y, DeltaTime, 3.f);
		//
		//SpringArm->SocketOffset.X = FMath::Clamp(SpringArm->SocketOffset.X, -CAM_LIMIT_DIST, CAM_LIMIT_DIST);
		//SpringArm->SocketOffset.Y = FMath::Clamp(SpringArm->SocketOffset.Y, -CAM_LIMIT_DIST, CAM_LIMIT_DIST);
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

}

FVector AMyPlayer::GetMousePoint()
{
	return MousePoint;
}

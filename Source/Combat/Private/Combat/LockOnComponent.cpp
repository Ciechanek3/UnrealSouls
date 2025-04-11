// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockOnComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	_ownerRef = GetOwner<ACharacter>();
	_playerController = GetWorld()->GetFirstPlayerController();
	_movementComp = _ownerRef->GetCharacterMovement();
	_springArmComponent = _ownerRef->FindComponentByClass<USpringArmComponent>();
}

void ULockOnComponent::StartLockOn(float Radius)
{
	FHitResult hitResult;
	FVector currentLocation = _ownerRef->GetActorLocation();
	FCollisionShape sphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams ignoreParams{
		FName { TEXT("Ignore Collision Params") },
		false,
		_ownerRef
	};
	
	bool bHasFoundTarget = GetWorld()->SweepSingleByChannel(
		hitResult,
		currentLocation,
		currentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		sphere,
		ignoreParams
	);

	if (!bHasFoundTarget) { return; }

	CurrentTargetActor = hitResult.GetActor();

	_playerController->SetIgnoreLookInput(true);
	_movementComp->bOrientRotationToMovement = false;
	_movementComp->bUseControllerDesiredRotation = true;
	
	_springArmComponent->TargetOffset = FVector{ 0.0, 0.0, 100.0 };
}

void ULockOnComponent::StopLockOn()
{
	CurrentTargetActor = nullptr;
	
	_movementComp->bOrientRotationToMovement = true;
	_movementComp->bUseControllerDesiredRotation = false;
	_springArmComponent->TargetOffset = FVector::ZeroVector;

	_playerController->ResetIgnoreLookInput();
}

void ULockOnComponent::ToggleLockOn(float radius)
{
	if (IsValid(CurrentTargetActor))
	{
		StopLockOn();
	}
	else
	{
		StartLockOn(radius);
	}
}

// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 

	if (!IsValid(CurrentTargetActor))
	{
		return;
	}

	if (FVector::Distance(CurrentTargetActor->GetActorLocation(), _ownerRef->GetActorLocation()) > _autoUnlockRange)
	{
		StopLockOn();
		return;
	}

	FVector targetLocation = CurrentTargetActor->GetActorLocation();
	targetLocation.Z -= 125;

	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(_ownerRef->GetActorLocation(), targetLocation);

	_playerController->SetControlRotation(rotation);
}
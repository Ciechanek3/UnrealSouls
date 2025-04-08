// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockOnComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

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
	//_movementComp->
}

// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 

	if (!IsValid(CurrentTargetActor))
	{
		return;
	}

	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(_ownerRef->GetActorLocation(), CurrentTargetActor->GetActorLocation());

	_playerController->SetControlRotation(rotation);
}


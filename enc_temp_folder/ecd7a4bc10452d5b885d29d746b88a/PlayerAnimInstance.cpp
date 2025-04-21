// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateSpeed()
{
	APawn* pawn{ TryGetPawnOwner() };

	if (!IsValid(pawn)) return;

	FVector vector = pawn->GetVelocity();
	_currentSpeed = vector.Length();
}

void UPlayerAnimInstance::HandleUpdateTarget(AActor* actor)
{
	bIsInCombat = IsValid(actor);
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* pawn{ TryGetPawnOwner() };

	if (!IsValid(pawn)) return;

	if (!bIsInCombat) return;

	_currentSpeed = CalculateDirection(

		pawn->GetVelocity(),
		pawn->GetActorRotation()
	);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateVelocity()
{
	APawn* pawn{ TryGetPawnOwner() };

	if (!IsValid(pawn)) return;

	FVector vector = pawn->GetVelocity();
	_currentVelocity = vector.Length();
}

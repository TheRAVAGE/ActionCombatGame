// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

void UPlayerAnimInstance::UpdateVelocity()
{
	/* Getting reference to the Pawn owning this AnimInstance */
	APawn* PawnRef { TryGetPawnOwner() };
	
	/* Validating the Pawn reference
	 * If invalid, return early from the function
	 */
	if (!IsValid(PawnRef)) { return; }
	
	FVector Velocity { PawnRef->GetVelocity() };
	
	/* Good Practice to explicitly mention type conversions
	 * static_cast is used to convert Velocity.Length() to float
	 */
	CurrentVelocity = static_cast<float>(Velocity.Length());
}

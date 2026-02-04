// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "KismetAnimationLibrary.h"

void UPlayerAnimInstance::UpdateSpeed()
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
	CurrentSpeed = static_cast<float>(Velocity.Length());
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef { TryGetPawnOwner() };
	if (!IsValid(PawnRef)) { return; }
	if (!bIsInCombat) { return; }
	CurrentDirection = UKismetAnimationLibrary::CalculateDirection(
		PawnRef->GetVelocity(), 
		PawnRef->GetActorRotation()
		);
}

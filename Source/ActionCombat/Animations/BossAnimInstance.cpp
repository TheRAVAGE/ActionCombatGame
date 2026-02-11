// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCombat/Animations/BossAnimInstance.h"

void UBossAnimInstance::UpdateSpeed()
{
	/* Getting reference to the Pawn owning this AnimInstance */
	APawn* PawnRef { TryGetPawnOwner() };
	if (!IsValid(PawnRef)) { return; }
	FVector Velocity { PawnRef->GetVelocity() };
	CurrentSpeed = static_cast<float>(Velocity.Length());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "LockonComponent.h"

#include "ActionCombat/Interfaces/Enemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "../Interfaces/Enemy.h"

// Sets default values for this component's properties
ULockonComponent::ULockonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();
	ControllerRef = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
	
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation { OwnerRef->GetActorLocation() };
	FCollisionShape Sphere { FCollisionShape::MakeSphere(Radius) };
	FCollisionQueryParams IgnoreParams {
		FName(TEXT("Ignore Collision Params")),
		false,
		OwnerRef
	};
	
	bool bHasFoundTargets{GetWorld()->SweepSingleByChannel(
		OutResult, /* OutResult */
		CurrentLocation, /* Start */
		CurrentLocation, /* End */
		FQuat::Identity, /* Rotation */
		ECollisionChannel::ECC_GameTraceChannel1, /* Collision Channel */
		Sphere, /* Collision Shape */
		IgnoreParams
	)};
	if (!bHasFoundTargets){	return;	}
	
	/* Ensure if the Actor we get has the UEnemy Interface */
	if (!OutResult.GetActor()->Implements<UEnemy>()) { return; }
	
	CurrentTargetActor = OutResult.GetActor();
	
	UE_LOG(LogTemp, Warning, TEXT("Actor Detected : %s"), 
		*OutResult.GetActor()->GetName()
		);
	
	ControllerRef->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;
	SpringArmComp->TargetOffset = FVector(0.0f, 0.0f, 100.0f);
	
	IEnemy::Execute_OnSelect(CurrentTargetActor);
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::EndLockon()
{
	if (!IsValid(CurrentTargetActor) && !CurrentTargetActor->Implements<UEnemy>()) { return; }
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	
	CurrentTargetActor = nullptr;
	ControllerRef->ResetIgnoreLookInput();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->bUseControllerDesiredRotation = false;
	SpringArmComp->TargetOffset = FVector::ZeroVector;
	
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		EndLockon();
	} else
	{
		StartLockon(Radius);
	}
}

// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/* Only run if we have a valid target */
	if (!IsValid(CurrentTargetActor)) { return; }
	FVector CurrentLocation { OwnerRef->GetActorLocation() };
	FVector TargetLocation { CurrentTargetActor->GetActorLocation() };
	
	
	/* Breaks the lockon if player moves away from the target */
	double TargetDistance { FVector::Distance(CurrentLocation, TargetLocation) };
	if (TargetDistance >= BreakDistance)
	{
		EndLockon(); 
		return;
	}
	TargetLocation.Z -= 125.0f; /* Adjust for target's center mass */
	
	FRotator NewRotation { UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation) };
	ControllerRef->SetControlRotation(NewRotation);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	
	UE_LOG(LogTemp, Warning, TEXT("Actor Detected : %s"), 
		*OutResult.GetActor()->GetName()
		);
	
	ControllerRef->SetIgnoreLookInput(true);
	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;
}


// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


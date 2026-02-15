// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "PlayerActionsComponent.h"
#include "StatsComponent.h"
#include "ActionCombat/Characters/EStats.h"
#include "ActionCombat/Combat/BlockComponent.h"
#include "ActionCombat/Combat/LockonComponent.h"
#include "ActionCombat/Combat/CombatComponent.h"
#include "ActionCombat/Combat/TraceComponent.h"

#include "ActionCombat/Animations/PlayerAnimInstance.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	LockonComponent = CreateDefaultSubobject<ULockonComponent>(TEXT("Lockon Component"));
	BlockComponent = CreateDefaultSubobject<UBlockComponent>(TEXT("Block Component"));
	PlayerActionsComponent = CreateDefaultSubobject<UPlayerActionsComponent>(TEXT("Player Actions Component"));
	TraceComponent = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace Component"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMainCharacter::GetDamage()
{
	return StatsComponent->Stats[EStat::Strength];
}

bool AMainCharacter::HasenoughStamina(float StaminaCost)
{
	return StatsComponent->Stats[EStat::Stamina] >= StaminaCost;
}

void AMainCharacter::HandleDaeth()
{
	PlayAnimMontage(DeathAnimaMontage);
	DisableInput(GetController<APlayerController>());
}

void AMainCharacter::EndLockOnWithActor(AActor* ActorToUnlock)
{
	if (LockonComponent->CurrentTargetActor != ActorToUnlock) { return; }
	LockonComponent->EndLockon();
}

bool AMainCharacter::CanTakeDamage(AActor* Opponent)
{
	if (PlayerActionsComponent->bIsRollActive) { return false; }
	if (PlayerAnimInstance->bIsBlocking) 
	{
		return BlockComponent->Check(Opponent);
	}

	return true;

}

void AMainCharacter::PlayHurtAnim(TSubclassOf<class UCameraShakeBase> CameraShakeTemplate)
{
	PlayAnimMontage(HurtAnimMontage);
	if (CameraShakeTemplate)
	{
		GetController<APlayerController>()->ClientStartCameraShake(CameraShakeTemplate);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActionCombat/Interfaces/MainPlayer.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	CharacterRef = GetOwner<ACharacter>();
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::ComboAttack()
{
	if (CharacterRef->Implements<UMainPlayer>())
	{
		IMainPlayer* IPlayerRef = Cast<IMainPlayer>(CharacterRef);
		if (IPlayerRef && !IPlayerRef->HasenoughStamina(StaminaCost))
		{
			UE_LOG(LogTemp, Warning, TEXT("Not enough stamina to attack!"));
			return;
		}
	}
	if (!bCanAttack) {return;}
	bCanAttack = false;
	int MaxCombo{ AttackAnimations.Num() };
	UE_LOG(LogTemp, Warning, TEXT("Combo Attack! %d / %d"), ComboCounter, MaxCombo);
	CharacterRef->PlayAnimMontage(AttackAnimations[ComboCounter]);
	ComboCounter++;
	
	ComboCounter = UKismetMathLibrary::Wrap (
		ComboCounter, /* Value */
		-1, /* Min [Excluded] */
		(MaxCombo-1) /* Max [Included] */
		);
	
	OnAttackPerformedDelegate.Broadcast(StaminaCost);
}

void UCombatComponent::HandleResetAttack()
{
	bCanAttack = true;
}


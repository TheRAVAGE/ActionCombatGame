// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ActionCombat/Interfaces/Fighter.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::ReduceHealth(float Amount, AActor* Opponent)
{
	if (Stats[EStat::Health] <= 0) { return; }
	IFighter* FighterRef { GetOwner<IFighter>() };
	if (!FighterRef->CanTakeDamage(Opponent))
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, TEXT("Blocked"));
		return;
	}
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, TEXT("Not Blocked"));
	Stats[EStat::Health] -= Amount;
	Stats[EStat::Health] = UKismetMathLibrary::FClamp(
		Stats[EStat::Health], 
		0, 
		Stats[EStat::MaxHealth]
		);
	
	OnHealthPercentUpdatedDelegate.Broadcast(GetStatPerentage(EStat::Health, EStat::MaxHealth));
	if (Stats[EStat::Health] <= 0)
	{
		OnZeroHealthDelegate.Broadcast();
	}
}

void UStatsComponent::ReduceStamina(float Amount)
{
	Stats[EStat::Stamina] = UKismetMathLibrary::FClamp(
		Stats[EStat::Stamina]-Amount,
		0,
		Stats[EStat::MaxStamina]
		);
	bCanRegen = false;
	FLatentActionInfo FunctionInfo{
		0, /*Linkage*/
		100, /*UUID - Custom Number [Any number we want]*/
		TEXT("EnableRegenration"), /*FunctionName*/
		this /*CallbackTarget*/
	};
	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(), /*WorldContextObject*/ 
		StaminaRegenDelay, /*Duration*/ 
		FunctionInfo /*LatentInfo*/
		);
	OnStaminaPercentUpdatedDelegate.Broadcast(GetStatPerentage(EStat::Stamina, EStat::MaxStamina));
}

void UStatsComponent::RegenStamina()
{
	if (!bCanRegen) { return; }
	Stats[EStat::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStat::Stamina], /*Current*/
		Stats[EStat::MaxStamina], /*Target*/
		GetWorld()->GetDeltaSeconds(),	/*DeltaTime*/
		StaminaRegenRate /*InterpSpeed*/
	);
	OnStaminaPercentUpdatedDelegate.Broadcast(GetStatPerentage(EStat::Stamina, EStat::MaxStamina));
}

void UStatsComponent::EnableRegenration()
{
	bCanRegen = true;
}

float UStatsComponent::GetStatPerentage(EStat Current, EStat Max)
{
	return Stats[Current] / Stats[Max];
}


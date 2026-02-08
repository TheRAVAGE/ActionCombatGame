// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

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

void UStatsComponent::ReduceHealth(float Amount)
{
	if (Stats[EStat::Health] <= 0) { return; }
	Stats[EStat::Health] -= Amount;
	Stats[EStat::Health] = UKismetMathLibrary::FClamp(
		Stats[EStat::Health], 
		0, 
		Stats[EStat::MaxHealth]
		);
	
	UE_LOG(LogTemp,Warning, TEXT("Health: %f/%f"), Stats[EStat::Health], Stats[EStat::MaxHealth]);
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
}

void UStatsComponent::EnableRegenration()
{
	bCanRegen = true;
}


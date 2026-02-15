// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionCombat/Characters/EStats.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnHealthChangedSignature, /*DelegateName*/
	UStatsComponent, /*Class that owns the delegate*/
	OnHealthPercentUpdatedDelegate, /*Property name of the delegate*/
	float, Percentage /*Parameter type*/
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnStaminaChangedSignature, /*DelegateName*/
	UStatsComponent, /*Class that owns the delegate*/
	OnStaminaPercentUpdatedDelegate, /*Property name of the delegate*/
	float, Percentage /*Parameter type*/
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(
	FOnZeroHealthSignature, /*DelegateName*/
	UStatsComponent, /*Class that owns the delegate*/
	OnZeroHealthDelegate /*Property name of the delegate*/
	);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	double StaminaRegenRate{ 10.0f };
	
	UPROPERTY(EditAnywhere)
	float StaminaRegenDelay{ 2.0f };
	
	UPROPERTY(VisibleAnywhere)
	bool bCanRegen{ true };

public:	
	// Sets default values for this component's properties
	UStatsComponent();
	
	UPROPERTY(EditAnywhere, Category = "Stats")
	TMap<TEnumAsByte<EStat>, float> Stats;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthPercentUpdatedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnStaminaChangedSignature OnStaminaPercentUpdatedDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnZeroHealthSignature OnZeroHealthDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float Amount, AActor* Opponent);
	
	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float Amount);
	
	UFUNCTION(BlueprintCallable)
	void RegenStamina();
	
	UFUNCTION()
	void EnableRegenration();
	
	UFUNCTION(BlueprintPure)
	float GetStatPerentage(EStat Current, EStat Max);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature, /* DelegateName */
	UCombatComponent,/* Class that holds the Event */
	OnAttackPerformedDelegate, /* Event Name */
	float, Amount/* Parameter Type *//* Parameter Name */
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	
	ACharacter* CharacterRef;
	
	UPROPERTY(VisibleAnywhere, Category = "Combat | Debug")
	int32 ComboCounter{ 0 };
	
	UPROPERTY(VisibleAnywhere, Category = "Combat | Debug | Bools")
	bool bCanAttack{ true };
	
	UPROPERTY(EditAnywhere, Category = "Combat | Animations")
	TArray<UAnimMontage*> AttackAnimations;
	
	UPROPERTY(EditAnywhere, Category = "Combat | Stamina")
	float StaminaCost{ 5.f };

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	
	UPROPERTY(BlueprintAssignable, Category = "Combat | Delegates")
	FOnAttackPerformedSignature OnAttackPerformedDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ComboAttack();
	
	UFUNCTION(BlueprintCallable, Category = "Combat | Anim Notify")
	void HandleResetAttack();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


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

public:	
	// Sets default values for this component's properties
	UCombatComponent();

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

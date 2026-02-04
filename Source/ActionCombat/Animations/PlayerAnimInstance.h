// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category="Animation Properties")
	float CurrentSpeed { 0.0f };
	
	UFUNCTION(BlueprintCallable, Category="Animation Properties")
	void UpdateSpeed();
	
	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category="Animation Properties")
	bool bIsInCombat { false };
	
	UPROPERTY (EditAnywhere,BlueprintReadWrite, Category="Animation Properties")
	float CurrentDirection { 0.0f };
	
public:
	
	UFUNCTION(BlueprintCallable, Category="Animation Properties")
	void HandleUpdatedTarget(AActor* NewTargetActorRef);
	
	UFUNCTION(BlueprintCallable, Category="Animation Properties")
	void UpdateDirection();
};

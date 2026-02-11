// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Movement")
	float CurrentSpeed { 0.0f };
	
	UFUNCTION(BlueprintCallable, Category="Movement")
	void UpdateSpeed();
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Combat")
	bool bIsCharging { false };
};

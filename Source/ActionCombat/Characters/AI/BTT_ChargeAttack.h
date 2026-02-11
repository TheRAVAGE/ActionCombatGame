// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionCombat/Animations/BossAnimInstance.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ChargeAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UBTT_ChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	AAIController* ControllerRef;
	ACharacter* CharacterRef;
	UBossAnimInstance* BossAnimRef;
	
	FScriptDelegate MoveCompletedDelegate;
	
	UPROPERTY(EditAnywhere, Category="Base")
	float BaseMovementSpeed { 600.0f };
	
	UPROPERTY(EditAnywhere, Category="Base")
	float BaseAcceleration { 2048.0f };
	
	UPROPERTY(EditAnywhere, Category="Charge Attack")
	float AcceptableRadius { 100.0f };
	
	UPROPERTY(EditAnywhere, Category="Charge Attack")
	float ChargeMovementSpeed { 2000.0f };
	
	UPROPERTY(VisibleAnywhere)
	bool bIsFinished { false };
	
protected:
	virtual void TickTask ( 
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds
	)override;
	
public:
	UBTT_ChargeAttack();
	
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
		) override;
	
	void ChargeAtPlayer();
	
	UFUNCTION()
	void HandleMoveCompleted();

	UFUNCTION()
	void FinishAttackTask();
	
};

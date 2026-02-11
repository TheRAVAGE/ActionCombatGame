// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCombat/Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "ActionCombat/Characters/EEnemyState.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_ChargeAttack::UBTT_ChargeAttack()
{
	bNotifyTick = true;
	MoveCompletedDelegate.BindUFunction(
		this, /* Class responsible for this delegate */
		"HandleMoveCompleted" /* Function Name */
		);
}

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool bIsReadyToCharge = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsReadyToCharge"));
	if (bIsReadyToCharge)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReadyToCharge", false);
		ChargeAtPlayer();
	}
	if (!bIsFinished) {return;}
	
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"),EEnemyState::Melee);
	ControllerRef->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetPawn<ACharacter>();
	BossAnimRef = Cast<UBossAnimInstance>(CharacterRef->GetMesh()->GetAnimInstance());
	BossAnimRef->bIsCharging = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsReadyToCharge", false);
	bIsFinished = false;
	return EBTNodeResult::InProgress;
}

void UBTT_ChargeAttack::ChargeAtPlayer()
{
	APawn* PlayerRef {GetWorld()->GetFirstPlayerController()->GetPawn()};
	UCharacterMovementComponent* BossMovementComponent = Cast<UCharacterMovementComponent>(CharacterRef->GetMovementComponent());
	
	FVector PlayerLocation {PlayerRef->GetActorLocation()};
	FAIMoveRequest MoveRequest { PlayerLocation }; /* Create a move request to the player's location */
	MoveRequest.SetUsePathfinding(true);
	MoveRequest.SetAcceptanceRadius(AcceptableRadius);
	
	ControllerRef->MoveTo(MoveRequest);
	ControllerRef->SetFocus(PlayerRef);
	
	ControllerRef->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate); 
	/* Bind the move completed delegate to handle when the boss reaches the player or fails to reach them */
	
	BaseMovementSpeed = BossMovementComponent->MaxWalkSpeed; /* Store the original movement speed to reset it later */
	BossMovementComponent->MaxWalkSpeed = ChargeMovementSpeed; /* Increase the boss's movement speed for the charge attack */
	BossMovementComponent->MaxAcceleration = BaseAcceleration * 2; /* Increase acceleration to make the charge more responsive */
}

void UBTT_ChargeAttack::HandleMoveCompleted()
{
	BossAnimRef->bIsCharging = false;
	FTimerHandle AttackTimerHandle;
	CharacterRef->GetWorldTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&UBTT_ChargeAttack::FinishAttackTask,
		1.0f, /* Duration of the attack animation or effect */
		false /* Do not loop the timer */
		);
	UCharacterMovementComponent* BossMovementComponent = Cast<UCharacterMovementComponent>(CharacterRef->GetMovementComponent());
	BossMovementComponent->MaxWalkSpeed = BaseMovementSpeed; /* Reset movement speed to its original value */
	BossMovementComponent->MaxAcceleration = BaseAcceleration; /* Reset acceleration to its original value */
}

void UBTT_ChargeAttack::FinishAttackTask()
{
	bIsFinished = true;
}

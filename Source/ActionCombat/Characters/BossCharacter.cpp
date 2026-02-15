// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"

#include "StatsComponent.h"
#include "ActionCombat/Combat/CombatComponent.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ActionCombat/Characters/MainCharacter.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABossCharacter::ABossCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	ControllerRef = GetController<AAIController>();
	BlackboardComponent = ControllerRef->GetBlackboardComponent();
	BlackboardComponent->SetValueAsEnum(
		TEXT("CurrentState"), 
		InitialState
		);
	
	GetWorld()->GetFirstPlayerController()->GetPawn<AMainCharacter>()
	->StatsComponent
	->OnZeroHealthDelegate.AddDynamic(
		this, /*Object*/
		&ABossCharacter::HandlePlayerDeath /*Function*/
		);
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABossCharacter::DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect)
{
	EEnemyState CurrentState {static_cast<EEnemyState>(BlackboardComponent->GetValueAsEnum(TEXT("CurrentState")))};
	if (PawnToDetect != DetectedPawn || CurrentState != EEnemyState::Idle) { return; }
	BlackboardComponent->SetValueAsEnum(
		TEXT("CurrentState"), 
		EEnemyState::Range
		);
}

float ABossCharacter::GetDamage()
{
	return StatsComponent->Stats[EStat::Strength];
}

void ABossCharacter::Attack()
{
	CombatComponent->RandomAttack();
}

float ABossCharacter::GetAnimDuration()
{
	// return 0.0f;
	return CombatComponent->AnimDuration;
}

float ABossCharacter::GetMeleeRange()
{
	return StatsComponent->Stats[EStat::MeleeRange];
}

void ABossCharacter::HandlePlayerDeath()
{
	ControllerRef->GetBlackboardComponent()->SetValueAsEnum(
		TEXT("CurrentState"),
		EEnemyState::GameOver
		);
}

void ABossCharacter::HandleDeath()
{
	float duration {PlayAnimMontage(DeathAnimMontage)};
	ControllerRef->GetBrainComponent()->StopLogic(TEXT("Boss Died"));
	FindComponentByClass<UCapsuleComponent>()
		->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FTimerHandle DeathTimerHandle;
	GetWorldTimerManager().SetTimer(
		DeathTimerHandle,
		this, /*Object*/
		&ABossCharacter::FinishDeathAnimation, /*Function*/
		duration, /*Time*/
		false /*bLooping*/
	);
	IMainPlayer* PlayerRef { Cast<IMainPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn()) };
	if (!PlayerRef) { return; }
	PlayerRef->EndLockOnWithActor(this);
}

void ABossCharacter::FinishDeathAnimation()
{
	Destroy();
}


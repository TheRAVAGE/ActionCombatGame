// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/Enemy.h"

#include "ActionCombat/Characters/EEnemyState.h"
#include "BossCharacter.generated.h"

class UBlackboardComponent;

UCLASS()
class ACTIONCOMBAT_API ABossCharacter : public ACharacter, public IEnemy
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;
	
	UBlackboardComponent* BlackboardComponent;

public:
	// Sets default values for this character's properties
	ABossCharacter();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Components")
	class UStatsComponent* StatsComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect);
};

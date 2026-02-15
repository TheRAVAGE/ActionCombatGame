// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActionCombat/Interfaces/MainPlayer.h"
#include "ActionCombat/Interfaces/Fighter.h"
#include "MainCharacter.generated.h"

class UPlayerAnimInstance;

UCLASS()
class ACTIONCOMBAT_API AMainCharacter : public ACharacter, public IMainPlayer, public IFighter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Anim Montage | Death")
	UAnimMontage* DeathAnimaMontage;
	
	UPROPERTY(EditAnywhere, Category="Anim Montage | Hit")
	UAnimMontage* HurtAnimMontage;

public:
	// Sets default values for this character's properties
	AMainCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UStatsComponent* StatsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class ULockonComponent* LockonComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UBlockComponent* BlockComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UPlayerActionsComponent* PlayerActionsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UTraceComponent* TraceComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UCombatComponent* CombatComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category="Animation")
	UPlayerAnimInstance* PlayerAnimInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() override;
	virtual bool HasenoughStamina(float StaminaCost) override;
	
	UFUNCTION(BlueprintCallable, Category="Death")
	void HandleDaeth();
	
	virtual void EndLockOnWithActor(AActor* ActorToUnlock) override;
	
	virtual bool CanTakeDamage(AActor* Opponent) override;
	
	UFUNCTION(BlueprintCallable, Category="Hit")
	void PlayHurtAnim(TSubclassOf<class UCameraShakeBase> CameraShakeTemplate);
};

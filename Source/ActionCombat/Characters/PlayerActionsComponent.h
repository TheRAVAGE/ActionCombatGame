// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"


class IMainPlayer;
class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature, /*DelegateName*/
	UPlayerActionsComponent, /*UserClass*/
	OnSprintDelegate, /*FunctionName*/
	float, /*Param1Type*/ Cost /*Param1Name*/
	);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnRollSignature, /*DelegateName*/
	UPlayerActionsComponent, /*UserClass*/
	OnRollDelegate, /*FunctionName*/
	float, /*Param1Type*/ Cost /*Param1Name*/
	);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()
	
	ACharacter* CharacterRef;
	IMainPlayer* IPlayerRef;
	UCharacterMovementComponent* MovementComp;
	
	UPROPERTY(EditAnywhere, Category="Player Actions | Movement")
	float SprintCost{ 1.0f };
	UPROPERTY(EditAnywhere, Category="Player Actions | Movement")
	float SprintSpeed{ 1000.0f };
	UPROPERTY(EditAnywhere, Category="Player Actions | Movement")
	float WalkSpeed{ 500.0f };
	
	UPROPERTY(EditAnywhere, Category="Player Actions | Movement")
	UAnimMontage* RollAnimMontage;
	
	UPROPERTY(EditAnywhere, Category="Player Actions | Movement")
	float RollCost{ 5.0f };
	
	

public:	
	// Sets default values for this component's properties
	UPlayerActionsComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnRollSignature OnRollDelegate;
	
	bool bIsRollActive { false };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION( BlueprintCallable, Category = "Player Actions | Movement")
	void Sprint();
	UFUNCTION( BlueprintCallable, Category = "Player Actions | Movement")
	void Walk();
	UFUNCTION( BlueprintCallable, Category = "Player Actions | Movement")
	void Roll();
	
	UFUNCTION()
	void FinishRollAnim();
};

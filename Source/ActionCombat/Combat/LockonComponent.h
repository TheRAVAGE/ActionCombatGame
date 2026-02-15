// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"


class USpringArmComponent;
class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockonComponent,	OnUpdatedTargetDelegate,
	AActor*, NewTargetActorRef
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()
	
	ACharacter* OwnerRef;
	APlayerController* ControllerRef;
	UCharacterMovementComponent* MovementComp;
	USpringArmComponent* SpringArmComp;

public:	
	// Sets default values for this component's properties
	ULockonComponent();
	
	AActor* CurrentTargetActor;
	
	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	void StartLockon(float Radius = 750.0f);
	
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ToggleLockon(float Radius = 750.0f);
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	double BreakDistance{ 1000.0f };

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void EndLockon();
	
};

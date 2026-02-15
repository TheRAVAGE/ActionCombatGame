// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionCombat/Combat/FTraceSockets.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()
	
	USkeletalMeshComponent* SkeletalMeshComp;
	
	UPROPERTY(EditAnywhere, Category = "Trace|Sockets")
	TArray<FTraceSockets> Sockets;
	
	UPROPERTY(EditAnywhere, Category = "Trace|BoxCollision")
	double BoxCollisionLength {30.0f};
	
	UPROPERTY(EditAnywhere, Category = "Trace|BoxCollision")
	bool bDebugMode {false};
	
	TArray<AActor*> TargetsToIgnore;
	
	UPROPERTY(EditAnywhere, Category = "Trace|Hit")
	UParticleSystem* HitParticleTemplate;

public:	
	// Sets default values for this component's properties
	UTraceComponent();
	
	UPROPERTY(VisibleAnywhere, Category = "Trace|Debug")
	bool bIsAttacking {false};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

};

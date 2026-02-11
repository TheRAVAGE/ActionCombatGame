// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class ACTIONCOMBAT_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,Category="Hit Settings")
	UParticleSystem* HitTemplate;
	
	UPROPERTY(EditAnywhere,Category="Hit Settings")
	float Damage { 10.0f };
	
public:	
	// Sets default values for this actor's properties
	AEnemyProjectile();
	
	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* OtherActor);
	
	UFUNCTION()
	void DestroyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

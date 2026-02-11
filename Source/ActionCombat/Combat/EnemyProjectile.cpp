// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionCombat/Combat/EnemyProjectile.h"

#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyProjectile::HandleBeginOverlap(AActor* OtherActor)
{
	APawn* PawnRef {
		Cast<APawn>(OtherActor)
	};
	if (!PawnRef->IsPlayerControlled()) return;
	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();
	
	FTimerHandle DeathTimerHandle{};
	GetWorldTimerManager().SetTimer(
		DeathTimerHandle, /* Out Handle */
		this, /* Object */
		&AEnemyProjectile::DestroyProjectile, /* Function */
		0.5f, /* Time */
		false /* Looping */
	);
	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FDamageEvent ProjectileAttackEvent{};
	PawnRef->TakeDamage(
		Damage, /* Damage Amount */
		ProjectileAttackEvent, /* Damage Event */
		PawnRef->GetController(), /* Event Instigator */
		this /* Damage Causer */
	);
}

void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


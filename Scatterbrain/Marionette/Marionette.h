// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rig/MarionetteRigComponent.h"
#include "Physics/MarionettePhysicsComponent.h"
#include "Movement/MarionetteMovementComponent.h"
#include "Sight/MarionetteSightComponent.h"
#include "Narrative/MarionetteNarrativeComponent.h"
#include "Effects/MarionetteEffectsComponent.h"
#include "Abilities/MarionetteAbilitiesComponent.h"

#include "../General/Math.h" // Important!

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Marionette.generated.h"

class USceneComponent;
class UCameraComponent;
class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
class USkeletalMeshComponent;

UCLASS()
class SCATTERBRAIN_API AMarionette : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMarionette();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMarionetteRigComponent* Rig;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMarionettePhysicsComponent* Physics;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMarionetteMovementComponent* Movement;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMarionetteSightComponent* Sight;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMarionetteNarrativeComponent* Narrative;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMarionetteEffectsComponent* Effects;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UMarionetteAbilitiesComponent* Abilities;

	/*** Components ***/

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USceneComponent* PseudoRoot;
	
		UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UCameraComponent* FirstPersonCameraComponent;

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UCapsuleComponent* BodyColliderComponent;

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UCameraComponent* ThirdPersonCameraComponent;

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USpringArmComponent* SpringArmComponent;

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		USkeletalMeshComponent* SkeletalMeshComponent;

	/*** General ***/
	
		UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")
		float TickDeltaTime;

		/* Is all constants initialized? */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
		bool bIsConstantsDone;
	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

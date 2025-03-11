#pragma once

#include "../Types/TwoLimbs.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionetteRigComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionetteRigComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionetteRigComponent();

protected:
	// Called when the game starts
	// virtual void BeginPlay() override;

private:

	UPROPERTY()
	AMarionette* Owner;

public:

	////////////// FUNCTIONS //////////////

	UFUNCTION()
	void SetOwner(AMarionette* OwnerClass);
	
	UFUNCTION(BlueprintCallable)
	void InitRigVariables();

	UFUNCTION(BlueprintCallable)
	void UpdateRigVariables();

	////////////// VARIABLES //////////////
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector RootLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator RootRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector HeadLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator HeadRotation;

	// Control Rig Goal location for head.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector HeadGoalLocation;

	// Control Rig Goal rotation for head.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator HeadGoalRotation;

	TWO_LIMBS_DEF(LegRootLocation, FVector)
	TWO_LIMBS_DEF(LegRootRotation, FRotator)
	TWO_LIMBS_DEF(KneeLocation, FVector)
	TWO_LIMBS_DEF(KneeRotation, FRotator)
	TWO_LIMBS_DEF(FootLocation, FVector)
	TWO_LIMBS_DEF(FootRotation, FRotator)
	TWO_LIMBS_DEF(ToeLocation, FVector)
	TWO_LIMBS_DEF(ToeRotation, FRotator)
	/* Foot Ik goal location. */
	TWO_LIMBS_DEF(FootGoalLocation, FVector)
	/* Foot Ik goal rotation. */
	TWO_LIMBS_DEF(FootGoalRotation, FRotator)
	TWO_LIMBS_DEF(FootAlphaIK, float)

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector PelvisLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator PelvisRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RootKneeLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float KneeFootLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FootToeLength;

	/* RootKneeLength + KneeFootLength */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LegLength;

	/* RootKneeLength + KneeFootLength + FootToeLength */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LegLengthTiptoes;

	/* Min distance between Leg Root and Foot. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RootFootMinLength;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float FootBoneGroundOffset;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ToeBoneGroundOffset;

	////////////// CONSTANTS //////////////
	
	/* Distance from pelvis bone the surface of a chair when marionette is sitting or laying. [m] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float PelvisHitDistance;
};
#pragma once

#include "../Types/LeftRight.h"

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
	void LoadLengthData();

	UFUNCTION(BlueprintCallable)
	void UpdateBoneData();

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> LegRootLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRotator> LegRootRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> KneeLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRotator> KneeRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> FootLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRotator> FootRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> ToeLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRotator> ToeRotation;
	
	/* Foot Ik goal location. */;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> FootGoalLocation;
	
	/* Foot Ik goal rotation. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRotator> FootGoalRotation;
	
	/* Toe Ik goal location. */;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> ToeGoalLocation;
	
	/* Toe Ik goal rotation. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRotator> ToeGoalRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<float> FootAlphaIK;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector PelvisLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator PelvisRotation;

	// [units]
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RootKneeLength;

	// [units]
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float KneeFootLength;

	// [units]
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FootToeLength;

	/* RootKneeLength + KneeFootLength [units] */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LegLength;

	/* RootKneeLength + KneeFootLength + FootToeLength [units] */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LegLengthTiptoes;

	/* Min distance between Leg Root and Foot. [units] */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RootFootMinLength;

	// [units]
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float FootBoneGroundOffset;

	// [units]
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ToeBoneGroundOffset;

	////////////// CONSTANTS //////////////
	
	/* Distance from pelvis bone the surface of a chair when marionette is sitting or laying. [m] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float PelvisHitDistance;

	/* The angle at which the foot bone should rotate when standing on the toes. (relative to T-pose) [deg] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TiptoesAngle;
};
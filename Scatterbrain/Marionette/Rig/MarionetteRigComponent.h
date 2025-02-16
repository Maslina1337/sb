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

	UFUNCTION(BlueprintCallable)
	void AttachGoalsToBones();

	////////////// VARIABLES //////////////
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector RootLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator RootRotation;

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

	/* Foot Ik goal location. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> FootGoalLocation;

	/* Foot Ik goal rotation. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRotator> FootGoalRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ClampMin = "0", ClampMax = "1"))
	TArray<float> FootAlphaIK;

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
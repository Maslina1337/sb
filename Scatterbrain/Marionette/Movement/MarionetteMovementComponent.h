#pragma once

#include "../Types/EMove.h"

#include "PassiveMoves/Walk/PM_Walk.h"
#include "ActiveMoves/Step/AM_Step.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionetteMovementComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionetteMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionetteMovementComponent();

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
	void SetMovementDirectionByVector2D(const FVector2D Input);

	/* Automatically chooses passive move to execute later. */
	UFUNCTION(BlueprintCallable)
	void ChoosePassiveMove();

	/* Executes current passive move. */
	UFUNCTION(BlueprintCallable)
	void ExecutePassiveMove();

	/* Executes current active moves. */
	UFUNCTION(BlueprintCallable)
	void ExecuteActiveMoves();

	UFUNCTION(BlueprintCallable)
	void AttachFootToHit(FVector& CurrentFootLocation, FHitResult Hit);
	
	////////////// VARIABLES //////////////

	// WASD input.
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FVector2D InputVector;

	// XY Movement Direction, rotates to sight Z.
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FVector2D MovementDirection;

	// XYZ Movement Direction take in count sight rotation, rotates to sight XYZ.
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FVector MovementDirectionSpace;

	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	bool bIsRunning;

	////////////// CONSTANTS //////////////

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector FootBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float LegWidth;
	
	// Walk

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SideWalkAngleBegin;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SideWalkAngleEnd;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float WalkStepDirectionChangeCoefficient;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float RaysFarRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float IterationsCountOfLocationClarify;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float StepSpeedWalk;

	// Fall

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MaxMovementAchievableInertiaSpeed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float MovementFallInertiaAcceleration;
	
private:
	UPROPERTY(EditAnywhere)
	EPassiveMove CurrentPassiveMove;

	UPROPERTY(EditAnywhere)
	EPassiveMove PastPassiveMove;

	UPROPERTY(EditAnywhere)
	TArray<EActiveMove> CurrentActiveMoves;

	UPROPERTY(EditAnywhere)
	TArray<EActiveMove> PastActiveMoves;
	
public:
	// Passive moves.
	FPM_Walk* PM_Walk;
	
	// Active moves.
	FAM_Step* AM_Step;
	
	UFUNCTION(BlueprintCallable)
	void SetPassiveMove(const EPassiveMove NewMove);

	UFUNCTION(BlueprintCallable)
	void AddActiveMove(const EActiveMove NewMove);
	
	UFUNCTION(BlueprintCallable)
	void DeleteActiveMove(const EActiveMove Move);

	UFUNCTION(BlueprintCallable)
	int32 FindCurrentActiveMove(const EActiveMove Move) const; /* int32 'cause it can return -1.
	And int16 isn't supported in Blueprints. */

	UFUNCTION(BlueprintCallable)
	int32 FindPastActiveMove(const EActiveMove Move) const; /* int32 'cause it can return -1.
	And int16 isn't supported in Blueprints. */

	UFUNCTION(BlueprintCallable)
	bool ItsFirstIterationPassive(const EPassiveMove Move) const;

	UFUNCTION(BlueprintCallable)
	bool ItsFirstIterationActive(const EActiveMove Move) const;

	/// Getters ///
	UFUNCTION(BlueprintCallable)
	EPassiveMove GetCurrentPassiveMove() const;

	UFUNCTION(BlueprintCallable)
	EPassiveMove GetPastPassiveMove() const;

	UFUNCTION(BlueprintCallable)
	EActiveMove GetCurrentActiveMoveByIndex(const uint8 Index) const;

	UFUNCTION(BlueprintCallable)
	EActiveMove GetPastActiveMoveByIndex(const uint8 Index) const;

	UFUNCTION(BlueprintCallable)
	TArray<EActiveMove> GetCurrentActiveMoves();

	UFUNCTION(BlueprintCallable)
	TArray<EActiveMove> GetPastActiveMoves();
};
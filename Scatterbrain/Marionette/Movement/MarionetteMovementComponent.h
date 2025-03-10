#pragma once

#include "../Types/EMove.h"

// Moves forward declaration.
class FPM_Walk;
class FPM_Fall;
class FAM_Step;

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
	void SetMovementDirectionByInput(const FVector2D Input);

	/* Automatically chooses passive move to execute later. */
	UFUNCTION(BlueprintCallable)
	void ChoosePassiveMove();

	/* Executes current passive move. */
	UFUNCTION(BlueprintCallable)
	void ExecutePassiveMove();

	/* Executes current active moves. */
	UFUNCTION(BlueprintCallable)
	void ExecuteActiveMoves();
	
	////////////// VARIABLES //////////////

	// WASD input.
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FVector2D InputVector;

	// Movement projected and normalized on gravity direction plane. (usually XY)
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FVector MovementDirection;

	// XY Movement Direction, rotates to sight Z.
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FVector2D MovementDirectionXY;

	// XYZ Movement Direction take in count sight rotation, rotates to sight XYZ.
	UPROPERTY(BlueprintReadWrite, EditAnywhere) 
	FVector MovementDirectionXYZ;
	
private:
	UPROPERTY(EditAnywhere)
	EPassiveMove CurrentPassiveMove;

	UPROPERTY(EditAnywhere)
	EPassiveMove PastPassiveMove;

	UPROPERTY(EditAnywhere)
	TArray<EActiveMove> CurrentActiveMoves;
	
public:
	// Passive moves.
	FPM_Walk* PM_Walk;
	FPM_Fall* PM_Fall;
	
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
	
	/// Getters ///
	UFUNCTION(BlueprintCallable)
	EPassiveMove GetCurrentPassiveMove() const;

	UFUNCTION(BlueprintCallable)
	EPassiveMove GetPastPassiveMove() const;

	UFUNCTION(BlueprintCallable)
	EActiveMove GetCurrentActiveMoveByIndex(const uint8 Index) const;
	
	UFUNCTION(BlueprintCallable)
	TArray<EActiveMove> GetCurrentActiveMoves();
};
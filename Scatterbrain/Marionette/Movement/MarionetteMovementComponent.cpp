#include "MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

// Moves includes (do not move it to .h [template classes such as TActiveMove will break.])
#include "PassiveMoves/Walk/PM_Walk.h"
#include "PassiveMoves/Fall/PM_Fall.h"
#include "ActiveMoves/Step/AM_Step.h"

#include "PassiveMoves/PassiveMove.h"
#include "ActiveMoves/ActiveMove.h"

// Sets default values for this component's properties
UMarionetteMovementComponent::UMarionetteMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Owner = nullptr;
	
	// Passive moves.
	PM_Walk = NewObject<FPM_Walk>();
	PM_Fall = NewObject<FPM_Fall>();
	
	// Active moves.
	AM_Step = NewObject<FAM_Step>();
	
	CurrentPassiveMove = PM_Fall;
	PastPassiveMove = PM_Fall;
}

void UMarionetteMovementComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;

	PM_Walk->SetOwner(Owner);
	PM_Fall->SetOwner(Owner);
	
	AM_Step->SetOwner(Owner);
}

void UMarionetteMovementComponent::SetPassiveMove(FPassiveMove* NewMove)
{
	PastPassiveMove = CurrentPassiveMove;
	CurrentPassiveMove = NewMove;
}

void UMarionetteMovementComponent::AddActiveMove(FActiveMove* NewMove)
{
	// If this Move is already in array it won't be added.
	for (int8 i = 0; i < CurrentActiveMoves.Num(); i++)
	{
		if (CurrentActiveMoves[i] == NewMove) return;
	}
	
	CurrentActiveMoves.Add(NewMove);
}

void UMarionetteMovementComponent::DeleteActiveMove(FActiveMove* Move)
{
	int8 Index = -1;
	for (int8 i = 0; i < CurrentActiveMoves.Num(); i++)
	{
		if (CurrentActiveMoves[i] == Move) Index = i;
	}

	// If nothing changing we don't need to change past active move.
	if (Index == -1) return;
	
	CurrentActiveMoves.RemoveAt(Index);
}

int32 UMarionetteMovementComponent::FindCurrentActiveMove(FActiveMove* Move) const
{
	int16 Index = -1;
	for (uint8 i = 0; i < CurrentActiveMoves.Num(); i++)
	{
		if (CurrentActiveMoves[i] == Move) Index = i;
	}
	return Index;
}

/// Getters ///
FPassiveMove* UMarionetteMovementComponent::GetCurrentPassiveMove() const
{
	return CurrentPassiveMove;
}

FPassiveMove* UMarionetteMovementComponent::GetPastPassiveMove() const
{
	return PastPassiveMove;
};

FActiveMove* UMarionetteMovementComponent::GetCurrentActiveMoveByIndex(const uint8 Index) const
{
	if (Index <= CurrentActiveMoves.Num() - 1)
	{
		return CurrentActiveMoves[Index];
	}

	return nullptr;
}

TArray<FActiveMove*> UMarionetteMovementComponent::GetCurrentActiveMoves()
{
	return CurrentActiveMoves;
};
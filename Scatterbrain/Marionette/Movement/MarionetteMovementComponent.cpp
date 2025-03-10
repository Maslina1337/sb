#include "MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

// Moves includes (do not move it to .h [template classes such as TActiveMove will break.])
#include "PassiveMoves/Walk/PM_Walk.h"
#include "PassiveMoves/Fall/PM_Fall.h"
#include "ActiveMoves/Step/AM_Step.h"

// Sets default values for this component's properties
UMarionetteMovementComponent::UMarionetteMovementComponent()
{
	Owner = nullptr;
	
	// Passive moves.
	PM_Walk = new FPM_Walk(Owner);
	PM_Fall = new FPM_Fall(Owner);
	
	// Active moves.
	AM_Step = new FAM_Step(Owner);
	
	CurrentPassiveMove = EPassiveMove::Fall;
	PastPassiveMove = EPassiveMove::Fall;
}

void UMarionetteMovementComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}

void UMarionetteMovementComponent::SetPassiveMove(const EPassiveMove NewMove)
{
	PastPassiveMove = CurrentPassiveMove;
	CurrentPassiveMove = NewMove;
}

void UMarionetteMovementComponent::AddActiveMove(const EActiveMove NewMove)
{
	// If this Move is already in array it won't be added.
	for (int8 i = 0; i < CurrentActiveMoves.Num(); i++)
	{
		if (CurrentActiveMoves[i] == NewMove)
		{
			return;
		}
	}
	
	CurrentActiveMoves.Add(NewMove);
}

void UMarionetteMovementComponent::DeleteActiveMove(const EActiveMove Move)
{
	int8 Index = -1;
	for (int8 i = 0; i < CurrentActiveMoves.Num(); i++)
	{
		if (CurrentActiveMoves[i] == Move)
		{
			Index = i;
		}
	}

	// If nothing changing we don't need to change past active move.
	if (Index == -1)
	{
		return;
	}
	
	CurrentActiveMoves.RemoveAt(Index);
}

int32 UMarionetteMovementComponent::FindCurrentActiveMove(const EActiveMove Move) const
{
	int16 Index = -1;
	for (uint8 i = 0; i < CurrentActiveMoves.Num(); i++)
	{
		if (CurrentActiveMoves[i] == Move)
		{
			Index = i;
		}
	}
	return Index;
}

/// Getters ///
EPassiveMove UMarionetteMovementComponent::GetCurrentPassiveMove() const
{
	return CurrentPassiveMove;
}

EPassiveMove UMarionetteMovementComponent::GetPastPassiveMove() const
{
	return PastPassiveMove;
};

EActiveMove UMarionetteMovementComponent::GetCurrentActiveMoveByIndex(const uint8 Index) const
{
	if (Index <= CurrentActiveMoves.Num() - 1)
	{
		return CurrentActiveMoves[Index];
	}
	
	return EActiveMove::None;
}

TArray<EActiveMove> UMarionetteMovementComponent::GetCurrentActiveMoves()
{
	return CurrentActiveMoves;
};
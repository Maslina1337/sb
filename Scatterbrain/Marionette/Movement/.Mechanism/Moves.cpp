#pragma once

#include "../MarionetteMovementComponent.h"
#include "../../Marionette.h"

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
	
	PastActiveMoves = CurrentActiveMoves;
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
	
	PastActiveMoves = CurrentActiveMoves;
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

int32 UMarionetteMovementComponent::FindPastActiveMove(const EActiveMove Move) const
{
	int16 Index = -1;
	for (uint8 i = 0; i < PastActiveMoves.Num(); i++)
	{
		if (PastActiveMoves[i] == Move)
		{
			Index = i;
		}
	}
	return Index;
}

bool UMarionetteMovementComponent::ItsFirstIterationPassive(const EPassiveMove Move) const
{
	return (PastPassiveMove != Move);
}

bool UMarionetteMovementComponent::ItsFirstIterationActive(const EActiveMove Move) const
{
	return (FindPastActiveMove(Move) == -1);
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

EActiveMove UMarionetteMovementComponent::GetPastActiveMoveByIndex(const uint8 Index) const
{
	if (Index <= PastActiveMoves.Num() - 1)
	{
		return PastActiveMoves[Index];
	}
	
	return EActiveMove::None;
}

TArray<EActiveMove> UMarionetteMovementComponent::GetCurrentActiveMoves()
{
	return CurrentActiveMoves;
};

TArray<EActiveMove> UMarionetteMovementComponent::GetPastActiveMoves()
{
	return PastActiveMoves;
};
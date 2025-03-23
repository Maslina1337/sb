#include "../MarionetteMovementComponent.h"

#include "Scatterbrain/Marionette/Movement/ActiveMoves/Step/AM_Step.h"

void UMarionetteMovementComponent::ExecuteActiveMoves()
{
	for (uint8 i = 0; i < GetCurrentActiveMoves().Num(); i++)
	{
		GetCurrentActiveMoveByIndex(i)->TickManual();
	}
}
#include "../MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Movement/PassiveMoves/PassiveMove.h"

void UMarionetteMovementComponent::ExecutePassiveMove()
{
	GetCurrentPassiveMove()->TickManual();
}

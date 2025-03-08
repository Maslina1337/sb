#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"

void UMarionettePhysicsComponent::ApplyAbsoluteAcceleration(FVector Acceleration)
{
	InertiaVelocity += Acceleration * pow(Owner->TickDeltaTime, 2) / 2;
}
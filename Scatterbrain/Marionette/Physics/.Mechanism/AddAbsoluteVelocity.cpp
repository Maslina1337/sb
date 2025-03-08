#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"

void UMarionettePhysicsComponent::AddAbsoluteVelocity(FVector Velocity)
{
	InertiaVelocity += Velocity;
}
#include "../MarionettePhysicsComponent.h"

void UMarionettePhysicsComponent::Reset() {
	if (States->GetBodyState() == EPhysicState::Stable)
		{
			GravitationalShift = FVector::ZeroVector;
			GravitationalVelocity = FVector::ZeroVector;

			InertiaShift = FVector::ZeroVector;
			InertiaVelocity = FVector::ZeroVector;
		}
}
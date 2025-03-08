#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"

void UMarionettePhysicsComponent::ApplyAbsoluteForce(FVector Force)
{
	const FEFCT_MassRevision* MassRevisionPtr = Owner->Effects->MassRevision;
	const float AsMass = (MassRevisionPtr->IsActive() ? MassRevisionPtr->GetParams().Mass : Mass);
	
	InertiaVelocity += (Force / AsMass) * pow(Owner->TickDeltaTime, 2) / 2;
}
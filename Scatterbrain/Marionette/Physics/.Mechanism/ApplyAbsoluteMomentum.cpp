﻿#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"

void UMarionettePhysicsComponent::ApplyAbsoluteMomentum(FVector Momentum)
{
	const FEFCT_MassRevision* MassRevisionPtr = Owner->Effects->MassRevision;
	const float AsMass = (MassRevisionPtr->IsActive() ? MassRevisionPtr->GetParams().Mass : Mass);
	
	InertiaVelocity += Momentum / AsMass;
}
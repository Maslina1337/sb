﻿#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"

void UMarionettePhysicsComponent::ApplyMomentum(FVector Momentum)
{
	FEFCT_MassRevision* MassRevisionPtr = Owner->Effects->MassRevision;
	const float AsMass = (MassRevisionPtr->IsActive() ? MassRevisionPtr->GetParams().Mass : Mass);

	FEFCT_MassRevision_Params DebugStuff;
	DebugStuff.Mass = 2;
	MassRevisionPtr->Activate(10, DebugStuff);
	
	InertiaSpeed += Momentum / AsMass;
}
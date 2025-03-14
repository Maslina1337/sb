#pragma once
#include "Scatterbrain/Marionette/Types/FParamsStrict.h"

// Step will use this params on start.

struct FAM_Step_Params final : FParamsStrict 
{
	FAM_Step_Params()
	{
		TargetPoint = FVector::ZeroVector;
		Act = false;
		Sup = false;
		StepVelocity = 1.f;
	}
	
	virtual ~FAM_Step_Params() override {};
	
	FVector TargetPoint; // The place where the foot should end up.
	bool Act;
	bool Sup;

	// [m/s]
	float StepVelocity;
};
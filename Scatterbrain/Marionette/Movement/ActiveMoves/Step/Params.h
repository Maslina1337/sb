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
		OverthrowAngle = 10.f;
		TimeToGoTiptoe = 0.2f;
	}

	FAM_Step_Params(const FVector& TargetPoint_, bool Act_, bool Sup_, float StepVelocity_, float OverthrowAngle_, float TimeToGoTiptoe_)
	{
		TargetPoint = TargetPoint_;
		Act = Act_;
		Sup = Sup_;
		StepVelocity = StepVelocity_;
		OverthrowAngle = OverthrowAngle_;
		TimeToGoTiptoe = TimeToGoTiptoe_;
	}
	
	virtual ~FAM_Step_Params() override {};
	
	FVector TargetPoint; // The place where the toe should end up.
	bool Act;
	bool Sup;

	// [m/s]
	float StepVelocity;

	// Angle of foot overthrow after it appear above the target point (InertialThrow Stage) [deg]
	float OverthrowAngle;

	// The time it takes for the foot to stand on its toes. (GoTiptoe Stage) [s]
	float TimeToGoTiptoe;
};
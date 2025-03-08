#pragma once

#include "Scatterbrain/Marionette/Types/EWalkSides.h"

class AMarionette;

class FPM_Walk
{
public:
	FPM_Walk(AMarionette*);
	
	void Tick();
private:
	AMarionette* Owner;

	// Variables //
	float AngleVisionToMoveDirection;
	
	EWalkSide GetWalkSideByAngle();

	FVector FootBox;
	float SideWalkAngleBegin;
	float SideWalkAngleEnd;
	float WalkStepDirectionChangeCoefficient;
	float RaysFarRotation;
	int8 IterationsCountOfLocationClarify;
	float StepVelocityWalk;
};
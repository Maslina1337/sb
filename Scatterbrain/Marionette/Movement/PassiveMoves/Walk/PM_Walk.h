#pragma once

#include "Scatterbrain/Marionette/Types/EWalkSides.h"
#include "Scatterbrain/Marionette/Movement/PassiveMoves/PassiveMove.h"

class AMarionette;

class FPM_Walk final : public FPassiveMove
{
public:
	
	FPM_Walk();
	
private:
	float AngleVisionToMoveDirection;

	void virtual Progress() override;
	
	EWalkSide GetWalkSideByAngle();

	FVector FootBox;
	float SideWalkAngleBegin;
	float SideWalkAngleEnd;
	float WalkStepDirectionChangeCoefficient;
	float RaysFarRotation;
	int8 IterationsCountOfLocationClarify;
	float StepVelocityWalk;
};
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
};
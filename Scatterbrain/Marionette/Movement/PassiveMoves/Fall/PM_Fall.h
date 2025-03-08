#pragma once

#include "Scatterbrain/Marionette/Types/EWalkSides.h"

class AMarionette;

class FPM_Fall
{
public:
	FPM_Fall(AMarionette*);
	
	void Tick();

	// Getters //
	FVector GetLandingDirection() const { return LandingDirection; }
	float GetAnimLandingReady() const { return AnimLandingReady; }

private:
	AMarionette* Owner;

	// Variables //
	bool LandingReadyLeg[2];
	
	float MaxInertiaVelocityAbleToIncrease;
	float InertiaAcceleration;

	// The direction in which the toes are ready to land.
	FVector LandingDirection;
	
	float AnimLandingReady;
};
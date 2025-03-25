#pragma once

#include "Scatterbrain/Marionette/Movement/PassiveMoves/PassiveMove.h"

class AMarionette;

class FPM_Fall final : public FPassiveMove
{
public:
	
	FPM_Fall();

	// Getters //
	FVector GetLandingDirection() const { return LandingDirection; }
	float GetAnimLandingReady() const { return AnimLandingReady; }

private:
	
	void virtual Progress() override;
	
	bool LandingReadyLeg[2];
	
	float MaxInertiaVelocityAbleToIncrease;
	float InertiaAcceleration;

	// The direction in which the toes are ready to land.
	FVector LandingDirection;
	
	float AnimLandingReady;
};
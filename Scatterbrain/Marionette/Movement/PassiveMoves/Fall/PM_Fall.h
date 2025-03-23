#pragma once

#include "Scatterbrain/Marionette/Types/EWalkSides.h"
#include "Scatterbrain/Marionette/Movement/PassiveMoves/PassiveMove.h"

class AMarionette;

class UPM_Fall final : public UPassiveMove
{
public:
	UPM_Fall();

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
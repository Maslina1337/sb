#pragma once

#include "Scatterbrain/Marionette/Types/FSurfCheckReturn.h"
#include "../Types/EPhysStates.h"

class AMarionette;

class IStates {
public:
	explicit IStates(AMarionette*);

private:
	
	AMarionette* Owner;
	
	EBodyPhysState BodyState;
	EBodyPhysState PastBodyState;
	bool bIsStableMoment;
	bool bIsUnstableMoment;

	// To leave surfing state 2 conditions must be met:
	// • Trace in the direction of the normal of the surf surface from pelvis
	//   should not encounter obstacles at a distance of PelvisHitDistance.
	// • Traces of legs should not encounter a surface that will obstruct the surf.
	bool bIsBodySurfing;
	
	void UpdateMoments();
	
public:

	// Update leg states.
	void StatesUpdate();
	
	void CopyCurrentToPast();
	
	FSurfCheckReturn SurfCheck(const FHitResult& Hit) const;

	//// Getters. ////
	
	EBodyPhysState GetBodyState() const { return BodyState; };
	EBodyPhysState GetPastBodyState() const { return PastBodyState; };
	bool GetIsLandingMoment() const { return bIsStableMoment; };
	bool GetIsUnstableMoment() const { return bIsUnstableMoment; };
};
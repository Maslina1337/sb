#pragma once

#include "Scatterbrain/Marionette/Types/TwoLimbs.h"
#include "Scatterbrain/Marionette/Types/FSurfCheckReturn.h"
#include "../Types/EPhysStates.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionettePhysicsComponent.generated.h"

class AMarionette;

class IStates {
public:
	explicit IStates(AMarionette*);

private:
	
	AMarionette* Owner;

	TArray<EFootPhysState> FootState;
	TArray<EFootPhysState> PastFootState;
	EBodyPhysState BodyState;
	EBodyPhysState PastBodyState;
	bool bIsStableMoment;
	bool bIsUnstableMoment;
	bool bIsBodyStable;
	bool bPastIsBodyStable;

	// // To leave surfing state 2 conditions must be met:
	// // • Trace in the direction of the normal of the surf surface from pelvis
	// //   should not encounter obstacles at a distance of PelvisHitDistance.
	// // • Traces of legs should not encounter a surface that will obstruct the surf.
	// bool bIsBodySurfing;

	// Simple update leg states.
	void SimpleStatesUpdate(const EFootPhysState NewLeftLegState, const EFootPhysState NewRightLegState);

	void AutoSetIsBodyStable();
	void AutoSetBodyState(TArray<FHitResult>& FootHit);
	void AutoSetMoments();

	// // Check if 2 conditions of surfing state exit are met (check description of bIsBodySurfing for more info).
	// void CheckSurfExit();
	
public:

	// Update leg states.
	void StatesUpdate(TArray<bool> IsFootHit, TArray<FHitResult> FootHit);
	
	void CopyCurrentToPast();
	
	FSurfCheckReturn LegSurfCheck(const FHitResult& Hit) const;

	//// Getters. ////
	
	EFootPhysState GetFootState(const uint8 Limb) const { return FootState[Limb]; };
	EFootPhysState GetPastFootState(const uint8 Limb) const { return PastFootState[Limb]; };
	EBodyPhysState GetBodyState() const { return BodyState; };
	EBodyPhysState GetPastBodyState() const { return PastBodyState; };
	bool GetIsBodyStable() const { return bIsBodyStable; };
	bool GetPastIsBodyStable() const { return bPastIsBodyStable; };
	bool GetIsStableMoment() const { return bIsStableMoment; };
	bool GetIsUnstableMoment() const { return bIsUnstableMoment; };
};
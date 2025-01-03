#include "States.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Types/TwoLimbs.h"

using namespace TwoLimbs;

IStates::IStates(AMarionette* OwnerClass)
{
	Owner = OwnerClass;

	TWO_LIMBS_INIT(FootState, EFootPhysState);
	TWO_LIMBS_INIT(PastFootState, EFootPhysState);

	FootState[Left] = EFootPhysState::Air;
	FootState[Right] = EFootPhysState::Air;
	BodyState = EBodyPhysState::Fall;
	PastFootState[Left] = EFootPhysState::Air;
	PastFootState[Right] = EFootPhysState::Air;
	PastBodyState = EBodyPhysState::Fall;
	bIsStableMoment = false;
	bIsUnstableMoment = false;
	bIsBodyStable = false;
	bPastIsBodyStable = false;
	bIsBodySurfing = false;
}


// Update leg states according to Hit results.
void IStates::StatesUpdate(TArray<bool> IsFootHit, TArray<FHitResult> FootHit)
{
	EFootPhysState NewLeftLegState;
	EFootPhysState NewRightLegState;

	// Logical exception: if the stablest state of legs is surfing and pelvis state is stable, then body state is surf.
	
	

	// TODO Implement surf mechanics.
	
	// Left leg.

	if (IsFootHit[Left])
	{
		if (LegSurfCheck(FootHit[Left]).IsSurf) NewLeftLegState = EFootPhysState::Surf;
		else NewLeftLegState = EFootPhysState::Fulcrum;
	}
	else NewLeftLegState = EFootPhysState::Air;

	// Right leg.

	if (IsFootHit[Right])
	{
		if (LegSurfCheck(FootHit[Right]).IsSurf) NewRightLegState = EFootPhysState::Surf;
		else NewRightLegState = EFootPhysState::Fulcrum;
	}
	else NewRightLegState = EFootPhysState::Air;

	SimpleStatesUpdate(NewLeftLegState, NewRightLegState);
	AutoSetIsBodyStable();
	AutoSetBodyState(FootHit);
}

void IStates::CopyCurrentToPast()
{
	PastFootState[Left] = FootState[Left];
	PastFootState[Right] = FootState[Right];
	PastBodyState = BodyState;
	bPastIsBodyStable = bIsBodyStable;
}

void IStates::SimpleStatesUpdate(const EFootPhysState NewLeftLegState, const EFootPhysState NewRightLegState)
{
	CopyCurrentToPast();

	FootState[Left] = NewLeftLegState;
	FootState[Right] = NewRightLegState;
}

void IStates::AutoSetIsBodyStable()
{
	bIsBodyStable = (FootState[Left] == EFootPhysState::Fulcrum || FootState[Right] == EFootPhysState::Fulcrum);
}

void IStates::AutoSetBodyState(TArray<FHitResult>& FootHit)
{
	// Is both lags landed?
	if (FootState[Left] == EFootPhysState::Fulcrum && FootState[Right] == EFootPhysState::Fulcrum)
	{
		BodyState = (FootHit[Left].Distance < FootHit[Right].Distance ? EBodyPhysState::LandingLeft : EBodyPhysState::LandingRight);
	}
	// Is only left leg landed?
	else if (FootState[Left] == EFootPhysState::Fulcrum)
	{
		BodyState = EBodyPhysState::LandingLeft;
	}
	// Is only right leg landed?
	else if (FootState[Right] == EFootPhysState::Fulcrum)
	{
		BodyState = EBodyPhysState::LandingRight;
	}
	// No fulcrum leg, so any leg surfing?
	else if (FootState[Left] == EFootPhysState::Surf || FootState[Right] == EFootPhysState::Surf)
	{
		BodyState = EBodyPhysState::Surf;
	} else
	{
		BodyState = EBodyPhysState::Fall;
	}
}


void IStates::AutoSetMoments()
{
	bIsStableMoment = (bIsBodyStable && !bPastIsBodyStable);
	bIsUnstableMoment = (!bIsBodyStable && bPastIsBodyStable);
}

FSurfCheckReturn IStates::LegSurfCheck(const FHitResult& Hit) const {
	FSurfCheckReturn Answer;
	Answer.AngleOfIncidence = AngleBetweenTwoVectors(FVector::UpVector, Hit.Normal);
	Answer.IsSurf = (Answer.AngleOfIncidence > Owner->Physics->SurfingAngle);
	return Answer;
}
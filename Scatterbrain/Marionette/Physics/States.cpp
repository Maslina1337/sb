#include "States.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Physics/MarionettePhysicsComponent.h"

IStates::IStates(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
	
	BodyState = EBodyPhysState::Fall;
	PastBodyState = EBodyPhysState::Fall;
	bIsStableMoment = false;
	bIsUnstableMoment = false;
	bIsBodySurfing = false;
}

// Update leg states according to Hit results.
void IStates::StatesUpdate()
{
	CopyCurrentToPast();

	if (Owner->Physics->bIsToesHit)
	{
		if (SurfCheck(Owner->Physics->ToesHit).IsSurf) BodyState = EBodyPhysState::Surf;
		else BodyState = EBodyPhysState::Stable;
	}
	else BodyState = EBodyPhysState::Fall;
}

void IStates::CopyCurrentToPast()
{
	PastBodyState = BodyState;
}

void IStates::UpdateMoments()
{
	bIsStableMoment = (BodyState == EBodyPhysState::Stable && PastBodyState != EBodyPhysState::Stable);
	bIsUnstableMoment = (BodyState != EBodyPhysState::Stable && PastBodyState == EBodyPhysState::Stable);
}

FSurfCheckReturn IStates::SurfCheck(const FHitResult& Hit) const {
	FSurfCheckReturn Answer;
	Answer.AngleOfIncidence = AngleBetweenTwoVectors(FVector::UpVector, Hit.Normal);
	Answer.IsSurf = (Answer.AngleOfIncidence > Owner->Physics->SurfingAngle);
	return Answer;
}
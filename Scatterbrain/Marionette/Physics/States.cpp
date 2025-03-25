#include "States.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Physics/MarionettePhysicsComponent.h"

IStates::IStates(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
	
	BodyState = EPhysicState::Fall;
	PastBodyState = EPhysicState::Fall;
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
		if (SurfCheck(Owner->Physics->ToesHit).IsSurf) BodyState = EPhysicState::Surf;
		else BodyState = EPhysicState::Stable;
	}
	else BodyState = EPhysicState::Fall;
}

void IStates::CopyCurrentToPast()
{
	PastBodyState = BodyState;
}

void IStates::UpdateMoments()
{
	bIsStableMoment = (BodyState == EPhysicState::Stable && PastBodyState != EPhysicState::Stable);
	bIsUnstableMoment = (BodyState != EPhysicState::Stable && PastBodyState == EPhysicState::Stable);
}

FSurfCheckReturn IStates::SurfCheck(const FHitResult& Hit) const {
	FSurfCheckReturn Answer;
	Answer.AngleOfIncidence = AngleBetweenTwoVectors(FVector::UpVector, Hit.Normal);
	Answer.IsSurf = (Answer.AngleOfIncidence > Owner->Physics->SurfingAngle);
	return Answer;
}
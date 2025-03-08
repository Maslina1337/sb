#include "PM_Fall.h"
#include "../../../Marionette.h"

FPM_Fall::FPM_Fall(AMarionette* NewOwner)
{
	Owner = NewOwner;
	
	LandingReadyLeg[0] = false;
	LandingReadyLeg[1] = false;

	MaxInertiaVelocityAbleToIncrease = 600.f;
	InertiaAcceleration = 200.f;

	LandingDirection = FVector::DownVector;
}

void FPM_Fall::Tick()
{
	Owner->Physics->ApplyAbsoluteAcceleration(Owner->Movement->MovementDirection * InertiaAcceleration);

	// Setting the Landing direction. **TEMP WAY**
	if (AngleBetweenTwoVectors(Owner-> Physics->FallVelocity, FVector::DownVector) < 90)
	{
		LandingDirection = Owner->Physics->FallVelocity.GetSafeNormal();
	} else
	{
		LandingDirection = Owner->Physics->FallVelocity.ProjectOnToNormal(FVector::DownVector).GetSafeNormal();
	}
}

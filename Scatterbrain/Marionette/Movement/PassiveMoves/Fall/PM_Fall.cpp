#include "PM_Fall.h"
#include "../../../Marionette.h"
#include "Scatterbrain/Marionette/Physics/MarionettePhysicsComponent.h"
#include "Scatterbrain/Marionette/Movement/MarionetteMovementComponent.h"

UPM_Fall::UPM_Fall()
{
	LandingReadyLeg[0] = false;
	LandingReadyLeg[1] = false;

	MaxInertiaVelocityAbleToIncrease = 600.f;
	InertiaAcceleration = 200.f;

	LandingDirection = FVector::DownVector;

	AnimLandingReady = 1.f;

	DebugName = "PM_Fall";
}

void UPM_Fall::Progress()
{
	UE_LOG(LogTemp, Error, TEXT("NEW PROGRESS"))
	
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

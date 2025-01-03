#include "../AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"

void FAM_Step::TransferWeight()
{
	// X, Y

	const FVector ActLocation = Owner->Rig->FootLocation[Params.Act];
	const FVector SupLocation = Owner->Rig->FootLocation[Params.Sup];

	NewActorLocationXY = FVector2D(
		ActLocation.X - SupLocation.X,
		ActLocation.Y - SupLocation.Y);
	NewActorLocationXY /= 2;
	NewActorLocationXY += FVector2D(SupLocation.X, SupLocation.Y);

	const FVector SupToTarget = Params.TargetPoint - SupLocation;
	const FVector ActorTargetXY = FVector((SupLocation + SupToTarget).X, (SupLocation + SupToTarget).Y, 0);
	const FVector ActorFullShiftXY = ActorTargetXY - FVector(ActLocationOnStepStart.X, ActLocationOnStepStart.Y, 0);
	const FVector ActorShiftXY = ActorFullShiftXY * StepPercent;

	// Z

	const FVector ActorLocation = Owner->GetActorLocation();
	const FVector ActorLocationXY = FVector(ActorLocation.X, ActorLocation.Y, 0);

	const FVector SupLocationXY = FVector(SupLocation.X, SupLocation.Y, 0);

	// Is this an unstable support?
	if ((ActorTargetXY - SupLocationXY).Length() > FulcrumZoneRadius)
	{
		
	}
}
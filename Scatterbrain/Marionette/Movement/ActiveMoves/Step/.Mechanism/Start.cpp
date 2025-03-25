#include "../AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Types/LeftRight.h"
#include "Scatterbrain/Marionette/Physics/MarionettePhysicsComponent.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"

using namespace LeftRight;

void FAM_Step::Start()
{
	Owner->Physics->PhysicsIgnore = true;
	ActorLocationOnStart = Owner->GetActorLocation();
	ActLocationOnStart = Owner->Rig->ToeLocation[Params.Act];
	RoundingCircle = FCircle2D(Vector3To2(Owner->Rig->ToeLocation[Params.Sup]), RoundingRadius);

	// Step Length and Height.
	
	StepHeight = ActLocationOnStart.Z - Params.TargetPoint.Z;
	StepLength = FVector2D(
		Owner->Rig->ToeLocation[Params.Act].X - Params.TargetPoint.X,
		Owner->Rig->ToeLocation[Params.Act].Y - Params.TargetPoint.Y
		).Length();

	// Setting Step vertical direction.
	
	if (StepHeight > StraightHeightDifference) StepVerticalDirection = EStepVerticalDirection::Upstairs;
	else if (StepHeight < -StraightHeightDifference) StepVerticalDirection = EStepVerticalDirection::Downstairs;
	else StepVerticalDirection = EStepVerticalDirection::Straight;
	
	//// Setting Rounding.
	
	// Is legs cross placed?
	if ((Owner->Rig->ToeLocation[Params.Act] - Owner->Rig->LegRootLocation[Params.Sup]).Length() >
		(Owner->Rig->ToeLocation[Params.Sup] - Owner->Rig->LegRootLocation[Params.Sup]).Length() &&
		(Owner->Rig->ToeLocation[Params.Act] - Owner->Rig->LegRootLocation[Params.Act]).Length() >
		(Owner->Rig->ToeLocation[Params.Sup] - Owner->Rig->LegRootLocation[Params.Act]).Length())
	{
		bNeedRounding = true;

		// Setting Is Clockwise.
		const FVector MarionetteDirection = Owner->GetActorRotation().RotateVector(FVector::ForwardVector);
		
		TArray<FVector> PelvisToKnee;
		PelvisToKnee.Init(FVector(), 2);

		PelvisToKnee[Params.Act] = Owner->Rig->PelvisLocation - Owner->Rig->KneeLocation[Params.Act];
		PelvisToKnee[Params.Sup] = Owner->Rig->PelvisLocation - Owner->Rig->KneeLocation[Params.Sup];

		// Is Act Leg Knee Forwarded?
		if (GetProjectionLength(PelvisToKnee[Params.Act], MarionetteDirection, true) >
			GetProjectionLength(PelvisToKnee[Params.Sup], MarionetteDirection, true))
		{
			bIsRoundingClockwise = Params.Act != Left;
		}
		else
		{
			bIsRoundingClockwise = Params.Act == Left;
		}
	}
	else
	{
		bNeedRounding = DistanceBetweenLineAndPoint(
		Vector3To2(Owner->Rig->ToeLocation[Params.Sup]),
		Vector3To2(ActLocationOnStart),
		Vector3To2(Params.TargetPoint)) < RoundingRadius;
		
		bIsRoundingClockwise = Params.Act == Left;
	}

	//// Setting all rounding path length's and tangent points locations. ////

	if (bNeedRounding)
	{
		RoundingTangentPointStart = FindTangentPoint(Vector3To2(Owner->Rig->ToeLocation[Params.Act]),
			RoundingCircle,
			bIsRoundingClockwise);
		
		RoundingTangentPointEnd = FindTangentPoint(Vector3To2(Params.TargetPoint),
			RoundingCircle,
			!bIsRoundingClockwise);

		RoundingStartToArcPathLength = (RoundingTangentPointStart - Vector3To2(Owner->Rig->ToeLocation[Params.Act])).Length();
		RoundingArcPathLength = GetArcLength(RoundingCircle, RoundingTangentPointStart, RoundingTangentPointEnd);
		RoundingArcToEndPathLength = (Vector3To2(Params.TargetPoint) - RoundingTangentPointEnd).Length();
		RoundingFullPathLength = RoundingStartToArcPathLength + RoundingArcPathLength + RoundingArcToEndPathLength;
	}

	Progress();
}
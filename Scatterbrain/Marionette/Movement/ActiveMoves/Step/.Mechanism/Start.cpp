#include "../AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Types/LeftRight.h"
#include "Scatterbrain/Marionette/Physics/MarionettePhysicsComponent.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"

using namespace LeftRight;

void FAM_Step::Start()
{
	Owner->Physics->PhysicsIgnore = true;
	ActorLocationOnStepStart = Owner->GetActorLocation();
	ActLocationOnStepStart = Owner->Rig->FootLocation[Params.Act];
	StepPercent = 0.0f;
	SupRoundingCircle = FCircle2D(Vector3To2(Owner->Rig->FootLocation[Params.Sup]), RoundingRadius);

	// Differences.
	
	StepHeight = ActLocationOnStepStart.Z - Params.TargetPoint.Z;
	StepLength = FVector2D(
		Owner->Rig->FootLocation[Params.Act].X - Owner->Rig->FootLocation[Params.Sup].X,
		Owner->Rig->FootLocation[Params.Act].Y - Owner->Rig->FootLocation[Params.Sup].Y
		).Length();

	//// Setting Is Possible To Reach Fulcrum Zone Standing. ////

	const FVector ActToTarget = Params.TargetPoint - Params.Act;
	const FVector2D TargetOnPlane = FVector2D(FVector2D(ActToTarget.X, ActToTarget.Y).Length(), ActToTarget.Z);
	const FVector2D TopLeft = FVector2D(TargetOnPlane.X - FulcrumZoneRadius, TargetOnPlane.Y + FulcrumZoneHeightOffset + 1000); // 1000 Is need to be replaced. For now IDK.
	const FVector2D BottomRight = FVector2D(TargetOnPlane.X + FulcrumZoneRadius, TargetOnPlane.Y + FulcrumZoneHeightOffset);
	const FRectangle2D FulcrumZone = FRectangle2D(TopLeft, BottomRight);
	const FCircle2D StraightLegTrajectory = FCircle2D(FVector2D(0), Owner->Rig->LegLength);
	
	bIsPossibleToReachFulcrumZoneStanding = IsRectangleIntersectingCircle(FulcrumZone, StraightLegTrajectory);

	//// Setting Is Rounding and Rounding Clockwise. ////

	// Is legs cross placed?
	if ((Owner->Rig->FootLocation[Params.Act] - Owner->Rig->LegRootLocation[Params.Sup]).Length() >
		(Owner->Rig->FootLocation[Params.Sup] - Owner->Rig->LegRootLocation[Params.Sup]).Length() &&
		(Owner->Rig->FootLocation[Params.Act] - Owner->Rig->LegRootLocation[Params.Act]).Length() >
		(Owner->Rig->FootLocation[Params.Sup] - Owner->Rig->LegRootLocation[Params.Act]).Length())
	{
		NeedRounding = true;

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
			IsRoundingClockwise = Params.Act != Left;
		}
		else
		{
			IsRoundingClockwise = Params.Act == Left;
		}
	}
	else
	{
		NeedRounding = DistanceBetweenLineAndPoint(
		Vector3To2(Owner->Rig->FootLocation[Params.Sup]),
		Vector3To2(ActLocationOnStepStart),
		Vector3To2(Params.TargetPoint)) < RoundingRadius;

		// Setting Is Clockwise.
		IsRoundingClockwise = Params.Act == Left;
	}

	//// Setting all rounding path length's and tangent points locations. ////

	if (NeedRounding)
	{
		RoundingTangentPointStart = FindTangentPoint(Vector3To2(Owner->Rig->FootLocation[Params.Act]),
			SupRoundingCircle,
			IsRoundingClockwise);
		
		RoundingTangentPointEnd = FindTangentPoint(Vector3To2(Params.TargetPoint),
			SupRoundingCircle,
			!IsRoundingClockwise);

		RoundingStartToArcPathLength = (RoundingTangentPointStart - Vector3To2(Owner->Rig->FootLocation[Params.Act])).Length();
		RoundingArcPathLength = GetArcLength(SupRoundingCircle, RoundingTangentPointStart, RoundingTangentPointEnd);
		RoundingArcToEndPathLength = (Vector3To2(Params.TargetPoint) - RoundingTangentPointEnd).Length();
		RoundingFullPathLength = RoundingStartToArcPathLength + RoundingArcPathLength + RoundingArcToEndPathLength;
	}
}
#include "../AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"

// Two points. One point have two fields describing it location in space: Vertical and Horizontal.
struct FTwoPoints2D
{
	FVector2D Highest;
	FVector2D Lowest;
	FVector2D Left;
	FVector2D Right;
};

void FAM_Step::MoveFoot()
{
	FVector NewFootLocation;
	
	FTwoPoints2D ExtremePoint;
	
	ExtremePoint.Highest.X = FootTrajectoryInverse(MaxStepHeight / (MaxStepHeight + FootTrajectoryLimit)) *
		(StepHeight > 0 ? 1 : -1) + 0.5f;
	ExtremePoint.Highest.Y = FootTrajectory(ExtremePoint.Highest.X);

	ExtremePoint.Lowest.Y = 1 - (StepHeight / MaxStepHeight) * ExtremePoint.Highest.Y;
	ExtremePoint.Lowest.X = 0.5f + FootTrajectoryInverse(ExtremePoint.Lowest.Y) * (StepHeight > 0 ? -1 : 1);

	if (StepHeight > 0)
	{
		ExtremePoint.Left.X = ExtremePoint.Lowest.X;
		ExtremePoint.Left.Y = ExtremePoint.Lowest.Y;
		// ExtremePoint.Right.X = ExtremePoint.Highest.X;
		// ExtremePoint.Right.Y = ExtremePoint.Highest.Y;
	}
	else
	{
		ExtremePoint.Left.X = ExtremePoint.Highest.X;
		ExtremePoint.Left.Y = ExtremePoint.Highest.Y;
		// ExtremePoint.Right.X = ExtremePoint.Lowest.X;
		// ExtremePoint.Right.Y = ExtremePoint.Lowest.Y;
	}

	FVector2D CurrentPoint;
	CurrentPoint.X = StepPercent * abs(ExtremePoint.Highest.X - ExtremePoint.Lowest.X) + ExtremePoint.Left.X;
	CurrentPoint.Y = FootTrajectory(CurrentPoint.X);

	// Intermediate value. (Z only)
	NewFootLocation.Z = (CurrentPoint.Y - ExtremePoint.Left.Y) /
		abs(ExtremePoint.Highest.Y - ExtremePoint.Lowest.Y) * StepLength;

	FVector2D RoundingShift;
	
	// Need Rounding?
	if (NeedRounding)
	{
		const float CurrentPathTraveled = StepPercent * RoundingFullPathLength;
		if (CurrentPathTraveled - RoundingStartToArcPathLength > 0)
		{
			if (CurrentPathTraveled - RoundingArcPathLength > 0)
			{
				// Rounding from arc to end.
				const float SegmentTraveledPercent = CurrentPathTraveled -
					(RoundingStartToArcPathLength + RoundingArcPathLength) /
					RoundingArcToEndPathLength;

				const FVector2D SegmentVector = Vector3To2(Params.TargetPoint) - RoundingTangentPointEnd;

				RoundingShift = SegmentVector.GetSafeNormal() * SegmentTraveledPercent;
			}
			else
			{
				// Rounding on arc.
				const float SegmentTraveledPercent = CurrentPathTraveled - RoundingStartToArcPathLength;

				GetPointOnArc(SupRoundingCircle,
					RoundingTangentPointStart,
					RoundingTangentPointEnd,
					SegmentTraveledPercent);
			}
		}
		else
		{
			// Rounding from start to arc.
			const float SegmentTraveledPercent = CurrentPathTraveled;

			const FVector2D SegmentVector = RoundingTangentPointStart - Vector3To2(ActLocationOnStepStart);

			RoundingShift = SegmentVector.GetSafeNormal() * SegmentTraveledPercent;
		}
	}

	// Combining Rounding (X & Y) and Trajectory (Z)
	NewFootLocation += Vector2To3(RoundingShift);
	
	// Applying new location.
	Owner->Rig->FootGoalLocation[Params.Act] = NewFootLocation;
}
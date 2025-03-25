#include "../AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"

// Two points. One point have two fields describing it location in space: Vertical and Horizontal.
struct FTwoPoints2D
{
	FVector2D Highest;
	FVector2D Lowest;
	FVector2D Leftest;
	FVector2D Rightest;
};

void FAM_Step::MoveFoot()
{
	FVector NewFootLocation;

	if (StepVerticalDirection != EStepVerticalDirection::Straight)
	{
		// FTwoPoints2D ExtremePoint;
		//
		// ExtremePoint.Highest.X = FootTrajectoryInverse(MaxStepHeight / (MaxStepHeight + FootTrajectoryLimit)) *
		// 	(StepHeight > 0 ? 1 : -1) + 0.5f;
		// ExtremePoint.Highest.Y = FootTrajectory(ExtremePoint.Highest.X);
		//
		// ExtremePoint.Lowest.Y = 1 - (StepHeight / MaxStepHeight) * ExtremePoint.Highest.Y;
		// ExtremePoint.Lowest.X = 0.5f + FootTrajectoryInverse(ExtremePoint.Lowest.Y) * (StepHeight > 0 ? -1 : 1);
		//
		// if (StepHeight > 0)
		// {
		// 	ExtremePoint.Leftest.X = ExtremePoint.Lowest.X;
		// 	ExtremePoint.Leftest.Y = ExtremePoint.Lowest.Y;
		// }
		// else
		// {
		// 	ExtremePoint.Leftest.X = ExtremePoint.Highest.X;
		// 	ExtremePoint.Leftest.Y = ExtremePoint.Highest.Y;
		// }
		//
		// FVector2D CurrentPoint;
		// CurrentPoint.X = StepPercent * abs(ExtremePoint.Highest.X - ExtremePoint.Lowest.X) + ExtremePoint.Leftest.X;
		// CurrentPoint.Y = FootTrajectory(CurrentPoint.X);
		//
		// // Intermediate value. (Z only)
		// NewFootLocation.Z = (CurrentPoint.Y - ExtremePoint.Leftest.Y) /
		// 	abs(ExtremePoint.Highest.Y - ExtremePoint.Lowest.Y) * StepLength;
	}

	if (StepStage == EStepStage::GoTiptoe)
	{
		
		float FramePathTravelled = Params.StepVelocity * 100.f * Owner->TickDeltaTime;

		if (FramePathTravelled > )
	}

	FVector2D RoundingShift = FVector2D::ZeroVector;
	
	// Need Rounding?
	if (bNeedRounding)
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

				GetPointOnArc(RoundingCircle,
					RoundingTangentPointStart,
					RoundingTangentPointEnd,
					SegmentTraveledPercent);
			}
		}
		else
		{
			// Rounding from start to arc.
			const float SegmentTraveledPercent = CurrentPathTraveled;

			const FVector2D SegmentVector = RoundingTangentPointStart - Vector3To2(ActLocationOnStart);

			RoundingShift = SegmentVector.GetSafeNormal() * SegmentTraveledPercent;
		}
	}

	// Combining Rounding (X & Y) and Trajectory (Z)
	NewFootLocation += Vector2To3(RoundingShift);
	
	// Applying new location.
	Owner->Rig->FootGoalLocation[Params.Act] = NewFootLocation;
}
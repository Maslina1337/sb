#pragma once

#include "Params.h"
#include "Scatterbrain/General/Math.h"
#include "../ActiveMove.h"

class AMarionette;

class FAM_Step final : public TActiveMove<FAM_Step_Params>
{
public:
	
	FAM_Step(AMarionette* Owner_);
	
private:
	
	virtual void Start() override; // Executed on first frame active.
	virtual void Progress() override; // Executed every tick (starting on second frame active).
	virtual void End() override; // Not executed automatically. Can be called manually in progress when it's done.
	
	void TransferWeight(); // Transfer body weight.
	void MoveFoot(); // Reach your foot towards the point.
	
	float FootTrajectory(float X);
	float FootTrajectoryInverse(float Y);

private:
	
	FVector ActorLocationOnStepStart;
	FVector ActLocationOnStepStart;

	float StepHeight;
	float StepLength;

	FVector2D NewActorLocationXY;
	float NewActorLocationZ;

	float StepPercent;

	// Is it possible to reach the fulcrum zone without lifting the act foot off the ground?
	bool bIsPossibleToReachFulcrumZoneStanding;

	FCircle2D SupRoundingCircle;

	// Rounding. (Setting on step start...)
	bool NeedRounding;
	bool IsRoundingClockwise;
	float RoundingFullPathLength;
	float RoundingStartToArcPathLength;
	float RoundingArcPathLength;
	float RoundingArcToEndPathLength;
	FVector2D RoundingTangentPointStart;
	FVector2D RoundingTangentPointEnd;

private:
	
	// The radius of the circular XY zone around the foot.
	// If the Body is outside this zone, the foot is no longer considered a support.
	const float FulcrumZoneRadius = 20;

	// The offset of the fulcrum zone from the foot vertically upwards.
	// The Fulcrum Zone is considered to be only what is above.
	const float FulcrumZoneHeightOffset = 20;
	
	// If the difference in step height is greater or less,
	// it is considered that the marionette is not walking on a straight surface, but, for example, on steps.
	const float StraightSurfaceHeightDiff = 15;
	
	// This value indicates how many units the leg rises when stepping on a straight surface.
	const float FootTrajectoryLimit = 10.0f;

	// Maximal difference between start fool location and target point.
	const float MaxStepHeight = 50.0f; // Vertical difference.
	const float MaxStepLength = 50.0f; // Horizontal difference.

	const float RoundingRadius = 5.f; // Radius of rounding. 
};

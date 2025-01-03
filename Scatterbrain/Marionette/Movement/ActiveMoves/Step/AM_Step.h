#pragma once

#include "Params.h"
#include "Scatterbrain/Marionette/Types/EWalkSides.h"
#include "Scatterbrain/General/Math.h"

class AMarionette;

class FAM_Step
{
public:
	FAM_Step(AMarionette*);
	
	void SetParams(FAM_Step_Params);
	void Tick();
	
private:
	//// FUNCTIONALITY ////

	// GENERAL //
	void Start();
	void Progress();
	void End();

	// OTHER //
	void TransferWeight(); // Transfer body weight.
	void MoveFoot(); // Reach your foot towards the point.

	FVector2D FindTangentPoint(const FVector2D Point, const FCircle2D Circle, const bool IsLeftTangent);
	FVector2D GetPointOnArc(const FCircle2D Circle, const FVector2D TangentA, const FVector2D TangentB, float ArcLength);
	float GetArcLength(const FCircle2D Circle, const FVector2D TangentA, const FVector2D TangentB);
	
	float FootTrajectory(float X);
	float FootTrajectoryInverse(float Y);

	//// VARIABLES ////

	// GENERAL //
	bool ParamsIsNull; // On creating instance is true. When we first time set params it's become forever false. 
	FAM_Step_Params Params; // Can be changed only when step isn't started yet.
	FAM_Step_Params ParamsFree; // Can be changed at any time.
	AMarionette* Owner; // Marionette instance.

	// OTHER //
	FVector ActorLocationOnStepStart;
	FVector ActLocationOnStepStart;

	float StepHeight;
	float StepLength;

	FVector2D NewActorLocationXY;
	float NewActorLocationZ;

	float StepPercent;

	// Is it possible to reach the fulcrum zone without lifting the act foot off the ground?
	bool bIsPossibleToReachFulcrumZoneStanding;

	FCircle2D SupLegWidthCircle;

	// Rounding. (Setting on step start...)
	bool NeedRounding;
	bool IsRoundingClockwise;
	float RoundingFullPathLength;
	float RoundingStartToArcPathLength;
	float RoundingArcPathLength;
	float RoundingArcToEndPathLength;
	FVector2D RoundingTangentPointStart;
	FVector2D RoundingTangentPointEnd;
	

	//// CONSTANTS ////

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
};

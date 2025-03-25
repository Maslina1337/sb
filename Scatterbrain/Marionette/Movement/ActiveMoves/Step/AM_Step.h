#pragma once

#include "Params.h"
#include "Scatterbrain/General/Math.h"
#include "../ActiveMove.h"

class AMarionette;

/*
	Step consists of 4 stages:
	 • Act leg stands on tiptoe.
	 • From the current lift the foot rushes (accelerated) to the place above the target point.
	 • Foot throws farther from target point by inertia.
	 • Body moves forward around the sup foot and based on the calculations, the foot slowly moves towards the target
	 and touches the target with its heel at the earliest moment when it theoretically can.
*/
enum class EStepStage : uint8
{
	GoTiptoe,
	RushToTarget,
	InertialThrow,
	SlowMoveToTarget,
};

enum class EStepVerticalDirection : uint8
{
	Upstairs,
	Straight,
	Downstairs,
};

class FAM_Step final : public TActiveMove<FAM_Step_Params>
{
public:
	
	FAM_Step();
	
private:
	
	virtual void Start() override; // Executed on first frame active.
	virtual void Progress() override; // Executed every tick (starting on second frame active).
	virtual void End() override; // Not executed automatically. Can be called manually in progress when it's done.

	// Called in constructor, so you should use IT as a constructor for non-constants.
	// Also, can be called manually to reset variables to default values.
	virtual void Reset() override;

private:
	
	void TransferWeight(); // Transfer body weight.
	void MoveFoot(); // Reach your foot towards the point.
	
	float FootTrajectory(float X);
	float FootTrajectoryInverse(float Y);

private:
	
	FVector ActorLocationOnStart; // Location of the Actor when step started.
	FVector ActLocationOnStart; // Location of the Act foot when step started.

	float StepHeight;
	float StepLength;

	

	FVector NewActorLocation;

	float StepPercent;

	FCircle2D RoundingCircle;

	// Rounding. (Setting on step start...)
	bool bNeedRounding;
	bool bIsRoundingClockwise; // Clockwise looking from top.
	float RoundingFullPathLength;
	float RoundingStartToArcPathLength;
	float RoundingArcPathLength;
	float RoundingArcToEndPathLength;
	FVector2D RoundingTangentPointStart;
	FVector2D RoundingTangentPointEnd;

	// See enum description for more info.
	EStepStage StepStage;

	EStepVerticalDirection StepVerticalDirection;

	// Stages.
	//float RushToTargetFootPath;
	// ....
	
	//float StateFootPathTravelled;

private:
	
	// If the difference in step height is greater or less,
	// it is considered that the marionette is not walking on a straight surface, but, for example, on steps. [units]
	const float StraightHeightDifference = 15;
	
	// This value indicates how many units the leg rises when stepping on a straight surface.
	const float FootTrajectoryLimit = 10.0f;

	// Maximal difference between start fool location and target point.
	const float MaxStepHeight = 50.0f; // Vertical difference.
	const float MaxStepLength = 50.0f; // Horizontal difference.

	const float RoundingRadius = 5.f; // Radius of rounding. 
};

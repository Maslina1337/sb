#include "AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Types/LeftRight.h"

void FAM_Step::Reset()
{
	ActorLocationOnStart = FVector::ZeroVector;
	ActLocationOnStart = FVector::ZeroVector;

	StepHeight = 0.f;
	StepLength = 0.f;

	NewActorLocation = FVector::ZeroVector;

	StepPercent = 0.f;

	RoundingCircle = FCircle2D();
	
	bNeedRounding = false;
	bIsRoundingClockwise = false;
	RoundingFullPathLength = 0.f;
	RoundingStartToArcPathLength = 0.f;
	RoundingArcPathLength = 0.f;
	RoundingArcToEndPathLength = 0.f;
	RoundingTangentPointStart = FVector2D::ZeroVector;
	RoundingTangentPointEnd = FVector2D::ZeroVector;

	StepStage = EStepStage::GoTiptoe;
	StepVerticalDirection = EStepVerticalDirection::Straight;
}

FAM_Step::FAM_Step() : TActiveMove()
{
	Reset();
	DebugName = "AM_Step";
}
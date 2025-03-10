#include "AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"

FAM_Step::FAM_Step(AMarionette* Owner_) : TActiveMove(Owner_)
{
	EnumName = EActiveMove::Step;
	
	ActorLocationOnStepStart = FVector::ZeroVector;
	ActLocationOnStepStart = FVector::ZeroVector;

	StepHeight = 0.f;
	StepLength = 0.f;

	NewActorLocationXY = FVector2D::ZeroVector;
	NewActorLocationZ = 0.f;

	StepPercent = 0.f;
	
	bIsPossibleToReachFulcrumZoneStanding = false;

	SupRoundingCircle = FCircle2D();
	
	NeedRounding = false;
	IsRoundingClockwise = false;
	RoundingFullPathLength = 0.f;
	RoundingStartToArcPathLength = 0.f;
	RoundingArcPathLength = 0.f;
	RoundingArcToEndPathLength = 0.f;
	RoundingTangentPointStart = FVector2D::ZeroVector;
	RoundingTangentPointEnd = FVector2D::ZeroVector;
}
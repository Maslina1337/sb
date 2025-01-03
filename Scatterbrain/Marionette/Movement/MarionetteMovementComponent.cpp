#include "MarionetteMovementComponent.h"

// Sets default values for this component's properties
UMarionetteMovementComponent::UMarionetteMovementComponent()
{
	CurrentPassiveMove = EPassiveMove::Fall;
	PastPassiveMove = EPassiveMove::Fall;
	
	FootBox = FVector(30, 10, 10);
	SideWalkAngleBegin = 60;
	SideWalkAngleEnd = 120;

	WalkStepDirectionChangeCoefficient = 3;
	RaysFarRotation = -10;
	IterationsCountOfLocationClarify = 1;
	StepSpeedWalk = 70;

	MaxMovementAchievableInertiaSpeed = 600;
	MovementFallInertiaAcceleration = 200;
}

void UMarionetteMovementComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}
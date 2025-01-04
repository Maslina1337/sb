#include "MarionettePhysicsComponent.h"

using namespace TwoLimbs;

// Sets default values for this component's properties
UMarionettePhysicsComponent::UMarionettePhysicsComponent()
{
	PhysicsIgnore = false;
	
	GravitationalSpeed = FVector::ZeroVector;
	InertiaSpeed = FVector::ZeroVector;
	LandingImpactSpeed = FVector::ZeroVector;
	FallSpeed = FVector::ZeroVector;
	FallDistanceRemaining = 0.0f;
	GravitationalDirection = FVector::DownVector;
	SurfAngle = 0.0f;
	
	SurfingAngle = 45.0f; // degrees
	GravitationalAcceleration = 9.81f; // m/s^2
	TraceError = 0.001f; // unit (centimeters)
	TimeOfConcentrateFalling = 3.0f; // s
	InertiaSlowdown = 0.025f; // m/s^2 (Negative affect)
	GravitationalSlowdown = 0.05f; // m/s^2 (Negative affect)
	Mass = 60.0f; // kg.
	SurfSlowdown = 2.0f; // m/s^2
	
	ToesHit = FHitResult();
	IsToesHit = false;
}

void UMarionettePhysicsComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
	States = new IStates(OwnerClass);
}
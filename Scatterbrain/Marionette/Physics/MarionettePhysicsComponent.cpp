#include "MarionettePhysicsComponent.h"

// Sets default values for this component's properties
UMarionettePhysicsComponent::UMarionettePhysicsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Owner = nullptr;
	States = nullptr;
	
	PhysicsIgnore = false;
	InertiaSlowdownIgnore = false;
	GravitationalSlowdownIgnore = false;
	
	GravitationalVelocity = FVector::ZeroVector;
	InertiaVelocity = FVector::ZeroVector;
	LandingImpactVelocity = FVector::ZeroVector;
	FallVelocity = FVector::ZeroVector;
	FallDistanceRemaining = 0.0f;
	GravitationalDirection = FVector::DownVector;
	SurfAngle = 60.0f;
	
	SurfingAngle = 45.0f; // degrees
	GravitationalAcceleration = 9.81f; // m/s^2
	TraceError = 0.001f; // unit (centimeters)
	TimeOfConcentrateFalling = 3.0f; // s
	InertiaSlowdown = 0.025f; // m/s^2 (Negative affect)
	GravitationalSlowdown = 0.05f; // m/s^2 (Negative affect)
	Mass = 60.0f; // kg.
	SurfSlowdown = 2.0f; // m/s^2
	/* DEV Value */ ToesFallColliderRadius = 10.f;
	StableAccelerationDamping = 1.f;
	bIsSurfaceActor = false;
	SurfaceActor = nullptr;
	
	ToesHit = FHitResult();
	bIsToesHit = false;

	bCheckPelvisHit = false;
}

void UMarionettePhysicsComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
	States = new IStates(OwnerClass);
}
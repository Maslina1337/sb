#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"


<<<<<<<< HEAD:Scatterbrain/Marionette/Physics/.Mechanism/TickPhysics.cpp
void UMarionettePhysicsComponent::TickPhysics() {
========
void UMarionettePhysicsComponent::TickGravity() {
>>>>>>>> origin/main:Scatterbrain/Marionette/Physics/.Mechanism/TickGravity.cpp

	if (PhysicsIgnore) return;

	if (States->GetBodyState() == EBodyPhysState::Stable)
	{
		States->CopyCurrentToPast();
		return;
	}
	
	// Temp variables.
	FVector TraceStart = FVector::ZeroVector;
	FVector TraceEnd = FVector::ZeroVector;
	FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
	TraceParams.AddIgnoredActor(Owner);
	bool bTempIsHit = false;
	FHitResult TempHit = FHitResult();

	// Checking the surface under the toes.

	TraceStart = Owner->Rig->PelvisLocation;
	TraceEnd = TraceStart + Owner->Movement->PM_Fall->GetLandingDirection() *
		(Owner->Rig->LegLengthTiptoes + Owner->Rig->ToeBoneGroundOffset - ToesFallColliderRadius + TraceError);
	const FCollisionShape ToesFallCollider = FCollisionShape::MakeSphere(ToesFallColliderRadius);
	const FQuat ToesFallColliderRotation = FQuat(1,0,0,0); // No rotation.
	
	bIsToesHit = GetWorld()->SweepSingleByChannel(ToesHit, TraceStart, TraceEnd, ToesFallColliderRotation, ECC_Visibility, ToesFallCollider, TraceParams);
		
	// Gravity (Z axis) update.
		
	GravitationalVelocity += (InertiaVelocity.GetSafeNormal().ProjectOnTo(GravitationalDirection) * InertiaVelocity);

	GravitationalShift = GravitationalVelocity * Owner->TickDeltaTime +
		(GravitationalDirection * GravitationalAcceleration -
		GravitationalVelocity.Size() * (GravitationalSlowdownIgnore ? 0 : GravitationalSlowdown)) *
			pow(Owner->TickDeltaTime,2) / 2;

	// Inertia (XY axes) update.
			
	InertiaVelocity = InertiaVelocity.ProjectOnToNormal(GravitationalDirection);
	
	InertiaShift = InertiaVelocity * Owner->TickDeltaTime -
		InertiaVelocity * (InertiaSlowdownIgnore ? 0 : InertiaSlowdown) * pow(Owner->TickDeltaTime,2) / 2;

	// Fall (All axes together) update.

	FallShift = GravitationalShift + InertiaShift;
	FallVelocity = FallShift / Owner->TickDeltaTime;
		
	// Trace with applying current fall shift.
				
	TraceStart = ToesHit.TraceEnd;
	TraceEnd = TraceStart + FallShift;
		
	bIsToesHit = GetWorld()->LineTraceSingleByChannel(ToesHit, TraceStart, TraceEnd, ECC_Pawn, TraceParams);

	// Updating States.

	States->StatesUpdate();

	// Applying physics.

	switch (States->GetBodyState())
	{
	case EBodyPhysState::Fall:
		Owner->SetActorLocation(Owner->GetActorLocation() + FallShift * 100.f);
		break;
	case EBodyPhysState::Surf: //// UNDONE ////
		break;
	case EBodyPhysState::Stable:
		Owner->SetActorLocation(Owner->GetActorLocation() - ToesHit.TraceStart + ToesHit.Location);
		LandingImpactVelocity = FallVelocity;
		LandingLocation = ToesHit.Location;
		Reset();
		break;
	}
}
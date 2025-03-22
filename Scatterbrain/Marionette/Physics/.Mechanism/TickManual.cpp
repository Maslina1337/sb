#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"
#include "Scatterbrain/Marionette/Movement/PassiveMoves/Fall/PM_Fall.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"
#include "Scatterbrain/Marionette/Movement/MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Development/MarionetteDevelopmentComponent.h"

void UMarionettePhysicsComponent::TickManual() {

	if (PhysicsIgnore) return;

	if (States->GetBodyState() == EBodyPhysState::Stable)
	{
		States->CopyCurrentToPast();
		return;
	}
	
	// Setting Trace Params.
	FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
	TraceParams.AddIgnoredActor(Owner);
	
	// Checking the surface under the toes.

	FVector TraceStart = Owner->Rig->PelvisLocation;
	FVector TraceEnd = TraceStart + Owner->Movement->PM_Fall->GetLandingDirection() *
		(Owner->Rig->LegLengthTiptoes + Owner->Rig->ToeBoneGroundOffset - ToesFallColliderRadius + TraceError);
	const FCollisionShape ToesFallCollider = FCollisionShape::MakeSphere(ToesFallColliderRadius);
	const FQuat ToesFallColliderRotation = FQuat(1,0,0,0); // No rotation.
	
	bIsToesHit = GetWorld()->SweepSingleByChannel(ToesHit, TraceStart, TraceEnd, ToesFallColliderRotation, ECC_Visibility, ToesFallCollider, TraceParams);
		
	// Gravity (Z axis) update.
	
	GravitationalVelocity += InertiaVelocity.ProjectOnTo(GravitationalDirection);

	GravitationalShift = GravitationalVelocity * Owner->TickDeltaTime +
		(GravitationalDirection * GravitationalAcceleration -
		GravitationalVelocity.Size() * (GravitationalSlowdownIgnore ? 0.f : GravitationalSlowdown)) *
			pow(Owner->TickDeltaTime,2) / 2;

	GravitationalVelocity += GravitationalDirection * GravitationalAcceleration * Owner->TickDeltaTime;

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
	
	bIsToesHit = GetWorld()->SweepSingleByChannel(ToesHit, TraceStart, TraceEnd, ToesFallColliderRotation, ECC_Visibility, ToesFallCollider, TraceParams);

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
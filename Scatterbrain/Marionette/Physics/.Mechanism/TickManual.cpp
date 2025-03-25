#include "../../Marionette.h"
#include "../MarionettePhysicsComponent.h"
#include "Scatterbrain/Marionette/Movement/PassiveMoves/Fall/PM_Fall.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"
#include "Scatterbrain/Marionette/Movement/MarionetteMovementComponent.h"
// #include "Scatterbrain/Marionette/Development/MarionetteDevelopmentComponent.h"

void UMarionettePhysicsComponent::TickManual() {

	if (PhysicsIgnore) return;

	if (States->GetBodyState() == EPhysicState::Grounded)
	{
		States->CopyCurrentToPast();
		return;
	}
			// FString LogTempStr = "";
			// UE_LOG(LogTemp, Error, TEXT("Body State: %hhd"), States->GetBodyState())
	
	// Setting Trace Params.
	FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
	TraceParams.AddIgnoredActor(Owner);
	
	// Checking the surface under the toes.

	FVector TraceStart = Owner->Rig->PelvisLocation;
	FVector TraceEnd = TraceStart + Owner->Movement->PM_Fall->GetLandingDirection() *
		(Owner->Rig->LegLengthTiptoes + Owner->Rig->ToeBoneGroundOffset - ToesFallColliderRadius + TraceError);

		// LogTempStr = IsValid(Owner->Movement->PM_Fall) ? "Yes" : "No";
		// UE_LOG(LogTemp, Error, TEXT("Is Move valid: %s"), *LogTempStr)
		// UE_LOG(LogTemp, Error, TEXT("Landing Direction: %s"), *Owner->Movement->PM_Fall->GetLandingDirection().ToString())
		// UE_LOG(LogTemp, Error, TEXT("Move Debug Name: %s"), *Owner->Movement->PM_Fall->DebugName)

	// Setting the collider
	const FCollisionShape ToesFallCollider = FCollisionShape::MakeSphere(ToesFallColliderRadius);
	const FQuat ToesFallColliderRotation = FQuat(1,0,0,0); // No rotation.

			// UE_LOG(LogTemp, Error, TEXT("Trace Start: %s"), *TraceStart.ToString())
			// UE_LOG(LogTemp, Error, TEXT("Trace End: %s"), *TraceEnd.ToString())
	
	bIsToesHit = GetWorld()->SweepSingleByChannel(ToesHit, TraceStart, TraceEnd, ToesFallColliderRotation, ECC_Visibility, ToesFallCollider, TraceParams);
			// Owner->Development->DrawTrace(bIsToesHit, ToesHit, TraceStart, TraceEnd);
			// LogTempStr = bIsToesHit ? "Yes" : "No";
			// UE_LOG(LogTemp, Error, TEXT("Does toes hit: %s"), *LogTempStr)
		
	// Gravity (Z axis) update.
	
	GravitationalVelocity += InertiaVelocity.ProjectOnTo(GravitationalDirection);

			// UE_LOG(LogTemp, Error, TEXT("Gravitational Vel: %s"), *GravitationalVelocity.ToString())

	GravitationalShift = GravitationalVelocity * Owner->TickDeltaTime +
		(GravitationalDirection * GravitationalAcceleration -
		GravitationalVelocity.Size() * (GravitationalSlowdownIgnore ? 0.f : GravitationalSlowdown)) *
			pow(Owner->TickDeltaTime,2) / 2;

	GravitationalVelocity += GravitationalDirection * GravitationalAcceleration * Owner->TickDeltaTime;

			// UE_LOG(LogTemp, Error, TEXT("Gravitational Vel 2: %s"), *GravitationalVelocity.ToString())
			// UE_LOG(LogTemp, Error, TEXT("Gravitational Shift: %s"), *GravitationalShift.ToString())

	// Inertia (XY axes) update.
			
	InertiaVelocity = InertiaVelocity.ProjectOnToNormal(GravitationalDirection);

			// UE_LOG(LogTemp, Error, TEXT("Inertia Vel: %s"), *InertiaVelocity.ToString())
	
	InertiaShift = InertiaVelocity * Owner->TickDeltaTime -
		InertiaVelocity * (InertiaSlowdownIgnore ? 0 : InertiaSlowdown) * pow(Owner->TickDeltaTime,2) / 2;

			// UE_LOG(LogTemp, Error, TEXT("Inertia Shift: %s"), *InertiaShift.ToString())

	// Fall (All axes together) update.

	FallShift = GravitationalShift + InertiaShift;
	FallVelocity = GravitationalVelocity + InertiaVelocity;

			// UE_LOG(LogTemp, Error, TEXT("Fall Vel: %s"), *FallVelocity.ToString())
			// UE_LOG(LogTemp, Error, TEXT("Fall Shift: %s"), *FallShift.ToString())
		
	// Trace with applying current fall shift.
	TraceStart = ToesHit.TraceEnd;
	TraceEnd = TraceStart + FallShift;

			// UE_LOG(LogTemp, Error, TEXT("Trace Start 2: %s"), *TraceStart.ToString())
			// UE_LOG(LogTemp, Error, TEXT("Trace End 2: %s"), *TraceEnd.ToString())
	
	bIsToesHit = GetWorld()->SweepSingleByChannel(ToesHit, TraceStart, TraceEnd, ToesFallColliderRotation, ECC_Visibility, ToesFallCollider, TraceParams);
			// Owner->Development->DrawTrace(bIsToesHit, ToesHit, TraceStart, TraceEnd);
			// LogTempStr = bIsToesHit ? "Yes" : "No";
			// UE_LOG(LogTemp, Error, TEXT("Does toes hit 2: %s"), *LogTempStr)

	// Updating States.

	States->StatesUpdate();

			// UE_LOG(LogTemp, Error, TEXT("State 2: %hhd"), States->GetBodyState())

	// Applying physics.

	switch (States->GetBodyState())
	{
	case EPhysicState::Falling:
		Owner->SetActorLocation(Owner->GetActorLocation() + FallShift * 100.f);
		break;
		
	case EPhysicState::Sliding: //// UNDONE ////
		break;
		
	case EPhysicState::Grounded:
		Owner->SetActorLocation(Owner->GetActorLocation() - ToesHit.TraceStart + ToesHit.Location);
		LandingImpactVelocity = FallVelocity;
		LandingLocation = ToesHit.Location;
		Reset();
		break;
		
	default:
		break;
	}
}
#include "../../Marionette.h"
#include "../../Types/TwoLimbs.h"
#include "../MarionettePhysicsComponent.h"

using namespace TwoLimbs;

void UMarionettePhysicsComponent::CalculateGravity() {

	if (PhysicsIgnore) return;
	
	// Temp variables.
	FVector TraceStart = FVector::ZeroVector;
	FVector TraceEnd = FVector::ZeroVector;
	FCollisionQueryParams TraceParams = FCollisionQueryParams::DefaultQueryParam;
	TraceParams.AddIgnoredActor(Owner);
	bool bTempIsHit = false;
	FHitResult TempHit = FHitResult();

	

	// //-------------- CHECKING STABLE (NON-SURFING) PLATFORM UNDER FOOT --------------
	//
	// // Check foots stability actuality. Tracing a ToeFallSphereCollider in direction of gravity action.
	// // *Supported only for actors that marionette standing on. Not for brushes.
	// TraceStart = Owner->Rig->PelvisLocation;
	// TraceEnd = TraceStart + GravitationalDirection *
	// 	(Owner->Rig->LegLengthTiptoes + Owner->Rig->ToeBoneGroundOffset - ToesFallColliderRadius + TraceError);
	// const FCollisionShape ToesFallCollider = FCollisionShape::MakeSphere(ToesFallColliderRadius);
	// const FQuat ToesFallColliderRotation = FQuat(1,0,0,0); // No rotation.
	//
	// IsToesHit = GetWorld()->SweepSingleByChannel(ToesHit, TraceStart, TraceEnd, ToesFallColliderRotation, ECC_Visibility, ToesFallCollider, TraceParams);
	//
	// // Is Marionette still stable?
	// if (IsToesHit)
	// {
	// 	States->CopyCurrentToPast();
	// 	return;
	// }
	//
	//
	// //-------------- CHANGE YOUR LOCATION IF PLATFORM CHANGE LOCATION --------------
	//
	// //Position of the point on which the marionette stood.
	// HitObjectRelativeLocation = ToesHit.HitObjectHandle.GetLocation();
	// HitObjectRelativeRotation = ToesHit.HitObjectHandle.GetRotation();


	
	if (States->GetIsBodyStable())
	{
		States->CopyCurrentToPast();
		return;
	}

	// Traces from pelvis to fall direction on length of fall shift.

	TraceStart = Owner->Rig->PelvisLocation;
	TraceEnd = TraceStart + GravitationalDirection *
		(Owner->Rig->LegLengthTiptoes + Owner->Rig->ToeBoneGroundOffset - ToesFallColliderRadius + TraceError);
	const FCollisionShape ToesFallCollider = FCollisionShape::MakeSphere(ToesFallColliderRadius);
	const FQuat ToesFallColliderRotation = FQuat(1,0,0,0); // No rotation.
	
	IsToesHit = GetWorld()->SweepSingleByChannel(ToesHit, TraceStart, TraceEnd, ToesFallColliderRotation, ECC_Visibility, ToesFallCollider, TraceParams);

	//States->StatesUpdate(IsFootHit, FootHit);
	
	if (States->GetBodyState() == EBodyPhysState::Surf || States->GetBodyState() == EBodyPhysState::Fall) {
		
		// Gravity (Z axis) update.
		
		GravitationalVelocity += (InertiaVelocity.GetSafeNormal().ProjectOnTo(GravitationalDirection) * InertiaVelocity);

		GravitationalShift = GravitationalVelocity * Owner->TickDeltaTime +
			(GravitationalDirection * GravitationalAcceleration -
			GravitationalVelocity.Size() * GravitationalSlowdown) *
				pow(Owner->TickDeltaTime,2) / 2;

		// Inertia (XY axes) update.
			
		InertiaVelocity = InertiaVelocity.ProjectOnToNormal(GravitationalDirection);
		
		InertiaShift = InertiaVelocity * Owner->TickDeltaTime -
			InertiaVelocity * InertiaSlowdown * pow(Owner->TickDeltaTime,2) / 2;

		// Fall (All axes together) update.

		FallShift = GravitationalShift + InertiaShift;
		FallVelocity = FallShift / Owner->TickDeltaTime;
		
		// Is Left leg able to touch the ground at this moment after physics applying?

			// Trace with applying current fall shift.
				
				TraceStart = ToesHit.TraceEnd;
				TraceEnd = TraceStart;
		
				bTempIsHit = GetWorld()->LineTraceSingleByChannel(TempHit, TraceStart, TraceEnd, ECC_Pawn, TraceParams);

			// Shift over TimeOfConcentrateFalling.
		
				const FVector TraceConcentrate = (GravitationalVelocity + FallVelocity) * TimeOfConcentrateFalling +
				(GravitationalDirection * GravitationalAcceleration -
				(GravitationalVelocity + FallVelocity).Size() * GravitationalSlowdown) *
				pow(TimeOfConcentrateFalling,2) / 2;

		// Applying hit results to legs which touches the ground at this moment.
		

		//States->StatesUpdate();

		// Applying physics.

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Blue, FString("Check 2"));
		}

		switch (States->GetBodyState())
		{
		case EBodyPhysState::Fall:
			Owner->SetActorLocation(Owner->GetActorLocation() + FallShift * 100);
			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Blue, FString("Check 3 Fall"));
			}
			
			break;
		case EBodyPhysState::Surf: //// UNDONE ////
			//FallShift.ProjectOnToNormal()

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Blue, FString("Check 3 Surf"));
			}
			
			break;
		case EBodyPhysState::LandingLeft: //// UNDONE ////
			Owner->SetActorLocation(Owner->GetActorLocation() - FootHit[Left].TraceStart + FootHit[Left].Location);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Blue, FString("Check 3 Landing Left"));
			}
			
			break;
		case EBodyPhysState::LandingRight: //// UNDONE ////
			Owner->SetActorLocation(Owner->GetActorLocation() - FootHit[Right].TraceStart + FootHit[Right].Location);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Blue, FString("Check 3 Landing Right"));
			}
			
			break;
		}

		// Variables set on landing.
		
		if (States->GetBodyState() == EBodyPhysState::LandingLeft || States->GetBodyState() == EBodyPhysState::LandingRight)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Blue, FString("Check 4 Gravity End"));
			}
			
			LandingImpactVelocity = FallVelocity;

			GravitationalShift = FVector::ZeroVector;
			GravitationalVelocity = FVector::ZeroVector;

			InertiaShift = FVector::ZeroVector;
			InertiaVelocity = FVector::ZeroVector;
		}
	}
}
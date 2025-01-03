#include "../../Marionette.h"
#include "../../Types/TwoLimbs.h"
#include "../MarionettePhysicsComponent.h"

using namespace TwoLimbs;

void UMarionettePhysicsComponent::CalculateGravity() {

	if (PhysicsIgnore) return;
	
	// Is body stable?
	
	if (States->GetIsStableMoment()) {
		States->CopyCurrentToPast();
		return;
	}

	// Traces from leg root to foot.
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);

	FVector TraceStartLocation[2] = {
		Owner->Rig->LegRootLocation[Left],
		Owner->Rig->LegRootLocation[Right]
	};
	
	IsFootHit[Left] = GetWorld()->LineTraceSingleByChannel(FootHit[Left], Owner->Rig->LegRootLocation[Left], Owner->Rig->ToeLocation[Left], ECC_Pawn, QueryParams);
	IsFootHit[Right] = GetWorld()->LineTraceSingleByChannel(FootHit[Right], Owner->Rig->LegRootLocation[Right], Owner->Rig->ToeLocation[Right], ECC_Pawn, QueryParams);

	States->StatesUpdate(IsFootHit, FootHit);
	
	if (States->GetBodyState() == EBodyPhysState::Surf || States->GetBodyState() == EBodyPhysState::Fall) {
		
		// Gravity (Z axis) update.
		
			GravitationalSpeed += (InertiaSpeed.GetSafeNormal().ProjectOnTo(GravitationalDirection) * InertiaSpeed);

			GravitationalShift = GravitationalSpeed * Owner->TickDeltaTime +
				(GravitationalDirection * GravitationalAcceleration -
				GravitationalSpeed.Size() * GravitationalSlowdown) *
				pow(Owner->TickDeltaTime,2) / 2;

		// Inertia (XY axes) update.
			
			InertiaSpeed = InertiaSpeed.ProjectOnToNormal(GravitationalDirection);
		
			InertiaShift = InertiaSpeed * Owner->TickDeltaTime -
				InertiaSpeed * InertiaSlowdown * pow(Owner->TickDeltaTime,2) / 2;

		// Fall (All axes together) update.

			FallShift = GravitationalShift + InertiaShift;
			FallSpeed = FallShift / Owner->TickDeltaTime;

		// Is Left leg able to touch the ground at this moment after physics applying (but the ray is also traced to set concentrate falling)
		
			// Shift over TimeOfConcentrateFalling.
		
			const FVector TraceConcentrate = (GravitationalSpeed + FallSpeed) * TimeOfConcentrateFalling +
				(GravitationalDirection * GravitationalAcceleration -
				(GravitationalSpeed + FallSpeed).Size() * GravitationalSlowdown) *
				pow(TimeOfConcentrateFalling,2) / 2;

			FHitResult TempHit;

			// Left leg.
				
				FVector TempTraceStart = FootHit[Left].TraceEnd;
				FVector TempTraceEnd = TempTraceStart + TraceConcentrate;
		
				const bool TempIsLeftLegHit = GetWorld()->LineTraceSingleByChannel(TempHit, TempTraceStart, TempTraceEnd, ECC_Pawn, QueryParams);
				const FHitResult TempLeftLegHit = TempHit;
				const bool WillLeftLegTouchGroundAtThisMoment = (TempHit.Distance <= FallShift.Size() && TempIsLeftLegHit);
				
			// Right leg.

				TempTraceStart = FootHit[Right].TraceEnd;
				TempTraceEnd = TempTraceStart + FallShift.GetSafeNormal() * TraceConcentrate;
		
				const bool TempIsRightLegHit = GetWorld()->LineTraceSingleByChannel(TempHit, TempTraceStart, TempTraceEnd, ECC_Pawn, QueryParams);
				const FHitResult TempRightLegHit = TempHit;
				const bool WillRightLegTouchGroundAtThisMoment = (TempHit.Distance <= FallShift.Size() && TempIsRightLegHit);

		// Applying hit results to legs which touches the ground at this moment.
		
		if (WillLeftLegTouchGroundAtThisMoment) {
			IsFootHit[Left] = true;
			FootHit[Left] = TempLeftLegHit;
		}

		if (WillRightLegTouchGroundAtThisMoment) {
			IsFootHit[Right] = true;
			FootHit[Right] = TempRightLegHit;
		}

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
			
			LandingImpactSpeed = FallSpeed;

			GravitationalShift = FVector::ZeroVector;
			GravitationalSpeed = FVector::ZeroVector;

			InertiaShift = FVector::ZeroVector;
			InertiaSpeed = FVector::ZeroVector;
		}
	}
}
#include "../MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteMovementComponent::AttachFootToHit(FVector& CurrentFootLocation, const FHitResult Hit)
{
	FVector NewLocation = Hit.ImpactPoint;
	NewLocation += Hit.ImpactNormal.GetSafeNormal() * Owner->Rig->FootBoneGroundOffset;

	CurrentFootLocation = NewLocation;
}
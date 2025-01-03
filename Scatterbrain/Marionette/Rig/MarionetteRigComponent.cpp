#include "MarionetteRigComponent.h"

UMarionetteRigComponent::UMarionetteRigComponent()
{
	RootLocation = FVector();
	RootRotation = FRotator();
	PelvisLocation = FVector();
	PelvisRotation = FRotator();
	RootKneeLength = 0.0f;
	KneeFootLength = 0.0f;
	FootToeLength = 0.0f;
	LegLength = 0.0f;
	RootFootMinLength = 0.0f;
	FootBoneGroundOffset = 0.0f;
	ToeBoneGroundOffset = 0.0f;

	TWO_LIMBS_INIT(LegRootLocation, FVector);
	TWO_LIMBS_INIT(LegRootRotation, FRotator);
	TWO_LIMBS_INIT(KneeLocation, FVector);
	TWO_LIMBS_INIT(KneeRotation, FRotator);
	TWO_LIMBS_INIT(FootLocation, FVector);
	TWO_LIMBS_INIT(FootRotation, FRotator);
	TWO_LIMBS_INIT(ToeLocation, FVector);
	TWO_LIMBS_INIT(ToeRotation, FRotator);
	TWO_LIMBS_INIT(FootGoalLocation, FVector);
	TWO_LIMBS_INIT(FootGoalRotation, FRotator);
	TWO_LIMBS_INIT(FootAlphaIK, float);
}

void UMarionetteRigComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}

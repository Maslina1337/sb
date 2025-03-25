#include "MarionetteRigComponent.h"

UMarionetteRigComponent::UMarionetteRigComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Owner = nullptr;
	
	RootLocation = FVector();
	RootRotation = FRotator();
	HeadLocation = FVector();
	HeadRotation = FRotator();
	HeadGoalLocation = FVector();
	HeadGoalRotation = FRotator();
	PelvisLocation = FVector();
	PelvisRotation = FRotator();
	RootKneeLength = 0.0f;
	KneeFootLength = 0.0f;
	FootToeLength = 0.0f;
	LegLength = 0.0f;
	RootFootMinLength = 0.0f;
	FootBoneGroundOffset = 0.0f;
	ToeBoneGroundOffset = 0.0f;
	LegLengthTiptoes = 0.0f;
	PelvisHitDistance = 5.0f;
	TiptoesAngle = 45.f;

	LEFT_RIGHT_INIT(LegRootLocation, FVector::ZeroVector);
	LEFT_RIGHT_INIT(LegRootRotation, FRotator::ZeroRotator);
	LEFT_RIGHT_INIT(KneeLocation, FVector::ZeroVector);
	LEFT_RIGHT_INIT(KneeRotation, FRotator::ZeroRotator);
	LEFT_RIGHT_INIT(FootLocation, FVector::ZeroVector);
	LEFT_RIGHT_INIT(FootRotation, FRotator::ZeroRotator);
	LEFT_RIGHT_INIT(ToeLocation, FVector::ZeroVector);
	LEFT_RIGHT_INIT(ToeRotation, FRotator::ZeroRotator);
	LEFT_RIGHT_INIT(FootGoalLocation, FVector::ZeroVector);
	LEFT_RIGHT_INIT(FootGoalRotation, FRotator::ZeroRotator);
	LEFT_RIGHT_INIT(ToeGoalLocation, FVector::ZeroVector);
	LEFT_RIGHT_INIT(ToeGoalRotation, FRotator::ZeroRotator);
	LEFT_RIGHT_INIT(FootAlphaIK, 0.f);
}

void UMarionetteRigComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}

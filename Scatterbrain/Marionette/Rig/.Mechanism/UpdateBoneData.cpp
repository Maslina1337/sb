#include "../MarionetteRigComponent.h"
#include "../../Marionette.h"
#include "../../Types/LeftRight.h"

using namespace LeftRight;

void UMarionetteRigComponent::UpdateBoneData()
{
	const USkeletalMeshComponent* SkeletalMeshComponent = Owner->SkeletalMeshComponent;
	
	RootLocation = SkeletalMeshComponent->GetSocketLocation("rootSocket");
	HeadLocation = SkeletalMeshComponent->GetSocketLocation("headSocket");
	PelvisLocation = SkeletalMeshComponent->GetSocketLocation("pelvisSocket");
	LegRootLocation[Left] = SkeletalMeshComponent->GetSocketLocation("thigh_lSocket");
	LegRootLocation[Right] = SkeletalMeshComponent->GetSocketLocation("thigh_rSocket");
	KneeLocation[Left] = SkeletalMeshComponent->GetSocketLocation("calf_lSocket");
	KneeLocation[Right] = SkeletalMeshComponent->GetSocketLocation("calf_rSocket");
	FootLocation[Left] = SkeletalMeshComponent->GetSocketLocation("foot_lSocket");
	FootLocation[Right] = SkeletalMeshComponent->GetSocketLocation("foot_rSocket");
	ToeLocation[Left] = SkeletalMeshComponent->GetSocketLocation("ball_lSocket");
	ToeLocation[Right] = SkeletalMeshComponent->GetSocketLocation("ball_rSocket");
	
	// Rotations
	
	RootRotation = SkeletalMeshComponent->GetSocketRotation("rootSocket");
	HeadRotation = SkeletalMeshComponent->GetSocketRotation("headSocket");
	PelvisRotation = SkeletalMeshComponent->GetSocketRotation("pelvisSocket");
	LegRootRotation[Left] = SkeletalMeshComponent->GetSocketRotation("thigh_lSocket");
	LegRootRotation[Right] = SkeletalMeshComponent->GetSocketRotation("thigh_rSocket");
	KneeRotation[Left] = SkeletalMeshComponent->GetSocketRotation("calf_lSocket");
	KneeRotation[Right] = SkeletalMeshComponent->GetSocketRotation("calf_rSocket");
	FootRotation[Left] = SkeletalMeshComponent->GetSocketRotation("foot_lSocket");
	FootRotation[Right] = SkeletalMeshComponent->GetSocketRotation("foot_rSocket");
	ToeRotation[Left] = SkeletalMeshComponent->GetSocketRotation("ball_lSocket");
	ToeRotation[Right] = SkeletalMeshComponent->GetSocketRotation("ball_rSocket");

	

	// Debug
	
	// DrawDebugSphere(Owner->GetWorld(), PelvisLocation, 30, 16, FColor::Green, true, 0, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), FootLocation[Left], 5, 16, FColor::Green, true, 0, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), FootLocation[Right], 5, 16, FColor::Green, true, 0, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Left], 5, 16, FColor::Green, true, 0, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Right], 5, 16, FColor::Green, true, 0, 0, 1);
}

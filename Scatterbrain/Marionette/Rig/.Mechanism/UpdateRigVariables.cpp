#include "../MarionetteRigComponent.h"
#include "../../Marionette.h"
#include "../../Types/TwoLimbs.h"

using namespace TwoLimbs;

void UMarionetteRigComponent::UpdateRigVariables()
{
	const USkeletalMeshComponent* SkeletalMeshComponent = Owner->SkeletalMeshComponent;
	
	// Locations.

	RootLocation = SkeletalMeshComponent->GetSocketLocation("root_s");
	RootLocation = SkeletalMeshComponent->GetSocketLocation("head_s");
	PelvisLocation = SkeletalMeshComponent->GetSocketLocation("pelvis_s");
	LegRootLocation[Left] = SkeletalMeshComponent->GetSocketLocation("thigh_l_s");
	LegRootLocation[Right] = SkeletalMeshComponent->GetSocketLocation("thigh_r_s");
	KneeLocation[Left] = SkeletalMeshComponent->GetSocketLocation("calf_l_s");
	KneeLocation[Right] = SkeletalMeshComponent->GetSocketLocation("calf_r_s");
	FootLocation[Left] = SkeletalMeshComponent->GetSocketLocation("foot_l_s");
	FootLocation[Right] = SkeletalMeshComponent->GetSocketLocation("foot_r_s");
	ToeLocation[Left] = SkeletalMeshComponent->GetSocketLocation("ball_l_s");
	ToeLocation[Right] = SkeletalMeshComponent->GetSocketLocation("ball_r_s");

	// Rotations

	RootRotation = SkeletalMeshComponent->GetSocketRotation("root_s");
	RootRotation = SkeletalMeshComponent->GetSocketRotation("head_s");
	PelvisRotation = SkeletalMeshComponent->GetSocketRotation("pelvis_s");
	LegRootRotation[Left] = SkeletalMeshComponent->GetSocketRotation("thigh_l_s");
	LegRootRotation[Right] = SkeletalMeshComponent->GetSocketRotation("thigh_r_s");
	KneeRotation[Left] = SkeletalMeshComponent->GetSocketRotation("calf_l_s");
	KneeRotation[Right] = SkeletalMeshComponent->GetSocketRotation("calf_r_s");
	FootRotation[Left] = SkeletalMeshComponent->GetSocketRotation("foot_l_s");
	FootRotation[Right] = SkeletalMeshComponent->GetSocketRotation("foot_r_s");
	ToeRotation[Left] = SkeletalMeshComponent->GetSocketRotation("ball_l_s");
	ToeRotation[Right] = SkeletalMeshComponent->GetSocketRotation("ball_r_s");

	// Debug
	
	DrawDebugSphere(Owner->GetWorld(), PelvisLocation, 30, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), FootLocation[Left], 5, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), FootLocation[Right], 5, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Left], 5, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Right], 5, 16, FColor::Green, true, 5, 0, 1);
}

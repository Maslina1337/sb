#include "../MarionetteRigComponent.h"
#include "../../Marionette.h"
#include "../../Types/TwoLimbs.h"

using namespace TwoLimbs;

void UMarionetteRigComponent::UpdateRigVariables()
{
	const USkeletalMeshComponent* SkeletalMeshComponent = Owner->SkeletalMeshComponent;
	
	// Locations.

	RootLocation = SkeletalMeshComponent->GetSocketLocation("root_s");
	PelvisLocation = SkeletalMeshComponent->GetSocketLocation("pelvis_s");
	LegRootLocation[Left] = SkeletalMeshComponent->GetSocketLocation("l_leg_root_s");
	LegRootLocation[Right] = SkeletalMeshComponent->GetSocketLocation("r_leg_root_s");
	KneeLocation[Left] = SkeletalMeshComponent->GetSocketLocation("l_knee_s");
	KneeLocation[Right] = SkeletalMeshComponent->GetSocketLocation("r_knee_s");
	FootLocation[Left] = SkeletalMeshComponent->GetSocketLocation("l_foot_s");
	FootLocation[Right] = SkeletalMeshComponent->GetSocketLocation("r_foot_s");
	ToeLocation[Left] = SkeletalMeshComponent->GetSocketLocation("l_toe_s");
	ToeLocation[Right] = SkeletalMeshComponent->GetSocketLocation("r_toe_s");

	// Rotations

	RootRotation = SkeletalMeshComponent->GetSocketRotation("root");
	PelvisRotation = SkeletalMeshComponent->GetSocketRotation("pelvis");
	LegRootRotation[Left] = SkeletalMeshComponent->GetSocketRotation("l_leg_root_s");
	LegRootRotation[Right] = SkeletalMeshComponent->GetSocketRotation("r_leg_root_s");
	KneeRotation[Left] = SkeletalMeshComponent->GetSocketRotation("l_knee_s");
	KneeRotation[Right] = SkeletalMeshComponent->GetSocketRotation("r_knee_s");
	FootRotation[Left] = SkeletalMeshComponent->GetSocketRotation("l_foot_s");
	FootRotation[Right] = SkeletalMeshComponent->GetSocketRotation("r_foot_s");
	ToeRotation[Left] = SkeletalMeshComponent->GetSocketRotation("l_toe_s");
	ToeRotation[Right] = SkeletalMeshComponent->GetSocketRotation("r_toe_s");

	// Debug
	
	DrawDebugSphere(Owner->GetWorld(), PelvisLocation, 30, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), FootLocation[Left], 5, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), FootLocation[Right], 5, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Left], 5, 16, FColor::Green, true, 5, 0, 1);
	DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Right], 5, 16, FColor::Green, true, 5, 0, 1);
}

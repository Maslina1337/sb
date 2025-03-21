#include "../MarionetteRigComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "../../Types/LeftRight.h"

using namespace LeftRight;

void UMarionetteRigComponent::LoadLengthData()
{
	RootKneeLength = Owner->DataAsset->RootKneeLength;
	KneeFootLength = Owner->DataAsset->KneeFootLength;
	FootToeLength = Owner->DataAsset->FootToeLength;

	LegLength = Owner->DataAsset->LegLength;
	LegLengthTiptoes = Owner->DataAsset->LegLengthTiptoes;

	FootBoneGroundOffset = Owner->DataAsset->FootBoneGroundOffset;
	ToeBoneGroundOffset = Owner->DataAsset->ToeBoneGroundOffset;
	

	

	// if (GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, "Root Location On INIT: " + RootLocation.ToString());
	// } else UE_LOG(LogTemp, Error, TEXT("FAILED SHITT"))
	//
	// DrawDebugSphere(Owner->GetWorld(), PelvisLocation, 30, 16, FColor::Red, true, -1, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), FootLocation[Left], 5, 16, FColor::Red, true, -1, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), FootLocation[Right], 5, 16, FColor::Red, true, -1, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Left], 5, 16, FColor::Red, true, -1, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), LegRootLocation[Right], 5, 16, FColor::Red, true, -1, 0, 1);
	// DrawDebugSphere(Owner->GetWorld(), RootLocation, 5, 16, FColor::Red, true, -1, 0, 1);
}
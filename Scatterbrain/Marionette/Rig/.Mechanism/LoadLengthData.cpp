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
}
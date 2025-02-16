#include "../MarionetteRigComponent.h"
#include "../../Types/TwoLimbs.h"

using namespace TwoLimbs;

void UMarionetteRigComponent::InitRigVariables()
{
	// Getting actual sockets locations and rotations.
	UpdateRigVariables();

	RootKneeLength = (LegRootLocation[Left] - KneeLocation[Left]).Length();
	KneeFootLength = (KneeLocation[Left] - FootLocation[Left]).Length();
	FootToeLength = (FootLocation[Left] - ToeLocation[Left]).Length();

	LegLength = RootKneeLength + KneeFootLength;
	LegLengthTiptoes = RootKneeLength + KneeFootLength + FootToeLength;

	FootBoneGroundOffset = RootLocation.Z - FootLocation[Left].Z;
	ToeBoneGroundOffset = RootLocation.Z - ToeLocation[Left].Z;
}
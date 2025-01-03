#include "../MarionetteRigComponent.h"
#include "../../Types/TwoLimbs.h"

using namespace TwoLimbs;

void UMarionetteRigComponent::AttachGoalsToBones()
{
	FootGoalLocation[Left] = FootLocation[Left];
	FootGoalLocation[Right] = FootLocation[Right];
	FootGoalRotation[Left] = FootRotation[Left];
	FootGoalRotation[Right] = FootRotation[Right];
}
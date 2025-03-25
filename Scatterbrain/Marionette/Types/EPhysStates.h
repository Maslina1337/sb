#pragma once

#include "CoreMinimal.h"
#include "EPhysStates.generated.h"

UENUM(BlueprintType)
enum class EPhysicState : uint8
{
	Grounded = 0,
	Falling = 1,
	Sliding = 2,
	Swimming = 3,
};
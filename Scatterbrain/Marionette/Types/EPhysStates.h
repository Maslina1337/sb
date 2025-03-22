#pragma once

#include "CoreMinimal.h"
#include "EPhysStates.generated.h"

UENUM(BlueprintType)
enum class EBodyPhysState : uint8 { Stable = 0, Fall = 1, Surf = 2 };
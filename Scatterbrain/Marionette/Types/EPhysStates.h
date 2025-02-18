#pragma once

#include "CoreMinimal.h"
#include "EPhysStates.generated.h"

UENUM(BlueprintType)
enum class EBodyPhysState : uint8 { Stable, Fall, Surf };
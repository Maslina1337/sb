#pragma once

#include "CoreMinimal.h"
#include "EPhysStates.generated.h"

UENUM(BlueprintType)
enum class EFootPhysState : uint8 { Fulcrum, Surf, Air };

UENUM(BlueprintType)
enum class EBodyPhysState : uint8 { LandingLeft, LandingRight, Fall, Surf };
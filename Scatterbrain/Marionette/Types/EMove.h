#pragma once

#include "CoreMinimal.h"
#include "EMove.generated.h"

// Moves describes how the all inputs should be processed.

// Passive moves
UENUM(BlueprintType)
enum class EPassiveMove : uint8 {
	None,
	Fall,
	Slide,
	Walk,
	Run,
};

// Active moves can overlap or work together with passive moves.
UENUM(BlueprintType)
enum class EActiveMove : uint8 {
	None,
	Step,
	Land,
	Punch,
};
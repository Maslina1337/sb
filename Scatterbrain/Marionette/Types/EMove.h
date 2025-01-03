#pragma once

#include "CoreMinimal.h"
#include "EMove.generated.h"

// Moves describes how the all inputs should be processed.

// Passive moves
UENUM(BlueprintType)
enum class EPassiveMove : uint8 {
	Stand, // Stand in place.
	Fall,
	Surf,
	Walk,
	Run,
};

// Active moves can overlap or work together with passive moves.
UENUM(BlueprintType)
enum class EActiveMove : uint8 {
	None,
	Step,
	Landing,
	Punch, // TEST //
};
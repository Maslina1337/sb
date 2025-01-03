#pragma once

#include "CoreMinimal.h"
#include "FSurfCheckReturn.generated.h"

USTRUCT(BlueprintType)
struct FSurfCheckReturn {

	GENERATED_BODY()
	
	float AngleOfIncidence;
	bool IsSurf;
};
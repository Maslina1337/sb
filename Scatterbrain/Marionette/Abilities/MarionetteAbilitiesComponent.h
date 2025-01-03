#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionetteAbilitiesComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionetteAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionetteAbilitiesComponent();
	
	void SetOwner(AMarionette*);

private:
	UPROPERTY()
	AMarionette* Owner;
};

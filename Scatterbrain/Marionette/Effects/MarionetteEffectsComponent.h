#pragma once

#include "Effect.h"
#include "Library/EffectsList.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionetteEffectsComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionetteEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionetteEffectsComponent();
	
	void SetOwner(AMarionette*);

	void TickActivatedEffects();
	void NotifyAboutActivation(FEffectBase*);

	EFFECTS_DECLARATION

private:
	UPROPERTY()
	AMarionette* Owner;

	TArray<FEffectBase*> EffectsToTick; // For Tick trigger only.
};

#include "MarionetteEffectsComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

// Sets default values for this component's properties
UMarionetteEffectsComponent::UMarionetteEffectsComponent()
{
	
}

void UMarionetteEffectsComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
	EFFECTS_INIT
}

void UMarionetteEffectsComponent::TickActivatedEffects()
{
	for (FEffectBase* Effect : EffectsToTick)
	{
		if (Effect)
		{
			Effect->Tick();	
		}
	}
}

void UMarionetteEffectsComponent::NotifyAboutActivation(FEffectBase* Pointer)
{
	EffectsToTick.Add(Pointer);
};
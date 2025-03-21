#include "MarionetteNarrativeComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

UMarionetteNarrativeComponent::UMarionetteNarrativeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMarionetteNarrativeComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}
#include "MarionetteNarrativeComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

UMarionetteNarrativeComponent::UMarionetteNarrativeComponent()
{
	
}

void UMarionetteNarrativeComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}
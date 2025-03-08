#include "MarionetteAbilitiesComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

// Sets default values for this component's properties
UMarionetteAbilitiesComponent::UMarionetteAbilitiesComponent()
{
	Owner = nullptr;
}

void UMarionetteAbilitiesComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}
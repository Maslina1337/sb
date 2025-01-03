#include "MarionetteSightComponent.h"


// Sets default values for this component's properties
UMarionetteSightComponent::UMarionetteSightComponent()
{
	SpringArmStep = 10.0f;
	SpringArmMinLength = 600.0f;
	SpringArmMaxLength = 100.0f;

	SightRotation = FRotator();
	SightSensitivity = 0.8f;
}

void UMarionetteSightComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}
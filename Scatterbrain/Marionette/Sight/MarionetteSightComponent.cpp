#include "MarionetteSightComponent.h"


// Sets default values for this component's properties
UMarionetteSightComponent::UMarionetteSightComponent()
{
	Owner = nullptr;
	
	SpringArmStep = 10.0f;
	SpringArmMinLength = 100.0f;
	SpringArmMaxLength = 600.0f;

	SightRotation = FRotator();
	SightSensitivity = 0.8f;

	bIsFirstPerson = true;
	bIsAbleToTogglePerson = true;

	SpringArmStartLength = 300.f;
	bIsSpringArmLengthChanging = false;
}

void UMarionetteSightComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}
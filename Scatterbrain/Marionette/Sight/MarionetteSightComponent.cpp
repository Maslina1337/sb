#include "MarionetteSightComponent.h"


// Sets default values for this component's properties
UMarionetteSightComponent::UMarionetteSightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Owner = nullptr;
	
	SpringArmStep = 10.0f;
	SpringArmMinLength = 100.0f;
	SpringArmMaxLength = 600.0f;

	SightRotation = FRotator();
	SightSensitivity = 1.2f;

	bIsFirstPerson = true;
	bIsAbleToTogglePerson = true;

	SpringArmDefaultLength = 300.f;
	bIsSpringArmLengthChanging = false;
}

void UMarionetteSightComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}
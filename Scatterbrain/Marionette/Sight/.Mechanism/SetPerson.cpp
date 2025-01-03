#include "../MarionetteSightComponent.h"
#include "Camera/CameraComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteSightComponent::SetPerson(bool IsFirstPerson)
{
	Owner->ThirdPersonCameraComponent->SetActive(!IsFirstPerson);
	Owner->FirstPersonCameraComponent->SetActive(IsFirstPerson);
}
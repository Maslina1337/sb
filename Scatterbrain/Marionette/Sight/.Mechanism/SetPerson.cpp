#include "../MarionetteSightComponent.h"
#include "Camera/CameraComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteSightComponent::SetPerson(bool bIsFirstPerson_)
{
	Owner->ThirdPersonCameraComponent->SetActive(!bIsFirstPerson_);
	Owner->FirstPersonCameraComponent->SetActive(bIsFirstPerson_);
}
#include "../MarionetteSightComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteSightComponent::ApplySightRotation()
{
	// Owner->SpringArmComponent->SetWorldRotation(SightRotation);
	// Owner->FirstPersonCameraComponent->SetWorldRotation(SightRotation);

	if (GEngine)
	{
		FString a = FString("Sight applied. Rot: " + SightRotation.ToString());	
		GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Black, a);
	}
}

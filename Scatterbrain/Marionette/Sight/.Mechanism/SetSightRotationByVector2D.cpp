#include "../MarionetteSightComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Scatterbrain/General/Math.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteSightComponent::SetSightRotationByVector2D(FVector2D Vector2D)
{
	SightRotation.Pitch = ClampAngle(Vector2D.Y * SightSensitivity + SightRotation.Pitch);
	SightRotation.Yaw = ClampAngle(Vector2D.X * SightSensitivity + SightRotation.Yaw);

	Owner->FirstPersonCameraComponent->SetWorldRotation(SightRotation);
	Owner->SpringArmComponent->SetWorldRotation(SightRotation);
}

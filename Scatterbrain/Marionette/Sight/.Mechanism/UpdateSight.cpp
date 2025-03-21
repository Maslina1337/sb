#include "../MarionetteSightComponent.h"

#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteSightComponent::UpdateSight(const FVector2D XY)
{
	if (!IsValid(Owner->Controller)) return;
	
	FRotator ControlRotation = Owner->GetControlRotation();
	ControlRotation.Yaw += XY.X * SightSensitivity;
	ControlRotation.Pitch += XY.Y * SightSensitivity;
	
	ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch, -80.f, 80.f);
	
	Owner->Controller->SetControlRotation(ControlRotation);
}
#include "../MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Sight/MarionetteSightComponent.h"
#include "Scatterbrain/Marionette/Physics/MarionettePhysicsComponent.h"

void UMarionetteMovementComponent::SetMovementDirectionByInput(const FVector2D Input)
{
	InputVector = Input;
	
	const FVector XVector = FVector::RightVector * Input.X;
	const FVector YVector = FVector::ForwardVector * Input.Y;

	const FRotator RotationGravity = ProjectRotatorOntoPlane(Owner->Sight->SightRotation, Owner->Physics->GravitationalDirection);

	// Depending on gravity direction.
	MovementDirection = RotationGravity.RotateVector(XVector) + RotationGravity.RotateVector(YVector);

	

	const FRotator RotationXY = ProjectRotatorOntoPlane(Owner->Sight->SightRotation, FVector::UpVector);
	
	MovementDirectionXY = Vector3To2(RotationXY.RotateVector(XVector)) + Vector3To2(RotationXY.RotateVector(YVector));
	MovementDirectionXYZ = Owner->Sight->SightRotation.RotateVector(XVector) + Owner->Sight->SightRotation.RotateVector(YVector);
}
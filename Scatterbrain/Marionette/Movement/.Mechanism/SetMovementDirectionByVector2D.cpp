#include "../MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteMovementComponent::SetMovementDirectionByVector2D(const FVector2D Input)
{
	InputVector = Input;
	
	const FVector XVector = FVector::RightVector * Input.X;
	const FVector YVector = FVector::ForwardVector * Input.Y;

	const FRotator RotationXY = ProjectRotatorOntoPlane(Owner->Sight->SightRotation, FVector::UpVector);
	
	MovementDirection = Vector3To2(RotationXY.RotateVector(XVector)) + Vector3To2(RotationXY.RotateVector(YVector));
	MovementDirectionSpace = Owner->Sight->SightRotation.RotateVector(XVector) + Owner->Sight->SightRotation.RotateVector(YVector);
}
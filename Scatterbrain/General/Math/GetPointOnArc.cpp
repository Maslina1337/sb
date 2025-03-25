#include "../Math.h"

FVector2D GetPointOnArc(const FVector2D& Center, const FVector2D& TangentA, const FVector2D& TangentB, float ArcLength)
{
	// Calculating Radius.
	const float Radius = (TangentA - Center).Size();
	
	float AngleA = FMath::Atan2(TangentA.Y - Center.Y, TangentA.X - Center.X);
	float AngleB = FMath::Atan2(TangentB.Y - Center.Y, TangentB.X - Center.X);
	
	AngleA = FMath::Fmod(AngleA + 2 * PI, 2 * PI);
	AngleB = FMath::Fmod(AngleB + 2 * PI, 2 * PI);
	
	float DeltaAngle = AngleB - AngleA;
	
	if (DeltaAngle < 0.0f)
	{
		DeltaAngle += 2 * PI;
	}

	float TotalArcLength = Radius * DeltaAngle;
	
	ArcLength = FMath::Fmod(ArcLength, TotalArcLength);

	const float ArcAngle = (ArcLength / Radius);

	const float NewAngle = AngleA + ArcAngle;

	FVector2D NewPoint;
	NewPoint.X = Center.X + Radius * FMath::Cos(NewAngle);
	NewPoint.Y = Center.Y + Radius * FMath::Sin(NewAngle);

	return NewPoint;
}

FVector GetPointOnArc(const FVector& Center, const FVector& TangentA, const FVector& TangentB, const float ArcLength)
{
	{
		// Calculating Radius.
		const float Radius = (TangentA - Center).Size();
    
		// Vectors from center to tangents.
		const FVector DirA = (TangentA - Center).GetSafeNormal();
		const FVector DirB = (TangentB - Center).GetSafeNormal();
    
		// Calculating angle between A and B tangents. [rad]
		const float AngleAB = FMath::Acos(FVector::DotProduct(DirA, DirB));
    
		// Calculating full arc length between A and B tangents.
		const float FullArcLength = Radius * AngleAB;
    
		// Normalizing ArcLength.
		const float NormalizedArcLength = FMath::Clamp(ArcLength, 0.0f, FullArcLength);
    
		// Calculating angle of ArcLength [rad]
		const float Angle = NormalizedArcLength / Radius;
    
		// Finding a normal to circle.
		const FVector Normal = FVector::CrossProduct(DirA, DirB).GetSafeNormal();
    
		// Rotating the DirA vector on Calculated Angle around normal vector.
		const FQuat RotationQuat = FQuat(Normal, Angle);
		const FVector NewDirection = RotationQuat.RotateVector(DirA);
		
		return Center + NewDirection * Radius;
	}
}

FVector GetPointOnArc(const FCircle3D& Circle, const FVector& Tangent, const float Angle)
{
	{
		// Calculating Radius.
		const float Radius = (Tangent - Circle.Center).Size();
    
		// Vectors from center to tangent.
		const FVector Dir = (Tangent - Circle.Center).GetSafeNormal();
		
		const FQuat RotationQuat(Circle.Normal, Angle);
    
		// Applying rotation onto Dir vector
		const FVector NewDirection = RotationQuat.RotateVector(Dir);

		return Circle.Center + NewDirection * Radius;
	}
}
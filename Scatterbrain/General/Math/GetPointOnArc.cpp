#include "../Math.h"

FVector2D GetPointOnArc(const FCircle2D Circle, const FVector2D TangentA, const FVector2D TangentB, float ArcLength)
{
	float AngleA = FMath::Atan2(TangentA.Y - Circle.Center.Y, TangentA.X - Circle.Center.X);
	float AngleB = FMath::Atan2(TangentB.Y - Circle.Center.Y, TangentB.X - Circle.Center.X);
	
	AngleA = FMath::Fmod(AngleA + 2 * PI, 2 * PI);
	AngleB = FMath::Fmod(AngleB + 2 * PI, 2 * PI);
	
	float DeltaAngle = AngleB - AngleA;
	
	if (DeltaAngle < 0.0f)
	{
		DeltaAngle += 2 * PI;
	}

	float TotalArcLength = Circle.Radius * DeltaAngle;
	
	ArcLength = FMath::Fmod(ArcLength, TotalArcLength);

	const float ArcAngle = (ArcLength / Circle.Radius);

	const float NewAngle = AngleA + ArcAngle;

	FVector2D NewPoint;
	NewPoint.X = Circle.Center.X + Circle.Radius * FMath::Cos(NewAngle);
	NewPoint.Y = Circle.Center.Y + Circle.Radius * FMath::Sin(NewAngle);

	return NewPoint;
}
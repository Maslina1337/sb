#include "../AM_Step.h"

float FAM_Step::GetArcLength(const FCircle2D Circle, const FVector2D TangentA, const FVector2D TangentB)
{
	float AngleA = FMath::Atan2(TangentA.Y - Circle.Center.Y, TangentA.X - Circle.Center.X);
	float AngleB = FMath::Atan2(TangentB.Y - Circle.Center.Y, TangentB.X - Circle.Center.X);
	
	float DeltaAngle = AngleB - AngleA;

	// Clamping.
	if (DeltaAngle < 0)
	{
		DeltaAngle += 2 * PI;
	}
	
	return DeltaAngle * Circle.Radius;
}
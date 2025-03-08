#include "../Math.h"

FVector2D FindTangentPoint(const FVector2D Point, const FCircle2D Circle, const bool IsLeftTangent) {
	const double PointCenterLength = (Point - Circle.Center).Length();

	// If the Point is too close to the circle, there are no tangents.
	if (PointCenterLength <= Circle.Radius) {
		return FVector2D::ZeroVector;
	}

	// The angle between the vector PC and the tangent.
	const double Theta = asin(Circle.Radius / PointCenterLength);

	// The main angle of the PC vector relative to the X axis.
	const double Phi = atan2(Point.Y - Circle.Center.Y, Point.X - Circle.Center.X);

	// Select the angle for the tangent depending on the direction of IsLeftTangent.
	const double Alpha = IsLeftTangent ? (Phi + Theta) : (Phi - Theta);

	// Calculate the coordinates of the point of contact.
	FVector2D T;
	T.X = Circle.Center.X + Circle.Radius * cos(Alpha);
	T.Y = Circle.Center.Y + Circle.Radius * sin(Alpha);

	return T;
}
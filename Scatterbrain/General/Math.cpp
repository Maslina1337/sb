#pragma once

#include "Math.h"

float AngleBetweenTwoVectors(FVector V1, FVector V2, const bool NeedNegative) {
	const FVector V1Norm = V1.GetSafeNormal();
	const FVector V2Norm = V2.GetSafeNormal();
	if (NeedNegative) {
		if (FVector::CrossProduct(V1Norm, V2Norm).Z > 0) {
			return acos(FVector::DotProduct(V1Norm, V2Norm));
		} else {
			return acos(FVector::DotProduct(V1Norm, V2Norm)) * -1;
		}
	} else {
		return acos(FVector::DotProduct(V1Norm, V2Norm));
	}
}

float DistanceBetweenLineAndPoint(FVector P, FVector A, FVector B)
{
	const FVector AB = B - A;
	const FVector AP = P - A;
	const FVector BP = P - B;

	float AB_length = AB.Length();
	FVector AB_normalized = {AB.X / AB_length, AB.Y / AB_length, AB.Z / AB_length};

	const float Projection = AP.Dot(AB_normalized);
	if (Projection < 0.0f) {
		return AP.Length();
	} else if (Projection > AB_length) {
		return BP.Length();
	} else {
		const FVector ClosestPoint = A + AB_normalized * Projection;
		return (P - ClosestPoint).Length();
	}
}

float DistanceBetweenLineAndPoint(FVector2D P, FVector2D A, FVector2D B)
{
	const FVector2D AB = B - A;
	const FVector2D AP = P - A;
	const FVector2D BP = P - B;

	float AB_length = AB.Length();
	FVector2D AB_normalized = {AB.X / AB_length, AB.Y / AB_length};

	const float Projection = AP.Dot(AB_normalized);
	if (Projection < 0.0f) {
		return AP.Length();
	} else if (Projection > AB_length) {
		return BP.Length();
	} else {
		const FVector2D ClosestPoint = A + AB_normalized * Projection;
		return (P - ClosestPoint).Length();
	}
}

bool IsLineHitPlane(FVector PlaneNormal, FVector PlaneLocation, FVector LineA, FVector LineB)
{
	return (PlaneNormal.X * (LineA.X - PlaneLocation.X)) + (PlaneNormal.Y * (LineA.Y - PlaneLocation.Y)) + (PlaneNormal.Z * (LineA.Z - PlaneLocation.Z)) > 0;
}

float Hypotenuse(float CathetusA, float CathetusB)
{
	return sqrt(CathetusA * CathetusA + CathetusB * CathetusB);
}

float AngleBetweenTwoRotators(FRotator R1, FRotator R2)
{
	FQuat Quat1 = FQuat(R1);
	FQuat Quat2 = FQuat(R2);
	
	float Angle = FMath::Acos((Quat1 | Quat2)) * 2.0f * (180.0f / PI);

	return Angle;
}

FRotator ProjectRotatorOntoPlane(const FRotator Rotator, const FVector PlaneNormal)
{
	// Преобразуем ротатор в кватернион
	FQuat Quat = FQuat(Rotator);

	// Проецируем кватернион на плоскость
	FVector Forward = Quat.GetForwardVector();
	FVector ProjectedForward = UKismetMathLibrary::ProjectVectorOnToPlane(Forward, PlaneNormal);

	// Создаем новый кватернион из проецированного вектора
	FQuat ProjectedQuat = FQuat::FindBetweenNormals(Forward, ProjectedForward) * Quat;

	// Преобразуем кватернион обратно в ротатор
	return ProjectedQuat.Rotator();
}

FRotator VectorToRotatorWithRoll(const FVector& Vector, float Roll)
{
	// Преобразуем вектор в кватернион
	FQuat Quat = FQuat::FindBetweenNormals(FVector::ForwardVector, Vector.GetSafeNormal());

	// Создаем кватернион для заданного roll
	FQuat RollQuat = FQuat(Vector.GetSafeNormal(), FMath::DegreesToRadians(Roll));

	// Объединяем кватернионы
	FQuat FinalQuat = RollQuat * Quat;

	// Преобразуем кватернион в ротатор
	return FinalQuat.Rotator();
}

float ClampAngle(float Angle) {
	Angle += 180;
	Angle = fmod(Angle, 360);
	Angle -= 180;

	return Angle;
}

FVector2D Vector3To2(const FVector Vector)
{
	return FVector2D(Vector.X, Vector.Y);
}

FVector Vector2To3(const FVector2D Vector2D)
{
	return FVector(Vector2D.X, Vector2D.Y, 0);
}

bool IsLineIntersectingCircle(const FLine2D Line, const FCircle2D Circle)
{
	const float DistX = Line.End.X - Line.Start.X;
	const float DistY = Line.End.Y - Line.Start.Y;
	const float Length = sqrt(DistX * DistX + DistY * DistY);
	const float Dot = (((Circle.Center.X - Line.Start.X) * DistX) + ((Circle.Center.Y - Line.Start.Y) * DistY)) / (Length * Length);

	FVector2D Closest;
	Closest.X = Line.Start.X + (Dot * DistX);
	Closest.Y = Line.Start.Y + (Dot * DistY);

	return (Circle.Center - Closest).Length() <= Circle.Radius;
}

bool IsRectangleIntersectingCircle(const FRectangle2D Rectangle, const FCircle2D Circle)
{
	if ((Circle.Center - Rectangle.TopLeft).Length() <= Circle.Radius || (Circle.Center - Rectangle.BottomRight).Length() <= Circle.Radius) {
		return true;
	}

	const FLine2D Left = FLine2D(Rectangle.TopLeft, FVector2D(Rectangle.TopLeft.X, Rectangle.BottomRight.Y));
	const FLine2D Right = FLine2D(Rectangle.BottomRight, FVector2D(Rectangle.TopLeft.Y, Rectangle.BottomRight.X));
	const FLine2D Top = FLine2D(Rectangle.TopLeft, FVector2D(Rectangle.TopLeft.Y, Rectangle.BottomRight.X));
	const FLine2D Bottom = FLine2D(Rectangle.BottomRight, FVector2D(Rectangle.TopLeft.X, Rectangle.BottomRight.Y));

	return IsLineIntersectingCircle(Left, Circle) ||
		   IsLineIntersectingCircle(Right, Circle) ||
		   IsLineIntersectingCircle(Top, Circle) ||
		   IsLineIntersectingCircle(Bottom, Circle);
}

float GetProjectionLength(const FVector Vector, const FVector On, const bool NeedNegative)
{
	const float DotProduct = FVector::DotProduct(Vector, On);
	const float OnLength = On.Size();
	return NeedNegative ? DotProduct / OnLength : abs(DotProduct / OnLength);
}

FVector ClearZ(FVector Vector)
{
	Vector.Z = 0;
	return Vector;
}

FVector ClearX(FVector Vector)
{
	Vector.X = 0;
	return Vector;
}

FVector ClearY(FVector Vector)
{
	Vector.Y = 0;
	return Vector;
}

FVector2D ClearX(FVector2D Vector2D)
{
	Vector2D.X = 0;
	return Vector2D;
}

FVector2D ClearY(FVector2D Vector2D)
{
	Vector2D.Y = 0;
	return Vector2D;
}
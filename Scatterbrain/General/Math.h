#pragma once

#include "Kismet/KismetMathLibrary.h" // Important!
#include <cmath> // Important!

struct FLine2D
{
	FLine2D()
	{
		Start = FVector2D::ZeroVector;
		End = FVector2D::ZeroVector;
	}
	
	FLine2D(FVector2D Start_, FVector2D End_)
	{
		Start = Start_;
		End = End_;
	}
	
	FVector2D Start;
	FVector2D End;
};

struct FCircle2D
{
	FCircle2D()
	{
		Center = FVector2D::ZeroVector;
		Radius = 0.0f;
	}
	
	FCircle2D(FVector2D Center_, float Radius_)
	{
		Center = Center_;
		Radius = Radius_;
	}
	
	FVector2D Center;
	float Radius;
};

struct FRectangle2D
{
	FRectangle2D()
	{
		TopLeft = FVector2D::ZeroVector;
		BottomRight = FVector2D::ZeroVector;
	}
	
	FRectangle2D(FVector2D TopLeft_, FVector2D BottomRight_)
	{
		TopLeft = TopLeft_;
		BottomRight = BottomRight_;
	}
	
	FVector2D TopLeft;
	FVector2D BottomRight;
};

float AngleBetweenTwoVectors(FVector V1, FVector V2, const bool NeedNegative = false);
float DistanceBetweenLineAndPoint(FVector P, FVector A, FVector B);
float DistanceBetweenLineAndPoint(FVector2D P, FVector2D A, FVector2D B);
bool IsLineHitPlane(FVector PlaneNormal, FVector PlaneLocation, FVector LineA, FVector LineB);
float Hypotenuse(float CathetusA, float CathetusB);
float AngleBetweenTwoRotators(FRotator R1, FRotator R2);
FRotator ProjectRotatorOntoPlane(const FRotator Rotator, const FVector PlaneNormal);
FRotator VectorToRotatorWithRoll(const FVector Vector, float Roll);
float ClampAngle(float Angle);
FVector2D Vector3To2(const FVector Vector);
FVector Vector2To3(const FVector2D Vector2D);
bool IsLineIntersectingCircle(FLine2D Line, FCircle2D Circle);
bool IsRectangleIntersectingCircle(FRectangle2D Rectangle, FCircle2D Circle);
float GetProjectionLength(const FVector Vector, const FVector On, const bool NeedNegative = false);

FVector ClearZ(FVector);
FVector ClearX(FVector);
FVector ClearY(FVector);

FVector2D ClearX(FVector2D);
FVector2D ClearY(FVector2D);


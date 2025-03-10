#include "PM_Walk.h"
#include "../../../Marionette.h"
#include "../../../Types/TwoLimbs.h"
#include "Scatterbrain/Marionette/Movement/ActiveMoves/Step/AM_Step.h"

using namespace TwoLimbs;

FPM_Walk::FPM_Walk(AMarionette* NewOwner)
{
	Owner = NewOwner;

	FootBox = FVector(30, 10, 10);
	SideWalkAngleBegin = 60.f;
	SideWalkAngleEnd = 120.f;
	WalkStepDirectionChangeCoefficient = 3.f;
	RaysFarRotation = -10.f;
	IterationsCountOfLocationClarify = 1;
	StepVelocityWalk = 70.f;
	AngleVisionToMoveDirection = 0.f;
}

void FPM_Walk::Tick()
{
	FAM_Step_Params AM_Step_Params;

	//// Leg choose ////
	
	if (Owner->Physics->States->GetBodyState() == EBodyPhysState::Stable)
	{
		FVector PointBetweenFoots =
			(Owner->Rig->FootGoalLocation[Left] - Owner->Rig->FootGoalLocation[Right]) / 2 + Owner->Rig->FootGoalLocation[Right];
		
		PointBetweenFoots.Z = 0;

		const FVector MovementDirection = Owner->Movement->MovementDirection;

		TArray<float> FootAngle;
		FootAngle.Init(0, 2);
		
		FootAngle[Left] = AngleBetweenTwoVectors(Owner->Rig->FootGoalLocation[Left] - PointBetweenFoots,MovementDirection);
		FootAngle[Right] = AngleBetweenTwoVectors(Owner->Rig->FootGoalLocation[Right] - PointBetweenFoots, MovementDirection);

		if (FootAngle[Left] > FootAngle[Right])
		{
			AM_Step_Params.Act = Right;
			AM_Step_Params.Sup = Left;
		}
		else
		{
			AM_Step_Params.Act = Left;
			AM_Step_Params.Sup = Right;
		}
	}

	//// Finding target point. ////

	const float FirstRayWidth = Hypotenuse(FootBox.X, FootBox.Y);
	const float SecondRayXRotation = (AM_Step_Params.Act == Left ? 5.0f : -5.0f);

	

	//AM_Step_Params.TargetPoint = &;

	//Setting Params for step. (even if it's already active, it doesn't matter)
	FAM_Step* AM_Step = Owner->Movement->AM_Step;
	
	if (AM_Step->IsActive()) AM_Step->SetParamsFree(AM_Step_Params);
	else AM_Step->Activate(AM_Step_Params);
}
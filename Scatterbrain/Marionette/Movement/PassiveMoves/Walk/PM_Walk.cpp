#include "PM_Walk.h"
#include "../../../Marionette.h"
#include "../../../Types/TwoLimbs.h"

using namespace TwoLimbs;

FPM_Walk::FPM_Walk(AMarionette* NewOwner)
{
	Owner = NewOwner;
}

void FPM_Walk::Tick()
{
	FAM_Step_Params AM_Step_Params;

	//// Leg choose ////

	// If both are fulcrums.
	if (Owner->Physics->GetFootState(Left) == EFootPhysState::Fulcrum &&
		Owner->Physics->GetFootState(Right) == EFootPhysState::Fulcrum)
	{
		FVector PointBetweenFoots =
			(Owner->Rig->FootGoalLocation[Left] - Owner->Rig->FootGoalLocation[Right]) / 2 + Owner->Rig->FootGoalLocation[Right];
		
		PointBetweenFoots.Z = 0;

		const FVector2D MovementDirection = Owner->Movement->MovementDirection;

		TArray<float> FootAngle;
		FootAngle.Init(0, 2);
		
		FootAngle[Left] = AngleBetweenTwoVectors(Owner->Rig->FootGoalLocation[Left] - PointBetweenFoots,Vector2To3(MovementDirection));
		FootAngle[Right] = AngleBetweenTwoVectors(Owner->Rig->FootGoalLocation[Right] - PointBetweenFoots, Vector2To3(MovementDirection));

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
	} else
	{
		if (Owner->Physics->GetFootState(Left) == EFootPhysState::Fulcrum)
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

	const float FirstRayWidth = Hypotenuse(Owner->Movement->FootBox.X, Owner->Movement->FootBox.Y);
	const float SecondRayXRotation = (AM_Step_Params.Act == Left ? 5.0f : -5.0f);

	

	//AM_Step_Params.TargetPoint = &;

	//Setting Params for step. (even if it's already active, it doesn't matter)
	Owner->Movement->AM_Step->SetParams(AM_Step_Params);
}


// Projecting Vision Rotator and Input Rotator to Horizontal plane and finding angle between it.
// const FRotator VisionRotationXY = ProjectRotatorOntoPlane(VisionRotation, FVector::UpVector);
// const FRotator InputRotator = VectorToRotatorWithRoll(MovementDirection, -90);
// const FRotator InputRotatorXY = ProjectRotatorOntoPlane(InputRotator, FVector::UpVector);
// const float AngleVisionToMoveDirection = ClampAngle(AngleBetweenTwoRotators(VisionRotationXY, InputRotatorXY));

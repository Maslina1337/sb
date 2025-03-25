#include "AM_Tiptoe.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"
#include "Scatterbrain/Marionette/Types/LeftRight.h"

using namespace LeftRight;

void FAM_Tiptoe::Reset()
{
	LEFT_RIGHT_INIT(FootPath, 0.f)
	LEFT_RIGHT_INIT(FootPathTravelled, 0.f)
	LEFT_RIGHT_INIT(FootVelocity, 0.f)
	LEFT_RIGHT_INIT(FootLocationOnStart, FVector::ZeroVector)
	//LEFT_RIGHT_INIT(FootPathCircle, FCircle2D())
}

FAM_Tiptoe::FAM_Tiptoe() : TActiveMove()
{
	Reset();
	DebugName = "AM_Tiptoe";
}

void FAM_Tiptoe::SetOwner(AMarionette* Owner_)
{
	Owner = Owner_;
	R = Owner->Rig;
}


void FAM_Tiptoe::Start()
{
	if (Params.bLeftToTiptoe)
	{
		FootPath[Left] = PI * R->FootToeLength * R->TiptoesAngle / 90.f;
		FootVelocity[Left] = FootPath[Left] / Params.TimeToGoTiptoe;
		FootLocationOnStart[Left] = R->ToeLocation[Left];
		const FVector CircleNormal = R->ToeRotation[Left].RotateVector(FVector::ForwardVector).Cross(R->ToeLocation[Left] - R->FootLocation[Left]);
		//FootPathCircle[Left] = FCircle3D(R->ToeLocation[Left], R->FootToeLength, CircleNormal);
	}
	
	if (Params.bRightToTiptoe)
	{
		FootPath[Right] = PI * R->FootToeLength * R->TiptoesAngle / 90.f;
		FootVelocity[Right] = FootPath[Right] / Params.TimeToGoTiptoe;
		FootLocationOnStart[Right] = R->ToeLocation[Right];
		//FootPathCircle[Right] = FCircle3D();
	}
}

void FAM_Tiptoe::Progress()
{
	FootPathTravelled[Left] += FootVelocity[Left] * Owner->TickDeltaTime;
	GetPointOnArc(R->ToeLocation[Left], R->FootLocation[Left], )
}

void FAM_Tiptoe::End()
{
	if (ParamsFree.Callback != nullptr) ParamsFree.Callback();
}
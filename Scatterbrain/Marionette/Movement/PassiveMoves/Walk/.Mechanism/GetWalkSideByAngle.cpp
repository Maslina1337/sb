#include "../PM_Walk.h"
#include "Scatterbrain/Marionette/Marionette.h"

EWalkSide FPM_Walk::GetWalkSideByAngle()
{
	if (AngleVisionToMoveDirection > Owner->Movement->SideWalkAngleBegin &&
		AngleVisionToMoveDirection < Owner->Movement->SideWalkAngleEnd) {
		return EWalkSide::Right;
	}
	
	if (AngleVisionToMoveDirection < -(Owner->Movement->SideWalkAngleEnd) &&
		AngleVisionToMoveDirection > Owner->Movement->SideWalkAngleEnd) {
		return EWalkSide::Backyard;
	}

	if (AngleVisionToMoveDirection < -(Owner->Movement->SideWalkAngleBegin) &&
		AngleVisionToMoveDirection > -(Owner->Movement->SideWalkAngleEnd)) {
		return EWalkSide::Left;
	}

	return EWalkSide::Forward;
}
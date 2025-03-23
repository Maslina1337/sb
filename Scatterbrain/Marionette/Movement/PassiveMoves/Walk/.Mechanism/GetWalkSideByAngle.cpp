#include "../PM_Walk.h"
#include "Scatterbrain/Marionette/Marionette.h"

EWalkSide UPM_Walk::GetWalkSideByAngle()
{
	if (AngleVisionToMoveDirection > SideWalkAngleBegin &&
		AngleVisionToMoveDirection < SideWalkAngleEnd) {
		return EWalkSide::Right;
	}
	
	if (AngleVisionToMoveDirection < -(SideWalkAngleEnd) &&
		AngleVisionToMoveDirection > SideWalkAngleEnd) {
		return EWalkSide::Backyard;
	}

	if (AngleVisionToMoveDirection < -(SideWalkAngleBegin) &&
		AngleVisionToMoveDirection > -(SideWalkAngleEnd)) {
		return EWalkSide::Left;
	}

	return EWalkSide::Forward;
}
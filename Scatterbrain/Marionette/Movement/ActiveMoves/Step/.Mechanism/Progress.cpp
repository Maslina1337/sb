#include "../AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"

void FAM_Step::Progress()
{
	// New foot location.

	MoveFoot();
	
	// New actor location.

	//TransferWeight();

	// Percent update.

	StepPercent += Owner->TickDeltaTime * Params.StepSpeed;
}
#include "AM_Step.h"
#include "Scatterbrain/Marionette/Marionette.h"

FAM_Step::FAM_Step(AMarionette* OwnerClass)
{
	// Set default values.
	
	Owner = OwnerClass;
	ParamsIsNull = true;
	Params = FAM_Step_Params();
	ParamsFree = FAM_Step_Params();
}

void FAM_Step::SetParams(FAM_Step_Params NewParams)
{
	ParamsFree = NewParams;
	// Is step inactive now?
	if (Owner->Movement->FindCurrentActiveMove(EActiveMove::Step) == -1)
	{
		ParamsIsNull = false;
		Params = NewParams;
	}
}

void FAM_Step::Tick()
{
	// If params is null - capitulate.
	if (ParamsIsNull)
	{
		return;
	}
	
	if (Owner->Movement->ItsFirstIterationActive(EActiveMove::Step))
	{
		Start();
	}
	
	Progress();
}
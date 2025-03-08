#include "ActiveMove.h"

#include "Scatterbrain/Marionette/Marionette.h"

FActiveMoveBase::FActiveMoveBase(AMarionette*)
{
	Owner = nullptr;
	bIsActive = false;
	bIsActivePastTick = false;
}

FActiveMoveBase::~FActiveMoveBase() {}

template <typename T>
void TActiveMove<T>::Activate(T Params_)
{
	if (!IsParamsValid(Params_)) return;
	if (bIsActive) return;
	
	Owner->Movement->AddActiveMove(this);
	
	Params = Params_;
	ParamsFree = Params_;
	
	bIsActive = true;
	bIsActivePastTick = false;
}

template <typename T>
void TActiveMove<T>::SetParamsFree(T Params_)
{
	if (!IsParamsValid(Params_)) return;
	ParamsFree = Params_;
}

void FActiveMoveBase::Tick()
{
	if (bIsActivePastTick) Progress();
	else Start();
	
	bIsActivePastTick = true;
}
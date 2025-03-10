#include "ActiveMove.h"

FActiveMoveBase::FActiveMoveBase(AMarionette* Owner_)
{
	Owner = Owner_;
	bIsActive = false;
	bIsActivePastTick = false;
	EnumName = EActiveMove::None;
}

FActiveMoveBase::~FActiveMoveBase() {}

void FActiveMoveBase::Tick()
{
	if (bIsActivePastTick) Progress();
	else Start();
	
	bIsActivePastTick = true;
}
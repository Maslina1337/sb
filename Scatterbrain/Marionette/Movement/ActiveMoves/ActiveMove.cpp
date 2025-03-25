#include "ActiveMove.h"

FActiveMoveBase::FActiveMoveBase()
{
	Owner = nullptr;
	bIsActive = false;
	bIsActivePastTick = false;
}

FActiveMoveBase::~FActiveMoveBase() {}

void FActiveMoveBase::SetOwner(AMarionette* Owner_)
{
	Owner = Owner_;
}

void FActiveMoveBase::TickManual()
{
	if (bIsActivePastTick) Progress();
	else { Reset(); Start(); }
	
	bIsActivePastTick = true;
}
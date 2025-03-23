#include "ActiveMove.h"

UActiveMoveBase::UActiveMoveBase()
{
	Owner = nullptr;
	bIsActive = false;
	bIsActivePastTick = false;
}

UActiveMoveBase::~UActiveMoveBase() {}

void UActiveMoveBase::SetOwner(AMarionette* Owner_)
{
	Owner = Owner_;
}

void UActiveMoveBase::TickManual()
{
	if (bIsActivePastTick) Progress();
	else Start();
	
	bIsActivePastTick = true;
}
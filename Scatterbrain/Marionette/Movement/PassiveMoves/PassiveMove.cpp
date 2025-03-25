#include "PassiveMove.h"

FPassiveMove::FPassiveMove()
{
	Owner = nullptr;
	bIsActive = false;
	bIsActivePastTick = false;
}

FPassiveMove::~FPassiveMove() {}

void FPassiveMove::SetOwner(AMarionette* Owner_)
{
	Owner = Owner_;
}

void FPassiveMove::TickManual()
{
	bIsActivePastTick = true;
	Progress();
}
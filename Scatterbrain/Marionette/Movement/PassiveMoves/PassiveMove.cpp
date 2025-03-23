#include "PassiveMove.h"

UPassiveMove::UPassiveMove()
{
	Owner = nullptr;
	bIsActive = false;
	bIsActivePastTick = false;
}

UPassiveMove::~UPassiveMove() {}

void UPassiveMove::SetOwner(AMarionette* Owner_)
{
	Owner = Owner_;
}

void UPassiveMove::TickManual()
{
	bIsActivePastTick = true;
	Progress();
}
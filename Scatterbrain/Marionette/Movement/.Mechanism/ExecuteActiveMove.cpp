#include "../MarionetteMovementComponent.h"

void UMarionetteMovementComponent::ExecuteActiveMoves()
{
	for (uint8 i = 0; i < GetCurrentActiveMoves().Num(); i++)
	{
		switch(GetCurrentActiveMoveByIndex(i))
		{
		case EActiveMove::None:
			break;	
		case EActiveMove::Step:
			//AM_Step->Tick();
			break;
		}	
	}
}
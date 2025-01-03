#include "../MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteMovementComponent::ChoosePassiveMove()
{
    if (Owner->Physics->GetBodyState() == EBodyPhysState::Fall)
    {
        SetPassiveMove(EPassiveMove::Fall);
        return;
    }

    if (Owner->Physics->GetBodyState() == EBodyPhysState::Surf)
    {
        SetPassiveMove(EPassiveMove::Surf);
        return;
    }

    if (Owner->Physics->GetIsBodyStable())
    {
        if (MovementDirection.Length() == 0)
        {
            SetPassiveMove(EPassiveMove::Stand);
        }
        
        if (bIsRunning)
        {
            SetPassiveMove(EPassiveMove::Run);
        }
        else
        {
            SetPassiveMove(EPassiveMove::Walk);
        }
        return;
    }
}
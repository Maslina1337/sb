#include "../MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

void UMarionetteMovementComponent::ChoosePassiveMove()
{
    if (Owner->Physics->States->GetBodyState() == EBodyPhysState::Fall)
    {
        SetPassiveMove(EPassiveMove::Fall);
        return;
    }

    if (Owner->Physics->States->GetBodyState() == EBodyPhysState::Surf)
    {
        SetPassiveMove(EPassiveMove::Surf);
        return;
    }

    if (Owner->Physics->States->GetBodyState() == EBodyPhysState::Stable)
    {
        if (MovementDirection.Length() == 0)
        {
            SetPassiveMove(EPassiveMove::Stand);
        }
        
        SetPassiveMove(EPassiveMove::Walk);
    }
}
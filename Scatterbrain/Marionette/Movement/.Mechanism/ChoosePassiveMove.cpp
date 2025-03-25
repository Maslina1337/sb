#include "../MarionetteMovementComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Physics/MarionettePhysicsComponent.h"

#include "../PassiveMoves/Fall/PM_Fall.h"
#include "../PassiveMoves/Walk/PM_Walk.h"

void UMarionetteMovementComponent::ChoosePassiveMove()
{
    switch (Owner->Physics->States->GetBodyState())
    {
        case EPhysicState::Fall:
            SetPassiveMove(PM_Fall);
            break;
        case EPhysicState::Surf:
            // SetPassiveMove(PM_Surf);
            break;
        case EPhysicState::Stable:
            if (MovementDirection.Length() == 0) { /*SetPassiveMove(PM_Stand)*/ }
            else SetPassiveMove(PM_Walk);
            break;
        default:
            break;
    }
}
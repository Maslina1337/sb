#pragma once

//// ALL YOU NEED TO DO TO ADD EFFECT TO THE LIST ////

// #include "MassRevision/EFCT_EffectName.h"

// FEFCT_EffectName EffectName; // In EFFECTS_DECLARATION

// EffectName = FEFCT_EffectName(Owner); // In EFFECTS_INIT

#include "MassRevision/EFCT_MassRevision.h"

#define EFFECTS_DECLARATION \
FEFCT_MassRevision* MassRevision;

#define EFFECTS_INIT \
MassRevision = new FEFCT_MassRevision(Owner);
#pragma once

#include "Scatterbrain/Marionette/Types/FParamsStrict.h"

// Mass Revision effect will use this params on start.

struct FEFCT_MassRevision_Params final : public FParamsStrict
{
	// Empty constructor
	FEFCT_MassRevision_Params()
	{
		Mass = 0;
	}
	
	// Params valid criterion.
	virtual bool IsValid() const override
	{
		if (Mass > 1000 || Mass < 0) return false;
		return true;
	} 
	
	float Mass; // 0-1.
};

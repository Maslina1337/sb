#pragma once

// Stunning effect will use this params on start.

struct FEFCT_MassRevision_Params
{
	// Empty constructor
	FEFCT_MassRevision_Params()
	{
		Mass = 0;
	}
	
	// Params valid criterion.
	bool IsValid() const 
	{
		if (Mass > 1000 || Mass < 0) return false;
		return true;
	}
	
	float Mass; // 0-1.
};

#pragma once

// Stunning effect will use this params on start.

struct FEFCT_Stunning_Params
{
	FEFCT_Stunning_Params()
	{
		Power = 0;
	}
	
	// Params valid criterion.
	bool IsValid() const 
	{
		if (Power > 1 || Power <= 0) return false;
		return true;
	}
	
	float Power; // 0-1.
};

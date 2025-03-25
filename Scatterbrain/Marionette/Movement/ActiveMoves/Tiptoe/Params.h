#pragma once
#include "Scatterbrain/Marionette/Types/FParamsStrict.h"

struct FAM_Tiptoe_Params final : FParamsStrict 
{
	FAM_Tiptoe_Params()
	{
		bLeftToTiptoe = false;
		bRightToTiptoe = false;
		TimeToGoTiptoe = 0.2f;
		
		Callback = nullptr;
	}

	FAM_Tiptoe_Params(const bool bLeftToTiptoe_, const bool bRightToTiptoe_, const float TimeToGoTiptoe_, void (*Callback_)())
	{
		bLeftToTiptoe = bLeftToTiptoe_;
		bRightToTiptoe = bRightToTiptoe_;
		TimeToGoTiptoe = TimeToGoTiptoe_;
		
		Callback = Callback_;
	}
	
	virtual ~FAM_Tiptoe_Params() override {};

	// Should the left foot stand on tiptoes?
	bool bLeftToTiptoe;

	// Should the right foot stand on tiptoes?
	bool bRightToTiptoe;
	
	// The time it takes for the foot to stand on its toes. [s]
	float TimeToGoTiptoe;

	// // The leg mast be fulcrum?
	// // {If toe is looking at top - then tiptoe of it leg can't be considered as fulcrum.}
	// bool bFulcrumStrict;

	void (*Callback)();
};
#pragma once

struct FParamsStrict
{
	// Empty constructor
	FParamsStrict() {}
	virtual ~FParamsStrict() {}
	
	// Params valid criterion.
	virtual bool IsValid() const { return true; }
};
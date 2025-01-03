#pragma once

#include "../../../Effect.h"
#include "./EFCT_Stunning_Params.h"

class AMarionette;

class FEFCT_Stunning : public FEffect<FEFCT_Stunning_Params>
{
	virtual void Start(float, FEFCT_Stunning_Params) override;
	virtual void Progress() override;
	virtual void End() override;
	virtual void OnUpdateParamsFree(float, FEFCT_Stunning_Params) override;
	virtual void ForcedEnd() override;
};
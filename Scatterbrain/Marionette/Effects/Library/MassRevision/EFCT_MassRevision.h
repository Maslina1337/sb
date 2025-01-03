#pragma once

#include "../../EffectStatus.h"
#include "./EFCT_MassRevision_Params.h"

class FEFCT_MassRevision : public FEffectStatus<FEFCT_MassRevision_Params>
{
public:
	//FEFCT_MassRevision(AMarionette*);
	using FEffectStatus::FEffectStatus;

protected:
	virtual void Start(float, FEFCT_MassRevision_Params) override;
	virtual void End() override;
	virtual void OnUpdateParamsFree(float, FEFCT_MassRevision_Params) override;
	virtual void ForcedEnd() override;
};
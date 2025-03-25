#pragma once

#include "Params.h"
#include "Scatterbrain/General/Math.h"
#include "../ActiveMove.h"

class AMarionette;
class UMarionetteRigComponent;

class FAM_Tiptoe final : public TActiveMove<FAM_Tiptoe_Params>
{
public:
	
	FAM_Tiptoe();

	virtual void SetOwner(AMarionette* Owner_) override;
	
private:
	
	virtual void Start() override; // Executed on first frame active.
	virtual void Progress() override; // Executed every tick (starting on second frame active).
	virtual void End() override; // Not executed automatically. Can be called manually in progress when it's done.

	// Called in constructor, so you should use IT as a constructor for non-constants.
	// Also, can be called manually to reset variables to default values.
	virtual void Reset() override;

	float GetLastTickRemainingTime() const { return LastTickRemainingTime; }
	
private:
	TArray<float> FootPath;
	TArray<float> FootPathTravelled;
	TArray<float> FootVelocity; // [units/s]
	//TArray<FCircle3D> FootPathCircle;
	TArray<FVector> FootLocationOnStart;

	float LastTickRemainingTime;

	UMarionetteRigComponent* R;
};

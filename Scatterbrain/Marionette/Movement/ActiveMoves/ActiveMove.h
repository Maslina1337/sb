// Parent class for every active move.

#pragma once

#include "Scatterbrain/Marionette/Marionette.h"
#include "Scatterbrain/Marionette/Types/EMove.h"
#include "Scatterbrain/Marionette/Movement/MarionetteMovementComponent.h"

// Not templated class that can be used as type for TArray to keep active moves.
// And be able to execute Tick method from it.
class FActiveMoveBase {
public:
	
	explicit FActiveMoveBase(AMarionette* Owner_);
	virtual ~FActiveMoveBase();
	
	void Tick();
	
	bool IsActive() const { return bIsActive; }
	bool IsActivePastTick() const { return bIsActivePastTick; }

	EActiveMove GetEnumName() const { return EnumName; }

protected:
	
	virtual void Start() = 0; // Executed on first frame active.
	virtual void Progress() = 0; // Executed every tick (starting on second frame active).
	virtual void End() = 0; // Not executed automatically. Can be called manually in progress when it's done.

protected:
	
	AMarionette* Owner; // Marionette instance.

	bool bIsActive;
	bool bIsActivePastTick;

	EActiveMove EnumName;
};



template <typename T>
class TActiveMove : public FActiveMoveBase {
public:
	
	using FActiveMoveBase::FActiveMoveBase;

	void Activate(T Params_) {
		if (!IsParamsValid(Params_)) return;
		if (bIsActive) return;
	
		Owner->Movement->AddActiveMove(EnumName);
	
		Params = Params_;
		ParamsFree = Params_;
	
		bIsActive = true;
		bIsActivePastTick = false;
	}
	
	void SetParamsFree(T Params_)
	{
		if (!IsParamsValid(Params_)) return;
		ParamsFree = Params_;
	}

	// Params valid check. If you have a valid criteria, implement it as a IsValid function in Params struct and call
	// it on overriding. Or else don't override it. It'll be "return true;".
	virtual bool IsParamsValid(T Params_) { return true; }

	T GetParams() const { return Params; }; // Params Getter.
	T GetParamsFree() const { return ParamsFree; }; // ParamsFree Getter.

protected:
	
	T Params; // Can be changed only when step isn't started yet.
	T ParamsFree; // Can be changed at any time.
};
// Parent class for every effect that unable to tick and is a status.
// This means that only something from the outside will access the effect if it is active.

#pragma once

class AMarionette;

// Not templated class that can be used as type for TArray to keep effects.
// And be able to execute Deactivate and Tick methods from it.
class FEffectStatusBase {
public:
	FEffectStatusBase(AMarionette*);

	void Deactivate(); // To force effect to end. { true - deactivated, false - deactivation failed }
	bool IsActive() const; // Getter for bIsActive.

protected:
	//// Child additions. ////
	
	virtual void End() = 0; // Executed on expected deactivation tick, when active time is ending.
	
	// Executed on tick of forced unexpected deactivation, when something from outside forced the effect to end.
	virtual void ForcedEnd() = 0;

protected:
	AMarionette* Owner;
	bool bIsActive;
	
	FTimerHandle TimerHandle;
	
	float Duration; // Seconds. If 0 - the stun is infinite until it is forcibly ended.
};



template <typename T>
class FEffectStatus : public FEffectStatusBase {
public:
	//FEffectStatus(AMarionette*);
	using FEffectStatusBase::FEffectStatusBase;
	
	//// Parent parts of functionality. ////

	bool Activate(float, T); // To activate effect with params. { true - activated, false - activation failed }
	bool UpdateParamsFree(float, T); // To update params when effect is active. { true - updated, false - update failed }

	T GetParams() const { return Params; }; // Params Getter.
	T GetParamsFree() const { return ParamsFree; }; // ParamsFree Getter.

protected:
	//// Child additions. ////
	
	virtual void Start(float, T) = 0; // Executed on activation tick.
	virtual void OnUpdateParamsFree(float, T) = 0; // Child addition to UpdateParamsFree method.

protected:
	T Params; // Can be changed only on activation.
	T ParamsFree; // Can be changed at any time.
};
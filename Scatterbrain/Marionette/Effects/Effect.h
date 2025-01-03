// Parent class for every effect that able to tick.

#pragma once

class AMarionette;

// Not templated class that can be used as type for TArray to keep effects.
// And be able to execute Deactivate and Tick methods from it.
class FEffectBase {
public:
	FEffectBase(AMarionette*);

	void Deactivate(); // To force effect to end.
	void Tick(); // To simple check if effect can tick and execute tick function.

protected:
	//// Child additions. ////
	
	virtual void Progress() = 0; // Executed every frame (tick) when activated. Except first tick and last.
	virtual void End() = 0; // Executed on expected deactivation tick, when active time is ending.
	
	// Executed on forced unexpected deactivation tick, when something from outside forced the effect to end.
	virtual void ForcedEnd() = 0;

protected:
	AMarionette* Owner;
	bool bIsActive;
	FTimerHandle TimerHandle;
	float Duration; // Seconds. If 0 - the stun is infinite until it is forcibly ended.
	// float TimeElapsed; // Seconds. Amount of time elapsed since activation.
};



template <typename T>
class FEffect : public FEffectBase {
public:
	using FEffectBase::FEffectBase;
	
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
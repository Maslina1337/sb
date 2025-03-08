#include "Effect.h"
#include "MarionetteEffectsComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

FEffectBase::FEffectBase(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
	bIsActive = false;
	Duration = 0;
}

template <typename T>
bool FEffect<T>::Activate(float Duration, T Params_)
{
	// Duration valid check.
	if (Duration < 0.f) return false;
	
	if (bIsActive || Params_.IsValid()) return false;

	Start(Duration, Params_); // Execute child addition.
		
	Params = Params_;
	ParamsFree = Params_;
	bIsActive = true;
	Owner->Effects->NotifyAboutActivation(this);
	
	return true;
}

template <typename T>
bool FEffect<T>::UpdateParamsFree(float const Duration, T const Params_)
{
	if (bIsActive && Params_.IsValid())
	{
		OnUpdateParamsFree(Duration, Params_); // Execute child addition.
		ParamsFree = Params_;
		return true;
	}
	return false;
}

void FEffectBase::Tick()
{
	Progress(); // Execute child addition for tick.
}

void FEffectBase::Deactivate()
{
	ForcedEnd(); // Execute child addition.
	bIsActive = false;
}
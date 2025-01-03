#include "EffectStatus.h"
#include "MarionetteEffectsComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

FEffectStatusBase::FEffectStatusBase(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
	bIsActive = false;
	Duration = 0;
}

// template <typename T>
// FEffectStatus<T>::FEffectStatus(AMarionette* OwnerClass) : FEffectStatusBase{OwnerClass}
// {
// 	Params = T();
// 	ParamsFree = T();
// }

template <typename T>
bool FEffectStatus<T>::Activate(float const Duration, T const Params_)
{
	// Duration valid check.
	if (Duration < 0) return false;
	
	if (!bIsActive && Params_.IsValid())
	{
		Start(Duration, Params_); // Execute child addition.
		
		Params = Params_;
		ParamsFree = Params_;
		bIsActive = true;

		Owner->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &End, Duration, false);
		
		return true;
	}
	return false;
}

template <typename T>
bool FEffectStatus<T>::UpdateParamsFree(float const Duration, T const Params_)
{
	if (bIsActive && Params_.IsValid())
	{
		OnUpdateParamsFree(Duration, Params_); // Execute child addition.
		ParamsFree = Params_;
		return true;
	}
	return false;
}

void FEffectStatusBase::Deactivate()
{
	ForcedEnd(); // Execute child addition.
	bIsActive = false;
}

bool FEffectStatusBase::IsActive() const
{
	return bIsActive;
}

// template <typename T>
// T FEffectStatus<T>::GetParams() const
// {
// 	return Params;
// }
//
// template <typename T>
// T FEffectStatus<T>::GetParamsFree() const
// {
// 	return ParamsFree;
// }

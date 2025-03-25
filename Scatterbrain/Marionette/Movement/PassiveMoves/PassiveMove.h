// Parent class for every active move.

#pragma once

#include "Scatterbrain/Marionette/Marionette.h"

class AMarionette;

class FPassiveMove {
public:
	
	explicit FPassiveMove();
	virtual ~FPassiveMove();

	virtual void SetOwner(AMarionette* Owner_);
	
	virtual void TickManual();
	
	bool IsActive() const { return bIsActive; }
	bool IsActivePastTick() const { return bIsActivePastTick; }

	// Called in constructor, so you should use IT as a constructor.
	// Also, can be called manually to reset variables to default values.
	virtual void Reset() = 0;

	void Activate() {
		if (bIsActive) return;
	
		bIsActive = true;
		bIsActivePastTick = false;
	}

	FString DebugName = "NoName";

protected:
	
	AMarionette* Owner; // Marionette instance.

	bool bIsActive;
	bool bIsActivePastTick;

	virtual void Progress() { UE_LOG(LogTemp, Error, TEXT("DEFAULT PROGRESS FUCK")) };
};
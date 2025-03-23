// Parent class for every active move.

#pragma once

#include "Scatterbrain/Marionette/Marionette.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PassiveMove.generated.h"

class AMarionette;

UCLASS(MinimalAPI)
class UPassiveMove : public UObject {
public:

	GENERATED_BODY()
	
	explicit UPassiveMove();
	virtual ~UPassiveMove() override;

	void SetOwner(AMarionette* Owner_);
	
	virtual void TickManual();
	
	bool IsActive() const { return bIsActive; }
	bool IsActivePastTick() const { return bIsActivePastTick; }

	void Activate() {
		if (bIsActive) return;
	
		bIsActive = true;
		bIsActivePastTick = false;
	}

	FString DebugName = "NoName";

protected:

	UPROPERTY()
	AMarionette* Owner; // Marionette instance.

	bool bIsActive;
	bool bIsActivePastTick;

	virtual void Progress() { UE_LOG(LogTemp, Error, TEXT("DEFAULT PROGRESS FUCK")) };
};
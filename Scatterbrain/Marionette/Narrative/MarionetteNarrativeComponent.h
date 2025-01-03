#pragma once

#include "Scatterbrain/Marionette/Types/ENarrativeRace.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionetteNarrativeComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionetteNarrativeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionetteNarrativeComponent();

	void SetOwner(AMarionette*);

private:

	UPROPERTY()
	AMarionette* Owner;

	//// INIT ON CREATION VARIABLES ////

	// The general name of the marionette, which is used to identify it in the system.
	// For example, to hang some effect on some marionette
	// (if, for some reason, there are several, then on all of them).
	UPROPERTY(EditAnywhere)
	FString SystemName;

	// The unique index of the marionette, which is used to identify it in the system.
	// For example, to hang some effect on some marionette.
	UPROPERTY(EditAnywhere)
	FString Index;

	// Marionette race, which may affect default settings.
	UPROPERTY(EditAnywhere)
	ENarrativeRace Race;

	//// UPDATE ANY TIME VARIABLES ////

	

public:
	////////////// FUNCTIONS //////////////

	

	////////////// VARIABLES //////////////

	

	////////////// CONSTANTS //////////////

	
};
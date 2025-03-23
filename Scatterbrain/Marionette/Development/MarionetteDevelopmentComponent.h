#pragma once

#include "Scatterbrain/Marionette/Types/UDA_Marionette.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionetteDevelopmentComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionetteDevelopmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionetteDevelopmentComponent();
	
	void SetOwner(AMarionette*);

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FSoftObjectPath DataAssetPath;

	// Dev method to automatically rewrite marionette data asset (Such as length's between bones).
	// !Call it with delay, when everything already loaded!
	UFUNCTION(BlueprintCallable)
	void RewriteDataAsset();

	void DrawTrace(const bool bIsHit, const FHitResult& HitResult,const FVector& TraceStart,const FVector& TraceEnd) const;
	void DrawTrace(const bool bIsHit, const FHitResult& HitResult,const FVector& TraceStart,const FVector& TraceEnd, float LifeTime) const;

private:
	UPROPERTY()
	AMarionette* Owner;

	void RewriteDataAssetRig(UDA_Marionette* DA) const;
};

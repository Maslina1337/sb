#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionetteSightComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionetteSightComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionetteSightComponent();

private:

	UPROPERTY()
	AMarionette* Owner;

public:

	////////////// FUNCTIONS //////////////

	UFUNCTION()
	void SetOwner(AMarionette* OwnerClass);
	
	UFUNCTION(BlueprintCallable)
	void SetPerson(bool bIsFirstPerson_);

	UFUNCTION(BlueprintCallable)
	void UpdateSight(const FVector2D XY);

	////////////// VARIABLES //////////////

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsFirstPerson;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsAbleToTogglePerson;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator SightRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpringArmDefaultLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSpringArmLengthChanging;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SightSensitivity;

	////////////// CONSTANTS //////////////
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SpringArmStep;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SpringArmMinLength;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SpringArmMaxLength;
};
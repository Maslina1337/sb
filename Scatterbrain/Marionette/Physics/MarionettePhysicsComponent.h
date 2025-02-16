#pragma once

#include "Scatterbrain/Marionette/Types/TwoLimbs.h"
#include "Scatterbrain/Marionette/Types/FSurfCheckReturn.h"
#include "../Types/EPhysStates.h"
#include "States.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MarionettePhysicsComponent.generated.h"

class AMarionette;

UCLASS(ClassGroup=(Marionette), meta=(BlueprintSpawnableComponent))
class SCATTERBRAIN_API UMarionettePhysicsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMarionettePhysicsComponent();

private:

	UPROPERTY()
	AMarionette* Owner;

	IStates* States;

public:
	////////////// FUNCTIONS //////////////

	UFUNCTION()
	void SetOwner(AMarionette* OwnerClass);
	
	// The purpose of this function is to apply physics to the doll until it touches a surface on which it feels stable.
	UFUNCTION(BlueprintCallable)
	void CalculateGravity();

	void ApplyAbsoluteMomentum(FVector);

	////////////// VARIABLES //////////////

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool PhysicsIgnore; // Physics will not be calculated and applied despite the all states.

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool GravitationalSlowdownIgnore; // The inertial velocity will not experience slowdown.
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool InertiaSlowdownIgnore; // The velocity of inertia will not experience slowdown.
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector GravitationalVelocity;

	/* Vector describing the displacement of the actor under the influence of gravity in this frame (Z only) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector GravitationalShift;

	/* Inertia vector uses X and Y axes. If there is Z it will be turned in to a gravitational velocity.
	 * You can use it as moment impulse. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ClampMin="0"))
	FVector InertiaVelocity;

	/* Marionette location shift at this moment. Only X and Y */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector InertiaShift;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHitResult ToesHit;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsToesHit;

	// Absolute Location relative to toes hit object. 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector HitObjectRelativeLocation;

	// Absolute Rotation relative to toes hit object.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator HitObjectRelativeRotation;

	/* The velocity value at the moment of landing. [m/s] */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector LandingImpactVelocity;

	/* Addition of the gravity shift vector and the inertial shift vector. [m] */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector FallShift;

	// Sum of gravitational and inertial velocity vectors. [m/s]
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector FallVelocity;

	/* Estimated distance to landing site. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FallDistanceRemaining;

	/* Estimated distance to landing site. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector GravitationalDirection;

	// Angle between surfing surface normal and horizontal plane.
	// In this case surfing surface is where pelvis surfing. [degrees]
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SurfAngle;

	/* Should component check if pelvis hit smth. (True when surfing) */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCheckPelvisHit;

	/* Ability to resist a quantity of acceleration while standing [m/s^2] */
	/* If the acceleration is higher the Marionette need to try to move legs to make more stable position. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool StableAccelerationDamping;

	/* Does Surface that Marionette standing on is able to move? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSurfaceActor;

	/* Reference to actor that Marionette standing on. [Before use check bIsSurfaceActor] */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* SurfaceActor;

	////////////// CONSTANTS //////////////

	/* The angle of the surf from the vertical. If the comparative angle is greater, then it is a surf. [degrees] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SurfingAngle;

	/* Describes the increase in velocity to the current gravitational velocity per second. [m/s^2] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float GravitationalAcceleration;

	/* [units (centimeters)] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TraceError;

	/* If there are less than this number of seconds left before landing, the doll begins to prepare for landing. [s] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TimeOfConcentrateFalling;

	/* The percentage value applied to the inertial velocity is designated air resistance. [m/s^2 (Negative affect)] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float InertiaSlowdown;

	/* The percentage value applied to the velocity of gravity represents air resistance. [m/s^2 (Negative affect)] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float GravitationalSlowdown;
	
	/* Real mass of the marionette body. [kg] */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Mass;
	
	// The slowdown (understand as friction) that would be experienced when hypothetically surfing on a horizontal surface.
	// (This value would be used with the cosine of SurfAngle) [m/s^2]
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float SurfSlowdown;

	// // Proportions of box collider of foots when stable. [units]
	// UPROPERTY(BlueprintReadOnly, EditAnywhere)
	// float FootStableColliderProportions;
	
	// Radius of spherical collider of both toes when falling. [units]
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ToesFallColliderRadius;
	
	// Proportions of pelvis collider traced on the current fall shift distance. To identify surf. [units]
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FVector PelvisSurfCollider;
};
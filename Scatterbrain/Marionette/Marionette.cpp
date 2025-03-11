// Fill out your copyright notice in the Description page of Project Settings.

// Components
#include "Marionette.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AMarionette::AMarionette()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Components

	Rig = CreateDefaultSubobject<UMarionetteRigComponent>("Rig");
	Rig->SetOwner(this);

	Physics = CreateDefaultSubobject<UMarionettePhysicsComponent>("Physics");
	Physics->SetOwner(this);

	Movement = CreateDefaultSubobject<UMarionetteMovementComponent>("Movement");
	Movement->SetOwner(this);

	Sight = CreateDefaultSubobject<UMarionetteSightComponent>("Sight");
	Sight->SetOwner(this);

	Narrative = CreateDefaultSubobject<UMarionetteNarrativeComponent>("Narrative");
	Narrative->SetOwner(this);

	Effects = CreateDefaultSubobject<UMarionetteEffectsComponent>("Effects");
	Effects->SetOwner(this);

	Abilities = CreateDefaultSubobject<UMarionetteAbilitiesComponent>("Abilities");
	Abilities->SetOwner(this);


	
	PseudoRoot = CreateDefaultSubobject<USceneComponent>("PseudoRoot");
	SetRootComponent(PseudoRoot);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent -> SetupAttachment(PseudoRoot);
	
	BodyColliderComponent = CreateDefaultSubobject<UCapsuleComponent>("BodyCollider");
	BodyColliderComponent -> SetupAttachment(SkeletalMeshComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent -> SetupAttachment(PseudoRoot);
	SpringArmComponent -> TargetArmLength = 300.0f;
	
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCameraComponent -> SetupAttachment(SpringArmComponent);
	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCameraComponent -> SetupAttachment(SkeletalMeshComponent);
}

// Called when the game starts or when spawned
void AMarionette::BeginPlay()
{
	Super::BeginPlay();

	// Initializing all Rig Constants.
	Rig->InitRigVariables();
}

// Called every frame ("frame" = "moment")
void AMarionette::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TickDeltaTime = DeltaTime;
	
	Rig->UpdateRigVariables();
	
	Sight->ApplySightRotation();
	
	Physics->TickPhysics();
	
	Movement->ChoosePassiveMove();
	Movement->ExecutePassiveMove();
	Movement->ExecuteActiveMoves();
	
}

// Called to bind functionality to input
void AMarionette::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


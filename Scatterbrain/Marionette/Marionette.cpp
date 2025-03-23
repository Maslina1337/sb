// Fill out your copyright notice in the Description page of Project Settings.

// Components
#include "Marionette.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

#include "Development/MarionetteDevelopmentComponent.h"
#include "Rig/MarionetteRigComponent.h"
#include "Physics/MarionettePhysicsComponent.h"
#include "Movement/MarionetteMovementComponent.h"
#include "Sight/MarionetteSightComponent.h"
#include "Narrative/MarionetteNarrativeComponent.h"
#include "Effects/MarionetteEffectsComponent.h"
#include "Abilities/MarionetteAbilitiesComponent.h"
#include "Movement/ActiveMoves/ActiveMove.h"
#include "Movement/PassiveMoves/PassiveMove.h"


// Sets default values
AMarionette::AMarionette()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// bUseControllerRotationYaw = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationYaw = false;

	// Components

	Development = CreateDefaultSubobject<UMarionetteDevelopmentComponent>("Development");
	Rig = CreateDefaultSubobject<UMarionetteRigComponent>("Rig");
	Physics = CreateDefaultSubobject<UMarionettePhysicsComponent>("Physics");
	Movement = CreateDefaultSubobject<UMarionetteMovementComponent>("Movement");
	Sight = CreateDefaultSubobject<UMarionetteSightComponent>("Sight");
	Narrative = CreateDefaultSubobject<UMarionetteNarrativeComponent>("Narrative");
	Effects = CreateDefaultSubobject<UMarionetteEffectsComponent>("Effects");
	Abilities = CreateDefaultSubobject<UMarionetteAbilitiesComponent>("Abilities");

	
	PseudoRoot = CreateDefaultSubobject<USceneComponent>("PseudoRoot");
	SetRootComponent(PseudoRoot);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(PseudoRoot);
	
	BodyColliderComponent = CreateDefaultSubobject<UCapsuleComponent>("BodyCollider");
	BodyColliderComponent->SetupAttachment(SkeletalMeshComponent);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(PseudoRoot);
	SpringArmComponent->TargetArmLength = Sight->SpringArmDefaultLength;
	SpringArmComponent->bUsePawnControlRotation = true;
	
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	ThirdPersonCameraComponent->SetupAttachment(SpringArmComponent);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCameraComponent->SetupAttachment(SkeletalMeshComponent);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMarionette::BeginPlay()
{
	Super::BeginPlay();

	// Setting Owner for components (do not move it to constructor)
	Development->SetOwner(this);
	Rig->SetOwner(this);
	Physics->SetOwner(this);
	Movement->SetOwner(this);
	Sight->SetOwner(this);
	Narrative->SetOwner(this);
	Effects->SetOwner(this);
	Abilities->SetOwner(this);
	
	Rig->LoadLengthData();

	// Setting up controller.
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	// Setting person.
	Sight->SetPerson(Sight->bIsFirstPerson);
}

void AMarionette::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TickDeltaTime = DeltaTime;

	Rig->UpdateBoneData();
	
	Physics->TickManual();
	
	Movement->ChoosePassiveMove();
	//Movement->ExecutePassiveMove();
	//Movement->ExecuteActiveMoves();

	

	// Debug display moves.
	if (IsValid(Movement->GetCurrentPassiveMove())) { UE_LOG(LogTemp, Error, TEXT("MOVE IS VALID")) }
	else { UE_LOG(LogTemp, Error, TEXT("MOVE ISN'T VALID")) }

	//if (Movement->GetCurrentPassiveMove()->DebugName) { UE_LOG(LogTemp, Error, TEXT("MOVE IS VALID")) }
	//else { UE_LOG(LogTemp, Error, TEXT("CANT'T ACCESS DEBUG NAME")) }
	
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Passive Move: ") + Movement->GetCurrentPassiveMove()->DebugName);

	// FString ActiveMovesDebugNames = TEXT("");
	// for (uint8 i = 0; i < Movement->GetCurrentActiveMoves().Num(); i++)
	// {
	// 	ActiveMovesDebugNames += Movement->GetCurrentActiveMoves()[i]->DebugName;
	// 	if (i+1 < Movement->GetCurrentActiveMoves().Num()) ActiveMovesDebugNames += TEXT(", ");
	// }
	// if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Active Move: ") + ActiveMovesDebugNames);
}

// Called to bind functionality to input
void AMarionette::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMarionette::LookActionHandler);
	}
}

void AMarionette::LookActionHandler(const FInputActionValue& Value)
{
	Sight->UpdateSight(Value.Get<FVector2D>());
};
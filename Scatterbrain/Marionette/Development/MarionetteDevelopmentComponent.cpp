#include "MarionetteDevelopmentComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

#include "Scatterbrain/Marionette/Types/UDA_Marionette.h"

#include "Scatterbrain/Marionette/Types/LeftRight.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"

#include "UObject/SavePackage.h"

// Sets default values for this component's properties
UMarionetteDevelopmentComponent::UMarionetteDevelopmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Owner = nullptr;
}

void UMarionetteDevelopmentComponent::SetOwner(AMarionette* OwnerClass)
{
	Owner = OwnerClass;
}

void UMarionetteDevelopmentComponent::RewriteDataAsset()
{
	FString DataAssetPathStr = DataAssetPath.GetAssetPathString();
	UDA_Marionette* MarionetteDataAsset = LoadObject<UDA_Marionette>(nullptr, *DataAssetPathStr);
	
	UPackage* Package = MarionetteDataAsset->GetPackage();
	const FString PackageName = Package->GetName();
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	if (!MarionetteDataAsset) { UE_LOG(LogTemp, Error, TEXT("Failed to load DataAsset!")); return;}
	
	// Data Changing.
	RewriteDataAssetRig(MarionetteDataAsset);
	
	// Saving the changes.

	// For some reason it does not mark package as dirty. But it still works after all...
	MarionetteDataAsset->MarkPackageDirty();

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Standalone;
	
	const bool bSaved = UPackage::SavePackage(Package, MarionetteDataAsset, *PackageFileName, SaveArgs);
	
	if (bSaved) {UE_LOG(LogTemp, Log, TEXT("DataAsset saved successfully!"));}
	else {UE_LOG(LogTemp, Error, TEXT("Failed to save DataAsset!"));}
}

void UMarionetteDevelopmentComponent::RewriteDataAssetRig(UDA_Marionette* DA) const
{
	using namespace LeftRight;
	
	UMarionetteRigComponent* R = Owner->Rig;

	// DEBUG
	FString temp = R->LegRootLocation[Left].ToString();
	UE_LOG(LogTemp, Error, TEXT("%s"), *temp);
	
	DA->RootKneeLength = (R->LegRootLocation[Left] - R->KneeLocation[Left]).Length();
	DA->KneeFootLength = (R->KneeLocation[Left] - R->FootLocation[Left]).Length();
	DA->FootToeLength = (R->FootLocation[Left] - R->ToeLocation[Left]).Length();

	DA->LegLength = DA->RootKneeLength + DA->KneeFootLength;
	DA->LegLengthTiptoes = DA->RootKneeLength + DA->KneeFootLength + DA->FootToeLength;

	DA->FootBoneGroundOffset = abs(R->RootLocation.Z - R->FootLocation[Left].Z);
	DA->ToeBoneGroundOffset = abs(R->RootLocation.Z - R->ToeLocation[Left].Z);
}

void UMarionetteDevelopmentComponent::DrawTrace(const bool bIsHit, const FHitResult& HitResult,const FVector& TraceStart,const FVector& TraceEnd) const
{
	DrawDebugLine(GetWorld(),TraceStart,TraceEnd,bIsHit ? FColor::Green : FColor::Red,false,-1.f,0,2.0f);

	if (bIsHit) DrawDebugPoint(GetWorld(),HitResult.Location,10.0f,FColor::Blue,false,-1.f);
}

void UMarionetteDevelopmentComponent::DrawTrace(const bool bIsHit, const FHitResult& HitResult,const FVector& TraceStart,const FVector& TraceEnd, float LifeTime) const
{
	DrawDebugLine(GetWorld(),TraceStart,TraceEnd,bIsHit ? FColor::Green : FColor::Red,false,LifeTime,0,2.0f);

	if (bIsHit) DrawDebugPoint(GetWorld(),HitResult.Location,10.0f,FColor::Blue,false,LifeTime);
}
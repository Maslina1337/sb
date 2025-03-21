#include "MarionetteDevelopmentComponent.h"
#include "Scatterbrain/Marionette/Marionette.h"

#include "Scatterbrain/Marionette/Types/UDA_Marionette.h"

#include "Scatterbrain/Marionette/Types/LeftRight.h"
#include "Scatterbrain/Marionette/Rig/MarionetteRigComponent.h"

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

	if (!MarionetteDataAsset) { UE_LOG(LogTemp, Error, TEXT("Failed to load DataAsset!")); return;}

	// Data Changing.
	RewriteDataAssetRig(MarionetteDataAsset);

	// Saving the changes.
	MarionetteDataAsset->MarkPackageDirty();
	FString PackageFileName = FPackageName::LongPackageNameToFilename(MarionetteDataAsset->GetOutermost()->GetName(),
		FPackageName::GetAssetPackageExtension());
		
	bool bSaved = UPackage::SavePackage(MarionetteDataAsset->GetOutermost(), MarionetteDataAsset,
		RF_Standalone, *PackageFileName);

	if (bSaved) {UE_LOG(LogTemp, Log, TEXT("DataAsset saved successfully!"));}
	else {UE_LOG(LogTemp, Error, TEXT("Failed to save DataAsset!"));}
}

void UMarionetteDevelopmentComponent::RewriteDataAssetRig(UDA_Marionette* DA) const
{
	using namespace LeftRight;
	
	UMarionetteRigComponent* R = Owner->Rig;
	
	DA->RootKneeLength = (R->LegRootLocation[Left] - R->KneeLocation[Left]).Length();
	DA->KneeFootLength = (R->KneeLocation[Left] - R->FootLocation[Left]).Length();
	DA->FootToeLength = (R->FootLocation[Left] - R->ToeLocation[Left]).Length();

	DA->LegLength = R->RootKneeLength + R->KneeFootLength;
	DA->LegLengthTiptoes = R->RootKneeLength + R->KneeFootLength + R->FootToeLength;

	DA->FootBoneGroundOffset = R->RootLocation.Z - R->FootLocation[Left].Z;
	DA->ToeBoneGroundOffset = R->RootLocation.Z - R->ToeLocation[Left].Z;
}
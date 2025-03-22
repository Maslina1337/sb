#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UDA_Marionette.generated.h"

UCLASS()
class SCATTERBRAIN_API UDA_Marionette : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float RootKneeLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float KneeFootLength;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float FootToeLength;
    
    /* RootKneeLength + KneeFootLength */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float LegLength;
    
    /* RootKneeLength + KneeFootLength + FootToeLength */
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float LegLengthTiptoes;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    float FootBoneGroundOffset;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    float ToeBoneGroundOffset;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    USkeletalMesh* Mesh;
};
#pragma once
#include "CoreMinimal.h"
#include "Types/Inv_GridTypes.h"
#include "StructUtils/InstancedStruct.h"
#include "Inv_ItemManifest.generated.h"

class UInv_InventoryItem;

USTRUCT(BlueprintType)
struct INVENTORYPLUGIN_API FInv_ItemManifest
{
    GENERATED_BODY()

public:

    UInv_InventoryItem* Manifest(UObject* NewOuter);
    EInv_ItemCategory GetItemCategory() const { return ItemCategory; };

private:

    UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
    EInv_ItemCategory ItemCategory = EInv_ItemCategory::None;
    
};


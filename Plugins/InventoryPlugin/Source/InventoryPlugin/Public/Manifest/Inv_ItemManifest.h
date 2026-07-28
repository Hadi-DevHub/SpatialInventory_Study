#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Types/Inv_GridTypes.h"
#include "StructUtils/InstancedStruct.h"
#include "Inv_ItemManifest.generated.h"

struct FInv_ItemFragment;
class UInv_InventoryItem;

USTRUCT(BlueprintType)
struct INVENTORYPLUGIN_API FInv_ItemManifest
{
    GENERATED_BODY()

public:

    UInv_InventoryItem* Manifest(UObject* NewOuter);
    EInv_ItemCategory GetItemCategory() const { return ItemCategory; };

    template<typename T> requires std::derived_from<T, FInv_ItemFragment>
    const T* GetFragmentOfTypeWithTag(const FGameplayTag& FragmentTag) const;
    
    template<typename T> requires std::derived_from<T, FInv_ItemFragment>
    const T* GetFragmentOfType() const;

    FGameplayTag GetItemType() const { return ItemType; };

private:

    UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
    EInv_ItemCategory ItemCategory = EInv_ItemCategory::None;

    UPROPERTY(EditAnywhere, Category = "INV PLUGIN", meta = (ExcludeBaseStruct))
    TArray<TInstancedStruct<FInv_ItemFragment>> Fragments;

    UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
    FGameplayTag ItemType = FGameplayTag();
    
};

template <typename T> 
 requires std::derived_from<T, FInv_ItemFragment>
 const T* FInv_ItemManifest::GetFragmentOfTypeWithTag(const FGameplayTag& FragmentTag) const
 {
     for (const TInstancedStruct<FInv_ItemFragment>& Fragment : Fragments)
     {
         if (const T* FragmentPtr = Fragment.GetPtr<T>())
         {
             if (!FragmentPtr->GetFragmentTag().MatchesTagExact(FragmentTag)) continue;
             return FragmentPtr;
         }
     }
     return nullptr;
 }
 
 template <typename T> 
 requires std::derived_from<T, FInv_ItemFragment>
 const T* FInv_ItemManifest::GetFragmentOfType() const
 {
     for (const TInstancedStruct<FInv_ItemFragment>& Fragment : Fragments)
     {
         if (const T* FragmentPtr = Fragment.GetPtr<T>())
         {
             return FragmentPtr;
         }
     }
     return nullptr;
 }

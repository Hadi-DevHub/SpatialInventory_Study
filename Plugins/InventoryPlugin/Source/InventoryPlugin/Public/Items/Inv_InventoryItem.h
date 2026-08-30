#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "UObject/Object.h"
#include "Manifest/Inv_ItemManifest.h"
#include "Inv_InventoryItem.generated.h"

UCLASS()
class INVENTORYPLUGIN_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool IsSupportedForNetworking() const override { return true; }

	void SetItemManifest(const FInv_ItemManifest& Manifest);
	void SetTotalStackCount(const int32 StackCount) { TotalStackCount = StackCount; };

	const FInv_ItemManifest& GetItemManifest() const { return ItemManifest.Get<FInv_ItemManifest>(); }
	const FInv_ItemManifest& GetItemManifestMutable() { return ItemManifest.GetMutable<FInv_ItemManifest>(); }
	int32 GetTotalStackCount() const { return TotalStackCount; }
	bool IsStackable() const;

private:

	UPROPERTY(VisibleAnywhere, Replicated, meta = (BaseStruct = "/Script/InventoryPlugin.Inv_ItemManifest"))
	FInstancedStruct ItemManifest;
	
	UPROPERTY(VisibleAnywhere, Replicated)
	int32 TotalStackCount{0};
};

template <typename FragmentType>
const FragmentType* GetFragment(const UInv_InventoryItem* Item, const FGameplayTag& FragmentTag)
{
	const FInv_ItemManifest& ItemManifest = Item->GetItemManifest();
	return ItemManifest.GetFragmentOfTypeWithTag<FragmentType>(FragmentTag);
}











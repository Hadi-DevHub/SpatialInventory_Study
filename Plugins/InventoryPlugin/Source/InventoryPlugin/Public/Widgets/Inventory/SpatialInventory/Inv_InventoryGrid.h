#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Fragments/Inv_ItemFragment.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

struct FInv_IconFragment;
struct FInv_GridFragment;
class UInv_SlottedItem;
class UInv_ItemComponent;
struct FInv_ItemManifest;
class UInv_InventoryComponent;
class UCanvasPanel;
class UInv_GridSlot;
class UImage;

UCLASS()
class INVENTORYPLUGIN_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	EInv_ItemCategory GetCategoryType() const { return ItemCategory; }
	
	void NativeOnInitialized() override;

	UFUNCTION()
	void AddItem(UInv_InventoryItem* Item);

	FInv_SlotAvailabilityResult HasRoomForItem(UInv_ItemComponent* InItemComponent);
	FInv_SlotAvailabilityResult HasRoomForItem(UInv_InventoryItem* InItem);
	
private:

	void AddItemToIndices(const FInv_SlotAvailabilityResult& Result, UInv_InventoryItem* NewItem);
	
	void AddItemAtIndex(UInv_InventoryItem* _Item, const int32 _Index, const bool _bStackable, const int32 _StackAmount);
	UInv_SlottedItem* CreateSlottedItem(UInv_InventoryItem* _Item,
		const FInv_GridFragment* _GridFragment,
		const FInv_IconFragment* _IconFragment,
		const int32 _Index,
		const bool _bStackable,
		const int32 StackAmount) const;

	void AddSlottedItemToCanvas(UInv_SlottedItem* SlottedItem, const FInv_GridFragment* _GridFragment, const int32 _Index);
	void UpdateGridSlots(UInv_InventoryItem* Item, const int32 Index, const bool bIsStackable, const int32 InStackAmount);
	FVector2D GetDrawSize(const FInv_GridFragment* _GridFragment) const;
	void SetSlottedItemImage(UInv_SlottedItem* _SlottedItem, const FInv_GridFragment* _GridFragment, const FInv_IconFragment* _IconFragment) const;
	FInv_SlotAvailabilityResult HasRoomForItem(const FInv_ItemManifest& InItemManifest);
	bool IsIndexClaimed(const TSet<int>& CheckedIndices, const int32 Index) const;
	bool HasRoomAtIndex(UInv_GridSlot* GridSlot, const FIntPoint& GridDimensions);
	FIntPoint GetItemDimensions(const FInv_ItemManifest& ItemManifest);

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;

	void ConstructGrid();

	UPROPERTY()
	TArray<UInv_GridSlot*> GridSlots;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	TSubclassOf<UInv_GridSlot> GridSlotClass;

	TMap<int32, UInv_SlottedItem*> SlottedItems;
	
	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	TSubclassOf<UInv_SlottedItem> SlottedItemClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "INV PLUGIN")
	EInv_ItemCategory ItemCategory = EInv_ItemCategory::None;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	int32 Rows;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	int32 Columns;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	float TileSize;

	bool MatchesCategory(const UInv_InventoryItem* Item) const;

};

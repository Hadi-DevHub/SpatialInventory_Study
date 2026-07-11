#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/Inv_InventoryItem.h"
#include "Inv_SlottedItem.generated.h"

class UTextBlock;
class UInv_InventoryItem;
class UImage;

UCLASS()
class INVENTORYPLUGIN_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetSlottedItemBrush(const FSlateBrush& _Brush) const;
	void SetSlottedItemIndex(int32 _index) { Index = _index; };
	void SetSlottedItemDimensions(FVector2D _GridDimensions) { GridDimensions = _GridDimensions; };
	void SetSlottedItemInventoryItemData(UInv_InventoryItem* _itemData) { InventoryItemData = _itemData; };
	void SetIsStackable(bool _bStackable) { bStackable = _bStackable; };
	void UpdateStackCount(int32 StackCount) const;
	
	UImage* GetSlottedItemIcon() const { return IMG_ItemIcon; };
	int32 GetSlottedItemIndex() const { return Index; };
	FVector2D GetSlottedItemDimensions() const { return GridDimensions; };
	UInv_InventoryItem* GetSlottedItemInventoryData() const;
	bool GetIsStackable() const { return bStackable; };

	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> IMG_ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TB_StackCount;

	int32 Index;
	FVector2D GridDimensions;

	TWeakObjectPtr<UInv_InventoryItem> InventoryItemData;

	bool bStackable{false};

	
};

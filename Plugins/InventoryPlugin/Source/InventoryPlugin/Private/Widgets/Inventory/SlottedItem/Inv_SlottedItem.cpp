#include "Widgets/Inventory/SlottedItem/Inv_SlottedItem.h"

#include "Components/Image.h"

void UInv_SlottedItem::SetSlottedItemBrush(const FSlateBrush& _Brush) const
{
	IMG_ItemIcon->SetBrush(_Brush);
}

UInv_InventoryItem* UInv_SlottedItem::GetSlottedItemInventoryData() const
{
	return InventoryItemData.Get();
}

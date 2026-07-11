#include "Widgets/Inventory/SlottedItem/Inv_SlottedItem.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UInv_SlottedItem::SetSlottedItemBrush(const FSlateBrush& _Brush) const
{
	IMG_ItemIcon->SetBrush(_Brush);
}

void UInv_SlottedItem::UpdateStackCount(int32 StackCount) const
{
	if (StackCount > 0)
	{
		TB_StackCount->SetVisibility(ESlateVisibility::Visible);
		TB_StackCount->SetText(FText::AsNumber(StackCount));
	}
	else
	{
		TB_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

UInv_InventoryItem* UInv_SlottedItem::GetSlottedItemInventoryData() const
{
	return InventoryItemData.Get();
}

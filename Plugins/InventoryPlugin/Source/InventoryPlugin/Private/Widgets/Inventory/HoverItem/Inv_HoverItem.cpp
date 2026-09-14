#include "Widgets/Inventory/HoverItem/Inv_HoverItem.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Inv_InventoryItem.h"

void UInv_HoverItem::SetImageIcon(const FSlateBrush& Brush) const
{
	Image_Icon->SetBrush(Brush);
}

void UInv_HoverItem::UpdateStackCount(int32 Count) const
{
	if (Count > 0)
	{
		TB_StackCount->SetText(FText::AsNumber(Count));
		TB_StackCount->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TB_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
}

FGameplayTag UInv_HoverItem::GetItemType() const
{
	if (InventoryItem.IsValid())
	{
		return InventoryItem->GetItemManifest().GetItemType();
	}

	return FGameplayTag();
}

void UInv_HoverItem::SetIsStackable(bool bStacks)
{
	bStackable = bStacks;
	if (!bStackable)
	{
		TB_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		TB_StackCount->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInv_HoverItem::SetInventoryItem(UInv_InventoryItem* Item)
{
	InventoryItem = Item;
}

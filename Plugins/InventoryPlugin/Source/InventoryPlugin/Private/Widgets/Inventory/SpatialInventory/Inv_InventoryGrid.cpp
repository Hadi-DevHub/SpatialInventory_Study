#include "Widgets/Inventory/SpatialInventory/Inv_InventoryGrid.h"
#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Fragments/Inv_FragmentTag.h"
#include "Fragments/Inv_ItemFragment.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/InventoryStatics/UInv_InventoryStatics.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Utils/WidgetUtils.h"
#include "Widgets/Inventory/SlottedItem/Inv_SlottedItem.h"
#include "InventoryManagement/InventoryStatics/UInv_InventoryStatics.h"

void UInv_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ConstructGrid();
	InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	InventoryComponent->OnItemAdded.AddDynamic(this, &ThisClass::AddItem);
}

void UInv_InventoryGrid::AddItem(UInv_InventoryItem* Item)
{
	if (!MatchesCategory(Item)) return;

	FInv_SlotAvailabilityResult Result = HasRoomForItem(Item);
	AddItemToIndices(Result, Item);
}

FInv_SlotAvailabilityResult UInv_InventoryGrid::HasRoomForItem(UInv_ItemComponent* InItemComponent)
{
	return HasRoomForItem(InItemComponent->GetItemManifest());
}

FInv_SlotAvailabilityResult UInv_InventoryGrid::HasRoomForItem(UInv_InventoryItem* InItem)
{
	return HasRoomForItem(InItem->GetItemManifest());
}

void UInv_InventoryGrid::AddItemToIndices(const FInv_SlotAvailabilityResult& Result, UInv_InventoryItem* NewItem)
{
	for (const FInv_SlotAvailability& Availability : Result.SlotAvailabilities)
	{
		AddItemAtIndex(NewItem, Availability.Index, Result.bStackable, Availability.AmountToFill);
		UpdateGridSlots(NewItem, Availability.Index, Result.bStackable, Availability.AmountToFill);
	}
}

void UInv_InventoryGrid::AddItemAtIndex(UInv_InventoryItem* _Item, const int32 _Index, const bool _bStackable,
	const int32 _StackAmount)
{
	const FInv_GridFragment* GridFragment = GetFragment<FInv_GridFragment>(_Item, FragmentTags::GridFragment);
	const FInv_IconFragment* IconFragment = GetFragment<FInv_IconFragment>(_Item, FragmentTags::IconFragment);
	if (!GridFragment || !IconFragment) return;

	UInv_SlottedItem* SlottedItem = CreateSlottedItem(_Item, GridFragment, IconFragment, _Index, _bStackable, _StackAmount);
	AddSlottedItemToCanvas(SlottedItem, GridFragment, _Index);
	SlottedItems.Add(_Index, SlottedItem);
}

UInv_SlottedItem* UInv_InventoryGrid::CreateSlottedItem(UInv_InventoryItem* _Item, const FInv_GridFragment* _GridFragment,
	const FInv_IconFragment* _IconFragment, const int32 _Index, const bool _bStackable, const int32 _StackAmount) const
{
	UInv_SlottedItem* SlottedItem = CreateWidget<UInv_SlottedItem>(GetOwningPlayer(), SlottedItemClass);
	SlottedItem->SetSlottedItemIndex(_Index);
	SlottedItem->SetSlottedItemInventoryItemData(_Item);
	SetSlottedItemImage(SlottedItem, _GridFragment, _IconFragment);
	SlottedItem->SetIsStackable(_bStackable);
	const int32 StackAmount = _bStackable ? _StackAmount : 0;
	SlottedItem->UpdateStackCount(_StackAmount);
	
	return SlottedItem;
}

void UInv_InventoryGrid::AddSlottedItemToCanvas(UInv_SlottedItem* SlottedItem, const FInv_GridFragment* _GridFragment,
	const int32 _Index)
{
	CanvasPanel->AddChild(SlottedItem);
	UCanvasPanelSlot* CPS = CanvasPanel->AddChildToCanvas(SlottedItem);
	CPS->SetSize(GetDrawSize(_GridFragment));
	const FVector2D DrawPos = UWidgetUtils::GetPosFromIndex(_Index, Columns) * TileSize;
	const FVector2D DrawPosWithPadding = DrawPos + FVector2D(_GridFragment->GetGridPadding());
	CPS->SetPosition(DrawPosWithPadding);
}

void UInv_InventoryGrid::UpdateGridSlots(UInv_InventoryItem* Item, const int32 Index, const bool bIsStackable, const int32 InStackAmount)
{
	if (bIsStackable)
	{
		GridSlots[Index]->SetStackAmount(InStackAmount);
	}
	
	const FInv_GridFragment* GridFragment = GetFragment<FInv_GridFragment>(Item, FragmentTags::GridFragment);
	FIntPoint ItemDimensions = GridFragment ? GridFragment->GetGridSize() : FIntPoint(1, 1);
	
	UInv_InventoryStatics::ForEach2D(Index, Columns, ItemDimensions, GridSlots, [&](UInv_GridSlot* GridSlot)
	{
		GridSlot->SetSlotToOccupied();
		GridSlot->SetInventoryItem(Item);
		GridSlot->SetIsAvailable(bIsStackable);
		GridSlot->SetUpperLeftIndex(Index);
	});
}

FVector2D UInv_InventoryGrid::GetDrawSize(const FInv_GridFragment* _GridFragment) const 
{
	const float IconTileWidth = TileSize - _GridFragment->GetGridPadding();
	return _GridFragment->GetGridSize() * IconTileWidth;
}

void UInv_InventoryGrid::SetSlottedItemImage(UInv_SlottedItem* _SlottedItem, const FInv_GridFragment* _GridFragment,
	const FInv_IconFragment* _IconFragment) const 
{
	FSlateBrush Brush;
	Brush.SetResourceObject(_IconFragment->GetIcon());
	Brush.DrawAs = ESlateBrushDrawType::Image;
	Brush.ImageSize = GetDrawSize(_GridFragment);
	_SlottedItem->SetSlottedItemBrush(Brush);
}

FInv_SlotAvailabilityResult UInv_InventoryGrid::HasRoomForItem(const FInv_ItemManifest& InItemManifest)
{
	FInv_SlotAvailabilityResult Result;
	
	const FInv_StackableFragment* StackableFragment = InItemManifest.GetFragmentOfType<FInv_StackableFragment>();
	Result.bStackable = StackableFragment != nullptr;
	// Determine how many stacks to add.
	// For each Grid Slot:
		// If we don't have anymore to fill, break out of the loop early.
		// Is this index claimed yet?
		// Can the item fit here? (i.e. is it out of grid bounds?)
		// Is there room at this index? (i.e. are there other items in the way?)
		// Check any other important conditions - ForEach2D over a 2D range
			// Index claimed?
			// Has valid item?
			// Is this item the same type as the item we're trying to add?
			// If so, is this a stackable item?
			// If stackable, is this slot at the max stack size already?
		// How much to fill?
		// Update the amount left to fill
	// How much is the Remainder?
	
	return Result;
}

void UInv_InventoryGrid::ConstructGrid()
{
	GridSlots.Reserve(Rows * Columns);

	for (int32 i = 0; i < Rows; ++i)
	{
		for (int32 j = 0; j < Columns; ++j)
		{
			UInv_GridSlot* GridSlot = CreateWidget<UInv_GridSlot>(this, GridSlotClass);
			CanvasPanel->AddChild(GridSlot);

			FIntPoint TilePosition(j, i);
			int32 TileIndex = UWidgetUtils::GetIndexFromPosition(TilePosition, Columns);
			GridSlot->SetTileIndex(TileIndex);

			UCanvasPanelSlot* GridCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			GridCPS->SetSize(FVector2D(TileSize));
			GridCPS->SetPosition(TilePosition * TileSize);

			GridSlots.Add(GridSlot);
		}
	}
}

bool UInv_InventoryGrid::MatchesCategory(const UInv_InventoryItem* Item) const
{
	return Item->GetItemManifest().GetItemCategory() == ItemCategory;
}

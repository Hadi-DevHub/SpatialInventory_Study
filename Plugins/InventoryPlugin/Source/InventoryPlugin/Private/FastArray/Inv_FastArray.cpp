#include "FastArray/Inv_FastArray.h"

TArray<UInv_InventoryItem*> FInv_InventoryFastArray::GetAllItems() const
{
	return TArray<UInv_InventoryItem*>();
}

void FInv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
}

void FInv_InventoryFastArray::PostReplicatedRemove(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
}

void FInv_InventoryFastArray::AddEntry(UInv_InventoryItem* InEntry)
{
}

void FInv_InventoryFastArray::AddEntry(UInv_ItemComponent* InItemComponent)
{
}

void FInv_InventoryFastArray::RemoveEntry(UInv_InventoryItem* InEntry)
{
}
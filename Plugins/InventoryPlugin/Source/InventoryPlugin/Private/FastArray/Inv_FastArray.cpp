#include "FastArray/Inv_FastArray.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"

TArray<UInv_InventoryItem*> FInv_InventoryFastArray::GetAllItems() const
{
	TArray<UInv_InventoryItem*> Result;
	Result.Reserve(Entries.Num());
	for (auto Entry : Entries)
	{
		if (!IsValid(Entry.Item)) continue;
		Result.Add(Entry.Item);
	}
	return Result;
}

void FInv_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;

	for (int32 Index : RemovedIndices)
	{
		IC->OnItemRemoved.Broadcast(Entries[Index].Item);
	}
}

void FInv_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;

	for (int32 Index : AddedIndices)
	{
		IC->OnItemAdded.Broadcast(Entries[Index].Item);
	}
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_InventoryItem* InEntry)
{
	check(OwnerComponent);
	AActor* Actor = OwnerComponent->GetOwner();
	check(Actor->HasAuthority());

	FInv_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = InEntry;

	MarkItemDirty(NewEntry);

	return InEntry;
}

UInv_InventoryItem* FInv_InventoryFastArray::AddEntry(UInv_ItemComponent* InItemComponent)
{
	check(OwnerComponent);
	AActor* OwnerActor = OwnerComponent->GetOwner();
	check(OwnerActor->HasAuthority());

	UInv_InventoryComponent* IC = Cast<UInv_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return nullptr;

	FInv_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = InItemComponent->GetItemManifest().Manifest(OwnerActor);

	IC->AddRepSubObj(NewEntry.Item);
	MarkItemDirty(NewEntry);

	return NewEntry.Item;
}

void FInv_InventoryFastArray::RemoveEntry(UInv_InventoryItem* InEntry)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FInv_InventoryEntry& Entry = *EntryIt;
		if (Entry.Item == InEntry)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}

UInv_InventoryItem* FInv_InventoryFastArray::FindFirstItemByType(const FGameplayTag& ItemType)
{
	auto FoundItem =  Entries.FindByPredicate([ItemType](const FInv_InventoryEntry& Entry)
	{
		return IsValid(Entry.Item) && Entry.Item->GetItemManifest().GetItemType().MatchesTagExact(ItemType);
	});

	return FoundItem ? FoundItem->Item : nullptr;
}

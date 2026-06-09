#pragma once
#include "Net/Serialization/FastArraySerializer.h"
#include "Inv_FastArray.generated.h"

class UInv_ItemComponent;
class UInv_InventoryItem;
class UInv_InventoryComponent;

USTRUCT(BlueprintType)
struct FInv_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

public:

	FInv_InventoryEntry(){};
	
private:
	friend struct FInv_InventoryFastArray;
	friend UInv_InventoryComponent;
	
	TObjectPtr<UInv_InventoryItem> Item;

};

USTRUCT(BlueprintType)
struct FInv_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()

public:

	FInv_InventoryFastArray(){}
	FInv_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent){}

	TArray<UInv_InventoryItem*> GetAllItems() const;

	/** Fast Array Serializer Contract */
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedRemove(const TArrayView<int32> AddedIndices, int32 FinalSize);
	/** End of Fast Array Serializer Contract */

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FInv_InventoryEntry, FInv_InventoryFastArray>(Entries, DeltaParams, *this);
	}

	void AddEntry(UInv_InventoryItem* InEntry);
	void AddEntry(UInv_ItemComponent* InItemComponent);
	void RemoveEntry(UInv_InventoryItem* InEntry);
	
private:
	friend UInv_InventoryComponent;

	UPROPERTY()
	TArray<FInv_InventoryEntry> Entries;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;

};



template<>
struct TStructOpsTypeTraits<FInv_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FInv_InventoryFastArray>
{
	enum { WithNetDeltaSerializer = true };
};

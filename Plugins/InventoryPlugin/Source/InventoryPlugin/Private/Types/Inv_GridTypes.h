#pragma once

#include "Inv_GridTypes.generated.h"

class UInv_InventoryItem;

UENUM(BlueprintType)
enum class EInv_ItemCategory : uint8
{
	Equippable,
	Consumable,
	Craftable,
	None
};

USTRUCT(BlueprintType)
struct FInv_SlotAvailability
{
	GENERATED_BODY()

	FInv_SlotAvailability(){};
	FInv_SlotAvailability(int32 InIndex, int32 InAmountToFill, bool bInItemAtIndex) : Index(InIndex), AmountToFill(InAmountToFill), bItemAtIndex(bInItemAtIndex) {};

	int32 Index{INDEX_NONE};
	int32 AmountToFill{0};
	bool bItemAtIndex{false};
};

USTRUCT(BlueprintType)
struct FInv_SlotAvailabilityResult
{
	GENERATED_BODY()

	FInv_SlotAvailabilityResult(){};

	TWeakObjectPtr<UInv_InventoryItem> Item;
	int32 TotalRoomToFill{0};
	int32 Remainder{0};
	bool bStackable {false};
	TArray<FInv_SlotAvailability> SlotAvailabilities;
};

UENUM(BlueprintType)
enum class EInv_TileQuadrant : uint8
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	None
};

USTRUCT(BlueprintType)
struct FInv_TileParameters
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "INV | PLUGIN")
	FIntPoint TileCoordinates{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "INV | PLUGIN")
	int32 TileIndex{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "INV | PLUGIN")
	EInv_TileQuadrant TileQuadrant{EInv_TileQuadrant::None};
	
};
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/Inv_InventoryItem.h"
#include "Inv_GridSlot.generated.h"

UENUM(BlueprintType)
enum class EGridSlotState : uint8
{
	GSS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	GSS_Occupied UMETA(DisplayName = "Occupied"),
	GSS_Active UMETA(DisplayName = "Active"),
	GSS_Disabled UMETA(DisplayName = "Disabled")
};

class UImage;

UCLASS()
class INVENTORYPLUGIN_API UInv_GridSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetSlotToUnoccupied();;
	void SetSlotToOccupied();
	void SetSlotToActive();
	void SetSlotToDisabled();

	// SETTERS AND GETTERS
	
	int32 GetTileIndex() const { return TileIndex; };
	int32 GetStackAmount() const { return StackAmount; };
	int32 GetUpperLeftIndex() const { return UpperLeftIndex; };
	bool GetIsAvailable() const { return bSlotAvailable; };
	TWeakObjectPtr<UInv_InventoryItem> GetInventoryItem() const { return InventoryItem; };

	void SetTileIndex(int32 InTileIndex) { TileIndex = InTileIndex; }
	void SetStackAmount(int32 InStackAmount) { StackAmount = InStackAmount; }
	void SetUpperLeftIndex(int32 InUpperLeftIndex) { UpperLeftIndex = InUpperLeftIndex; }
	void SetIsAvailable(bool bAvailable) { bSlotAvailable = bAvailable; }
	void SetInventoryItem(UInv_InventoryItem* InInventoryItem) {InventoryItem = InInventoryItem; };

	// SETTERS AND GETTERS

private:
	UPROPERTY(EditAnywhere, Category = "INV PLUGIN", Meta = (BindWidget))
	TObjectPtr<UImage> IMG_GridSlot;

	int32 TileIndex;
	int32 StackAmount;
	int32 UpperLeftIndex{INDEX_NONE};
	bool bSlotAvailable = true;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;

	UPROPERTY(VisibleAnywhere, Category = "INV PLUGIN")
	EGridSlotState SlotState = EGridSlotState::GSS_Unoccupied;

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	FSlateBrush Unoccupied_Brush;

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	FSlateBrush Occupied_Brush;
	
	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	FSlateBrush Active_Brush;

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	FSlateBrush Disabled_Brush;
};


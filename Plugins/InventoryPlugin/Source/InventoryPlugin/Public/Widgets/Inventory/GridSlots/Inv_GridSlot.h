#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	int32 GetTileIndex() const { return TileIndex; };
	void SetTileIndex(int32 InTileIndex) { TileIndex = InTileIndex; };


	void SetSlotToUnoccupied();
	void SetSlotToOccupied();
	void SetSlotToActive();
	void SetSlotToDisabled();

private:
	UPROPERTY(EditAnywhere, Category = "INV PLUGIN", Meta = (BindWidget))
	TObjectPtr<UImage> IMG_GridSlot;

	int32 TileIndex;

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


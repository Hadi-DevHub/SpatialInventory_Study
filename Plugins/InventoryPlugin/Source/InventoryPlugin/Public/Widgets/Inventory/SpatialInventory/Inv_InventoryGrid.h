#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"
#include "Inv_InventoryGrid.generated.h"

class UCanvasPanel;
class UInv_GridSlot;
class UImage;

UCLASS()
class INVENTORYPLUGIN_API UInv_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	EInv_ItemCategory GetCategoryType() const { return ItemCategory; }
	
	void NativeOnInitialized() override;
	
private:

	void ConstructGrid();

	UPROPERTY()
	TArray<UInv_GridSlot*> GridSlots;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	TSubclassOf<UInv_GridSlot> GridSlotClass;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "INV PLUGIN")
	EInv_ItemCategory ItemCategory = EInv_ItemCategory::None;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	int32 Rows;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	int32 Columns;

	UPROPERTY(EditAnywhere,Category = "INV PLUGIN")
	float TileSize;

};

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HoverItem.generated.h"

class UInv_InventoryItem;
class UTextBlock;
class UImage;

UCLASS()
class INVENTORYPLUGIN_API UInv_HoverItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetImageIcon(const FSlateBrush& Brush) const;
	void UpdateStackCount(int32 Count) const;

	FGameplayTag GetItemType() const;
	int32 GetStackCount() const { return StackCount; }
	bool GetIsStackable() const { return bStackable; }
	UInv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	int32 GetPreviousGridIndex() const { return PreviousGridIndex; }
	FIntPoint GetGridDimensions() const { return GridDimensions; }

	void SetGridDimension(FIntPoint Dimensions) { GridDimensions = Dimensions; }
	void SetPreviousGridIndex(int32 Index) { PreviousGridIndex = Index; }
	void SetIsStackable(bool bStacks);
	void SetInventoryItem(UInv_InventoryItem* Item);
	
	
protected:

private:

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Icon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_StackCount;

	int32 PreviousGridIndex {0};
	FIntPoint GridDimensions {0,0};
	int32 StackCount {0};
	bool bStackable {false};
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
};

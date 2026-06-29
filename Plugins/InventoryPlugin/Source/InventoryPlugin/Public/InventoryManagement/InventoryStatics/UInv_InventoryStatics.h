#pragma once

#include "Types/Inv_GridTypes.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Utils/WidgetUtils.h"
#include "UInv_InventoryStatics.generated.h"

class UWidgetUtils;
class UInv_ItemComponent;
class UInv_InventoryComponent;

UCLASS()
class INVENTORYPLUGIN_API UInv_InventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "INV PLUGIN | STATICS", BlueprintAuthorityOnly)
	static UInv_InventoryComponent* GetInventoryComponent(APlayerController* InPlayerController);

	static EInv_ItemCategory GetItemCategoryFromItemComp(UInv_ItemComponent* InItemComp);

	template <typename T, typename FuncT>
	static void ForEach2D (const int32& StartingIndex, const int32 GridColumns, const FIntPoint& ItemDimensions, TArray<T> InArray, const FuncT& Function);

};

template <typename T, typename FuncT>
void UInv_InventoryStatics::ForEach2D(const int32& StartingIndex, const int32 GridColumns, const FIntPoint& ItemDimensions,
	TArray<T> InArray, const FuncT& Function)
{
	for (int32 i = 0; i < ItemDimensions.Y; ++i)
	{
		for (int32 j = 0; j < ItemDimensions.X; ++j)
		{
			FIntPoint Coordinates = UWidgetUtils::GetPosFromIndex(StartingIndex, GridColumns) + FIntPoint(i, j);
			int32 TileIndex = UWidgetUtils::GetIndexFromPosition(Coordinates, GridColumns);
			if (InArray.IsValidIndex(TileIndex))
			{
				Function(InArray[TileIndex]);
			}
		}
	}
}

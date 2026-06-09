#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_GridSlot.generated.h"

class UImage;

UCLASS()
class INVENTORYPLUGIN_API UInv_GridSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	int32 GetTileIndex() const { return TileIndex; };
	void SetTileIndex(int32 InTileIndex) { TileIndex = InTileIndex; };

private:
	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	TObjectPtr<UImage> Image_GridSlot;

	int32 TileIndex;
};

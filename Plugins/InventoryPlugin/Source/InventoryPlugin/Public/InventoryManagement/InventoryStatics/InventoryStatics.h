#pragma once

#include "Types/Inv_GridTypes.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventoryStatics.generated.h"

class UInv_ItemComponent;
class UInv_InventoryComponent;

UCLASS()
class INVENTORYPLUGIN_API UInventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "INV PLUGIN | STATICS", BlueprintAuthorityOnly)
	static UInv_InventoryComponent* GetInventoryComponent(APlayerController* InPlayerController);

	static EInv_ItemCategory GetItemCategoryFromItemComp(UInv_ItemComponent* InItemComp);

};

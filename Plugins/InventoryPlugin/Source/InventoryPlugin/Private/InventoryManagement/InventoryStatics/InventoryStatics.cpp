#include "InventoryManagement/InventoryStatics/InventoryStatics.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Types/Inv_GridTypes.h"

UInv_InventoryComponent* UInventoryStatics::GetInventoryComponent(APlayerController* InPlayerController)
{
	if (!IsValid(InPlayerController)) return nullptr;

	UInv_InventoryComponent* InventoryComponent = InPlayerController->FindComponentByClass<UInv_InventoryComponent>();
	return InventoryComponent;
}

EInv_ItemCategory UInventoryStatics::GetItemCategoryFromItemComp(UInv_ItemComponent* InItemComp)
{
	if (!IsValid(InItemComp)) return EInv_ItemCategory::None;

	return InItemComp->GetItemManifest().GetItemCategory();
}

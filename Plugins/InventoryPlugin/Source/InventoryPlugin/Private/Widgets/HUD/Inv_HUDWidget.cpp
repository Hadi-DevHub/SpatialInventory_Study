#include "Widgets/HUD/Inv_HUDWidget.h"

#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "InventoryManagement/InventoryStatics/UInv_InventoryStatics.h"
#include "Widgets/HUD/Inv_InfoMessage.h"

void UInv_HUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UInv_InventoryComponent* InventoryComponent = UInv_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	if (InventoryComponent && GetOwningPlayer()->HasAuthority())
	{
		InventoryComponent->OnNoRoomInInventory.AddDynamic(this, &UInv_HUDWidget::OnNoRoom);
	}
}

void UInv_HUDWidget::OnNoRoom()
{
	if (!IsValid(WBP_InfoMessage)) return;
	WBP_InfoMessage->SetAndShowMessage(FText::FromString(TEXT("No Room In Inventory")));
}

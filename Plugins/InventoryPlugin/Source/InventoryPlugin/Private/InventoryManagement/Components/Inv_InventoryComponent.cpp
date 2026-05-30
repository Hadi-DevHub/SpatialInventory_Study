#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Widgets/Inventory/InventoryBase/Inv_UW_InventoryBase.h"
#include "Blueprint/UserWidget.h"

UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ConstructInventory();
}

void UInv_InventoryComponent::ConstructInventory()
{
	OwnerController = Cast<APlayerController>(GetOwner());
	checkf(OwnerController.IsValid(), TEXT("Inventory Component must have a Player Controller as it's owner."));
	if (!OwnerController->IsLocalController()) return;

	InventoryWidget = CreateWidget<UInv_UW_InventoryBase>(OwnerController.Get(), InventoryWidgetClass);
	InventoryWidget->AddToViewport();
}

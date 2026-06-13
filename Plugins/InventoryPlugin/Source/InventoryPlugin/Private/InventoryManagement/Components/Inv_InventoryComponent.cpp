#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Widgets/Inventory/InventoryBase/Inv_UW_InventoryBase.h"
#include "Blueprint/UserWidget.h"
#include "Types/Inv_GridTypes.h"

UInv_InventoryComponent::UInv_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInv_InventoryComponent::ToggleInventoryMenu()
{
	if (!bInventoryMenuOpen)
	{
		OpenInventoryMenu();
	}
	else
	{
		CloseInventoryMenu();
	}
}

void UInv_InventoryComponent::TryAddItem(UInv_ItemComponent* InItemComponent)
{
	FInv_SlotAvailabilityResult Result = InventoryWidget->HasRoomForItem(InItemComponent);

	if (Result.TotalRoomToFill == 0)
	{
		OnNoRoomInInventory.Broadcast();
	}
}

void UInv_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ConstructInventory();
	CloseInventoryMenu();
}

void UInv_InventoryComponent::OpenInventoryMenu()
{
	bInventoryMenuOpen = true;

	if (!IsValid(InventoryWidget)) return;
	InventoryWidget->SetVisibility(ESlateVisibility::Visible);

	if (!OwnerController.IsValid()) return;
	FInputModeGameAndUI InputModeGAmeAndUI;
	OwnerController->SetInputMode(InputModeGAmeAndUI);
	OwnerController->SetShowMouseCursor(true);
}

void UInv_InventoryComponent::CloseInventoryMenu()
{
	bInventoryMenuOpen = false;

	if (!IsValid(InventoryWidget)) return;
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

	if (!OwnerController.IsValid()) return;
	FInputModeGameOnly InputModeGame;
	OwnerController->SetInputMode(InputModeGame);
	OwnerController->SetShowMouseCursor(false);
}

void UInv_InventoryComponent::ConstructInventory()
{
	OwnerController = Cast<APlayerController>(GetOwner());
	checkf(OwnerController.IsValid(), TEXT("Inventory Component must have a Player Controller as it's owner."));
	if (!OwnerController->IsLocalController()) return;

	InventoryWidget = CreateWidget<UInv_UW_InventoryBase>(OwnerController.Get(), InventoryWidgetClass);
	InventoryWidget->AddToViewport();
}

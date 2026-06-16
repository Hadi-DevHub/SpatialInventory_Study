#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Widgets/Inventory/InventoryBase/Inv_UW_InventoryBase.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
#include "Types/Inv_GridTypes.h"

UInv_InventoryComponent::UInv_InventoryComponent() : InventoryList(this)
{
	PrimaryComponentTick.bCanEverTick = false;

	bReplicateUsingRegisteredSubObjectList = true;
	SetIsReplicatedByDefault(true);
	bInventoryMenuOpen = false;
}

void UInv_InventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, InventoryList);
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

void UInv_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && IsValid(SubObj))
	{
		AddReplicatedSubObject(SubObj);
	}
}

void UInv_InventoryComponent::TryAddItem(UInv_ItemComponent* InItemComponent)
{
	FInv_SlotAvailabilityResult Result = InventoryWidget->HasRoomForItem(InItemComponent);

	if (Result.TotalRoomToFill == 0)
	{
		OnNoRoomInInventory.Broadcast();
	}

	if (Result.Item.IsValid() && Result.bStackable)
	{
		// Add stacks to an item that already exist in the inventory. We only want to update the stack count,
		// not create a new item of this type
		Server_AddStacksToItem(InItemComponent, Result.TotalRoomToFill, Result.Remainder);
	}
	if (Result.TotalRoomToFill > 0)
	{
		// this item doesn't exist in the inventory, create a new one and update all pertinent slots.
		Server_AddNewItem(InItemComponent, Result.bStackable ? Result.TotalRoomToFill : 0);
	}
}

void UInv_InventoryComponent::Server_AddNewItem_Implementation(UInv_ItemComponent* InItem, int32 StackCount)
{
	UInv_InventoryItem* NewItem = InventoryList.AddEntry(InItem);

	if (GetNetMode() == NM_ListenServer || GetNetMode() == NM_Standalone)
	{
		OnItemAdded.Broadcast(NewItem);
	}
}

void UInv_InventoryComponent::Server_AddStacksToItem_Implementation(UInv_ItemComponent* InItem, int32 StackCount, int32 Remainder)
{
	
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

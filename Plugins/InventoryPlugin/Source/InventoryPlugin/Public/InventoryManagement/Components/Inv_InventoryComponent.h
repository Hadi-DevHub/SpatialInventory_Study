#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_ItemComponent;
class UInv_UW_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UInv_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNoRoomInInventory);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPLUGIN_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_InventoryComponent();

	void ToggleInventoryMenu();

	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FOnNoRoomInInventory OnNoRoomInInventory;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "INV PLUGIN")
	void TryAddItem(UInv_ItemComponent* InItemComponent);

	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UInv_ItemComponent* InItem, int32 StackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_AddStacksToItem(UInv_ItemComponent* InItem, int32 StackCount, int32 Remainder);

protected:
	virtual void BeginPlay() override;

	void OpenInventoryMenu();
	void CloseInventoryMenu();
	bool bInventoryMenuOpen = false;

private:

	UFUNCTION()
	void ConstructInventory();
	
	TWeakObjectPtr<APlayerController> OwnerController;

	UPROPERTY()
	TObjectPtr<UInv_UW_InventoryBase> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, Category = "INV PLUGIN | Widgets")
	TSubclassOf<UInv_UW_InventoryBase> InventoryWidgetClass;
};

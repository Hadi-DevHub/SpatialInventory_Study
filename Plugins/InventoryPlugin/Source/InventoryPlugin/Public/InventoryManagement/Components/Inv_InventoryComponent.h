#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_UW_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UInv_InventoryItem*, Item);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPLUGIN_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_InventoryComponent();

	void ToggleInventoryMenu();

	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;

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

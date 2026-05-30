#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inv_InventoryComponent.generated.h"

class UInv_UW_InventoryBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPLUGIN_API UInv_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_InventoryComponent();

protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void ConstructInventory();
	
	TWeakObjectPtr<APlayerController> OwnerController;

	UPROPERTY()
	TObjectPtr<UInv_UW_InventoryBase> InventoryWidget;

	UPROPERTY(EditDefaultsOnly, Category = "INV PLUGIN | Widgets")
	TSubclassOf<UInv_UW_InventoryBase> InventoryWidgetClass;
};

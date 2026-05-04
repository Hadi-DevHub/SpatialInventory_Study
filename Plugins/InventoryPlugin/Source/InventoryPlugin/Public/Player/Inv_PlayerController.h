#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

class UInv_HUDWidget;
class UInputComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class INVENTORYPLUGIN_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	UFUNCTION()
	void PrimaryInteract();

	void CreateHUDWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Inputs")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Inputs")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Widgets")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Plugin | Widgets", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInv_HUDWidget> HUDWidget;
};

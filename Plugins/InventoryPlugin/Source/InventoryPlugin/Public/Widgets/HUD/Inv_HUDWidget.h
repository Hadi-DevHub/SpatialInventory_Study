#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_HUDWidget.generated.h"

class UInv_InfoMessage;

UCLASS()
class INVENTORYPLUGIN_API UInv_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeOnInitialized() override;

	UFUNCTION()
	void OnNoRoom();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowPickupWidget(const FString& PickupMessage);
	
	UFUNCTION(BlueprintImplementableEvent)
	void HidePickupWidget();

private:

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UInv_InfoMessage> WBP_InfoMessage;
};

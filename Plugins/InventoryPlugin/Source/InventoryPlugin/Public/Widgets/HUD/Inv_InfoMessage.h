#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_InfoMessage.generated.h"

class UTextBlock;

UCLASS()
class INVENTORYPLUGIN_API UInv_InfoMessage : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintCallable)
	void SetAndShowMessage(const FText& InMessage);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "INV PLUGIN")
	void ShowMessage();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "INV PLUGIN")
	void HideMessage();

private:

	bool bShowingMessage = false;

	UPROPERTY(EditAnywhere, Meta = (BindWidget), Category = "INV PLUGIN")
	TObjectPtr<UTextBlock> TB_TextMessage;

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	float MessageLifeTime{3};

	FTimerHandle MessageTimerHandle;
};

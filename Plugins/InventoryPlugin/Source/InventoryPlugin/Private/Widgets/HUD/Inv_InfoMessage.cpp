#include "Widgets/HUD/Inv_InfoMessage.h"

#include "Components/TextBlock.h"

void UInv_InfoMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	TB_TextMessage->SetText(FText::GetEmpty());
	HideMessage();
}

void UInv_InfoMessage::SetAndShowMessage(const FText& InMessage)
{
	TB_TextMessage->SetText(InMessage);
	
	if (!bShowingMessage)
	{
		ShowMessage();
	}

	bShowingMessage = true;

	GetWorld()->GetTimerManager().SetTimer(
		MessageTimerHandle,
		[this]()
		{
			HideMessage();
		},
		MessageLifeTime,
		false
		);
	
}

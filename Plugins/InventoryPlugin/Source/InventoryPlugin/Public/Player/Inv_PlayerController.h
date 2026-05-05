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
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	//------------------//
	//	 Item Tracing   //
	//------------------//
	
	void TraceForItems();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Item Tracing")
	float TraceDistance = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Item Tracing")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel = ECC_GameTraceChannel1;

	TWeakObjectPtr<AActor> ThisActor;
	TWeakObjectPtr<AActor> LastActor;

	//------------//
	//	 Inputs   //
	//------------//
	
	UFUNCTION()
	void PrimaryInteract();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Inputs")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Inputs")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMCs;

	//-------------//
	//	 Widgets   //
	//-------------//

	void CreateHUDWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Plugin | Widgets")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Plugin | Widgets", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInv_HUDWidget> HUDWidget;
};

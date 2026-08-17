#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Manifest/Inv_ItemManifest.h"
#include "Inv_ItemComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPLUGIN_API UInv_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInv_ItemComponent();

	void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	FString GetPickupMessage() const { return PickupMessage; }

	FInv_ItemManifest GetItemManifest() const { return ItemManifest; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPickedUp();
	
	void PickedUp();

private:
	UPROPERTY(EditAnywhere , Category = "INV PLUGIN | Item Property")
	FString PickupMessage = "E - To Pickup";

	UPROPERTY(EditAnywhere, Replicated, Category = "INV PLUGIN | Item Property")
	FInv_ItemManifest ItemManifest;
};

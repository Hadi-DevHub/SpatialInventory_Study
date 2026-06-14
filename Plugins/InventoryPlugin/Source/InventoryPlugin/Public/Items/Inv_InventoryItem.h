#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "UObject/Object.h"
#include "Manifest/Inv_ItemManifest.h"
#include "Inv_InventoryItem.generated.h"

struct FInv_ItemManifest;

UCLASS()
class INVENTORYPLUGIN_API UInv_InventoryItem : public UObject
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	void SetItemManifest(const FInv_ItemManifest& Manifest);

private:

	UPROPERTY(VisibleAnywhere, Replicated, meta = (BaseStruct = "/Script/InventoryPlugin.Inv_ItemManifest"))
	FInstancedStruct ItemManifest;
};












// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagement/InventoryStatics/InventoryStatics.h"

#include "InventoryManagement/Components/Inv_InventoryComponent.h"

UInv_InventoryComponent* UInventoryStatics::GetInventoryComponent(APlayerController* InPlayerController)
{
	if (!IsValid(InPlayerController)) return nullptr;

	UInv_InventoryComponent* InventoryComponent = InPlayerController->FindComponentByClass<UInv_InventoryComponent>();
	return InventoryComponent;
}

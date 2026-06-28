#include "Widgets/Inventory/GridSlots/Inv_GridSlot.h"
#include "Components/Image.h"

void UInv_GridSlot::SetSlotToUnoccupied()
{
	SlotState = EGridSlotState::GSS_Unoccupied;
	IMG_GridSlot->SetBrush(Unoccupied_Brush);
}

void UInv_GridSlot::SetSlotToOccupied()
{
	SlotState = EGridSlotState::GSS_Occupied;
	IMG_GridSlot->SetBrush(Occupied_Brush);
}

void UInv_GridSlot::SetSlotToActive()
{
	SlotState = EGridSlotState::GSS_Active;
	IMG_GridSlot->SetBrush(Active_Brush);
}

void UInv_GridSlot::SetSlotToDisabled()
{
	SlotState = EGridSlotState::GSS_Disabled;
	IMG_GridSlot->SetBrush(Disabled_Brush);
}

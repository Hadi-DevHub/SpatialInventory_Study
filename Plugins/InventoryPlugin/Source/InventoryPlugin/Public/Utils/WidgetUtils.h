#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetUtils.generated.h"

class UInv_ItemComponent;

UCLASS()
class INVENTORYPLUGIN_API UWidgetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static int32 GetIndexFromPosition(const FIntPoint& Position, const int32 Columns);
	static FIntPoint GetPosFromIndex(int32 Index, const int32 Columns);
};

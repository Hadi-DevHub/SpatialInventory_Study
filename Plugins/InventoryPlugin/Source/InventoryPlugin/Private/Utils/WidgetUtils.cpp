#include "Utils/WidgetUtils.h"

int32 UWidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.Y + Columns * Position.X;
}

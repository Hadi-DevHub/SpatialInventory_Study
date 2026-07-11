#include "Utils/WidgetUtils.h"

int32 UWidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.X + Columns * Position.Y;
}

FIntPoint UWidgetUtils::GetPosFromIndex(int32 Index, int32 Columns)
{
	int32 Remainder = Index % Columns;
	return FIntPoint(Index % Columns, Index / Columns);
}

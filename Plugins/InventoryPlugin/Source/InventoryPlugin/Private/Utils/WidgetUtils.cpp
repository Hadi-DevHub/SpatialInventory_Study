#include "Utils/WidgetUtils.h"

int32 UWidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.Y + Columns * Position.X;
}

FIntPoint UWidgetUtils::GetPosFromIndex(int32 Index, int32 Columns)
{
	int32 Remainder = Index % Columns;
	return FIntPoint(FMath::DivideAndRoundDown(Index, Columns), Remainder);
}

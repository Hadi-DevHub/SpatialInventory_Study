#include "Utils/WidgetUtils.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Widget.h"

int32 UWidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return Position.X + Columns * Position.Y;
}

FIntPoint UWidgetUtils::GetPosFromIndex(int32 Index, int32 Columns)
{
	int32 Remainder = Index % Columns;
	return FIntPoint(Index % Columns, Index / Columns);
}

FVector2D UWidgetUtils::GetWidgetPosition(UWidget* Widget)
{
	FGeometry Geometry = Widget->GetCachedGeometry();

	FVector2D ViewportPosition = FVector2D::ZeroVector;
	FVector2D PixelPosition = FVector2D::ZeroVector;

	USlateBlueprintLibrary::LocalToViewport(Widget, Geometry, USlateBlueprintLibrary::GetLocalTopLeft(Geometry), PixelPosition, ViewportPosition);

	return ViewportPosition;
}

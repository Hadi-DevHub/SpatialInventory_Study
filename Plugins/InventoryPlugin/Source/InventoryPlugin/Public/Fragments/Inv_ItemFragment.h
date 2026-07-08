#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Inv_ItemFragment.generated.h"

class UImage;

USTRUCT(BlueprintType)
struct FInv_ItemFragment 
{
	GENERATED_BODY()

	FInv_ItemFragment() {};
	FInv_ItemFragment(const FInv_ItemFragment&) = default;
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;
	FInv_ItemFragment(FInv_ItemFragment&&) = default;
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;
	virtual ~FInv_ItemFragment() {}

	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	void SetFragment(FGameplayTag Tag) { FragmentTag = Tag; };
	
private:
	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
	
};

USTRUCT(BlueprintType)
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FIntPoint GetGridSize() const { return GridSize; }
	float GetGridPadding() const { return GridPadding; }

	void SetGridSize(FIntPoint InGridSize) { GridSize = InGridSize; }
	void SetGridPadding(float InGridPadding) { GridPadding = InGridPadding; }
	
private:
	
	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	FIntPoint GridSize{1,1};

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	float GridPadding = 0.f;
	
};

USTRUCT(BlueprintType)
struct FInv_IconFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	UTexture2D* GetIcon() const { return ItemIcon; }
	
private:

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	TObjectPtr<UTexture2D> ItemIcon{ nullptr };

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	FVector2D IconSize{44.f,44.f};
};

USTRUCT()
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()


public:
	
	int32 GetMaxStackSize() const { return MaxStackSize; }
	int32 GetStackCount() const { return StackCount; }
	
private:

	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	int32 MaxStackSize{1};
	
	UPROPERTY(EditAnywhere, Category = "INV PLUGIN")
	int32 StackCount{1};
};

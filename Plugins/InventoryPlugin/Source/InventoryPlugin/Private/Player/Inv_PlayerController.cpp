#include "Player/Inv_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InventoryPlugin.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUD/Inv_HUDWidget.h"

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &ThisClass::PrimaryInteract);
	}
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		for (auto Context : DefaultIMCs)
		{
			Subsystem->AddMappingContext(Context, 0);
		}
	}
	CreateHUDWidget();
}

void AInv_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TraceForItems();
}

void AInv_PlayerController::PrimaryInteract()
{
	UE_LOG(LogInventory, Log, TEXT("primary interact called"))
}

void AInv_PlayerController::CreateHUDWidget()
{
	if (!IsLocalController()) return;
	checkf(HUDWidgetClass, TEXT("don't forget to set the HUD widget class!."));
	
	HUDWidget = CreateWidget<UInv_HUDWidget>(this, HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}

void AInv_PlayerController::TraceForItems()
{
	if (!IsValid(GEngine)) return;
	
	FVector2D Viewport;
	GEngine->GameViewport->GetViewportSize(Viewport);
	FVector2D ViewportCenter = Viewport / 2.f;
	
	FVector TraceStart;
	FVector Forward;
	FHitResult HitResult;
	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward)) return;
	FVector End = TraceStart + Forward * TraceDistance;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, End, ItemTraceChannel);

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	if (ThisActor == LastActor) return;

	if (ThisActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("started tracing an item!."));
		
		UInv_ItemComponent* ThisActorItemComponent = ThisActor->FindComponentByClass<UInv_ItemComponent>();
		if (!IsValid(ThisActorItemComponent)) return;
		
		if (IsValid(HUDWidget)) HUDWidget->ShowPickupWidget(ThisActorItemComponent->GetPickupMessage());
	}
	else
	{
		HUDWidget->HidePickupWidget();
	}
	
	if (LastActor.IsValid()) UE_LOG(LogTemp, Warning, TEXT("stopped tracing an item!."))

}


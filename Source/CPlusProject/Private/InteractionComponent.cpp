#include "InteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionComponent::Interact()
{
	
}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}





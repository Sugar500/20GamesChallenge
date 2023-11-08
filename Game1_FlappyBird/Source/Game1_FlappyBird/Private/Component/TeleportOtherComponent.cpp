// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/TeleportOtherComponent.h"

#include "Component/ResetComponent.h"


// Sets default values for this component's properties
UTeleportOtherComponent::UTeleportOtherComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTeleportOtherComponent::BeginPlay()
{
	Super::BeginPlay();

	if(UPrimitiveComponent* ColliderComponent = GetOwner()->GetComponentByClass<UPrimitiveComponent>();
		ColliderComponent != nullptr)
		ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
	
}


// Called every frame
void UTeleportOtherComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTeleportOtherComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetComponentByClass<UResetComponent>())
	{
		OtherActor->SetActorLocation(TeleportLocation->GetActorLocation());
	}
}


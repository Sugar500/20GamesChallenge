// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResetComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeathDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAME1_FLAPPYBIRD_API UResetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResetComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	void BroadcastPlayerDeath() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FPlayerDeathDelegate CallDeathDelegate;

private:
	void ResetLevel() const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gadget.generated.h"

UCLASS(ABSTRACT)
class APESELFSTUDY_API AGadget : public AActor
{
	GENERATED_BODY()
	
public:
	AGadget();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	class UCapsuleComponent* Hitbox;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlapComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult);
};

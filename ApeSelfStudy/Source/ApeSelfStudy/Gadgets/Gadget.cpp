// Fill out your copyright notice in the Description page of Project Settings.


#include "Gadget.h"

#include "ApeSelfStudy/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"

AGadget::AGadget()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Hitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hitbox"));
	Hitbox->SetupAttachment(Root);
	
}

void AGadget::BeginPlay()
{
	Super::BeginPlay();
	Hitbox->OnComponentBeginOverlap.AddDynamic(this,&AGadget::OnOverlapBegin);
}

void AGadget::OnOverlapBegin(UPrimitiveComponent* OverlapComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner()))
	{
		if(player->getIsSwinging())
		{
			GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, TEXT("Overlapp"));
		}
	}
}



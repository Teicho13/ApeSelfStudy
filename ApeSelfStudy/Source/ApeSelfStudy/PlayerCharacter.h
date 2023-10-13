// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"

//Needs to be last
#include "PlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;


UENUM(BlueprintType)
enum class EGadgets : uint8 {
	E_None       UMETA(DisplayName="None"),
	E_StunClub       UMETA(DisplayName="Stun Club"),
	E_TimeNet        UMETA(DisplayName="Time Net"),
	E_MonkeyRadar        UMETA(DisplayName="Monkey Radar"),
	E_SlingShot        UMETA(DisplayName="Slingshot"),
	E_Hoop        UMETA(DisplayName="Hoop")
};



UCLASS()
class APESELFSTUDY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool getIsSwinging();

	UFUNCTION(BlueprintCallable)
	void setIsSwinging(bool swings);

	UFUNCTION(BlueprintCallable)
	void SetIsProning(bool proning);

	UFUNCTION(BlueprintCallable)
	bool getIsProning();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Jump(const FInputActionValue& value);
	void Move(const FInputActionValue& value);
	void Swing(const FInputActionValue& value);
	void Prone(const FInputActionValue& value);

	/* MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ProneAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SwingAction;

	UPROPERTY(EditDefaultsOnly, Category="Configurations")
	TSubclassOf<class AGadget> DefaultGadget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Gadgets)
	EGadgets EquipedGadget;

private:
	bool isSwinging;
	bool isProning;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTypes.h"
#include "QuadTreeComponent.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"


UCLASS()
class QUA_OCT_TREE_EXAMPLE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//UPROPERTY()
	FQuadNode* CurrentNode;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere , Category = Component)
	UQuadTreeComponent* QuadTreeComponent;



	UPROPERTY(EditAnywhere,Category = QuandNode)
	float X;
	UPROPERTY(EditAnywhere,Category = QuandNode)
	float Y;
	UPROPERTY(EditAnywhere,Category = QuandNode)
	float Divied;
	UPROPERTY(EditAnywhere,Category = QuandNode)
	FVector Origin;
	
	
};



// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MainCharacter.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

#define QUANDTREE QuadTreeComponent->GetQuandTree()

namespace NS_MainCharacterCvars
{
	static  bool bShowQuadLine = false;
	FAutoConsoleVariableRef ConsoleVariableRef(TEXT("quad.bShowQuad"),bShowQuadLine,
		TEXT("ToShowQuadLine \n 0 :Hide ,  1:  Show "),ECVF_Default);
	
}

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	QuadTreeComponent = CreateDefaultSubobject<UQuadTreeComponent>(TEXT("QuadTreeComponent"));

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	QuadTreeComponent->InitQuadTree(X,Y,Divied,Origin);
	QUANDTREE->CreateQuanTree();
	QUANDTREE->InitQuandTree(GetWorld(),QUANDTREE->GetRootNode(),nullptr);
	int32 i = QuadTreeComponent->GetQuandTree()->GetAllNodeNum(QUANDTREE->GetRootNode(),0);
	print(FString::SanitizeFloat(i));
	DrawDebugSphere(GetWorld(),QUANDTREE->GetRootNode()->Origin,64,8,FColor::Red,true);
	
}


// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (QUANDTREE == nullptr)
		return;
	
	if (CurrentNode == nullptr )
	{
		CurrentNode = QuadTreeComponent->FindCharCurrentLocNode(QUANDTREE->GetRootNode());
		if (CurrentNode && NS_MainCharacterCvars::bShowQuadLine)
		{
			DrawDebugSphere(GetWorld(),CurrentNode->Origin,64,4,FColor::Black,true);
		}
	}
	else
	{
		float Dis = UKismetMathLibrary::Vector_Distance(CurrentNode->Origin , GetActorLocation());
		if (Dis > CurrentNode->Divide / 2)
		{
			// Reset
			CurrentNode = nullptr;
		}
	}
	


	
}
// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

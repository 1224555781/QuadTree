// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/QuadTreeComponent.h"

// Sets default values for this component's properties
UQuadTreeComponent::UQuadTreeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuadTreeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuadTreeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuadTreeComponent::InitQuadTree(float InX, float InY, float InDivide, FVector InOrigin)
{
	QuadTree = MakeShareable<FQuadTree>( new FQuadTree(InOrigin,InX,InY,InDivide));
}


FQuadNode* UQuadTreeComponent::FindCharCurrentLocNode(FQuadNode* Node)
{
	ensureMsgf(Node,TEXT("Find Char Failed Input A NULL Node"));
	
	FQuadNode* RetNode = Node;
	//Real Distance Node To ParentNode , Node.X .Y is The Max Distance
	float Real_X; 
	float Real_Y;
	const FVector CharLoc = GetOwner()->GetActorLocation();
	if (Node->ParentNode)
	{
		Real_X = FMath::Abs(Node->Origin.X - Node->ParentNode->Origin.X) ;
		Real_Y = FMath::Abs(Node->Origin.Y - Node->ParentNode->Origin.Y) ;
	}
	else
	{
		Real_X = Node->X  / 2;
		Real_Y = Node->Y / 2;
	}

	
	if (!CharIsInNodeArea(Node,CharLoc,Real_X,Real_Y))
	{
		return nullptr;
	}
	
	//#TODO Char Cross Node Area
	//Begin Check  Time : Log(n)
	
	
	RetNode = CharIsInChildArea(RetNode,CharLoc);
	float Real_Radius_X; 
	float Real_Radius_Y;
	Real_Radius_X = FMath::Abs(RetNode->Origin.X - RetNode->ParentNode->Origin.X) ;
	Real_Radius_Y = FMath::Abs(RetNode->Origin.Y - RetNode->ParentNode->Origin.Y) ;
	//print(CharLoc.ToString() + Node->Origin.ToString() + FString::SanitizeFloat(Real_Radius_X) + TEXT("Real_Y") + FString::SanitizeFloat(Real_Radius_Y) + FString::SanitizeFloat(Node->Divide));
	
	if (Real_Radius_X  <= RetNode->Divide && Real_Radius_Y  <= RetNode->Divide)
	{
		// Find Last Result
		RetNode = CharIsInChildArea(RetNode,CharLoc);
		return RetNode;
	}
	else
	{
		RetNode = FindCharCurrentLocNode(RetNode);
	}
	
	
	
	return RetNode;
}

bool UQuadTreeComponent::CharIsInNodeArea(FQuadNode* Node , FVector Target,float Real_X , float Real_Y) const
{
	return  Target.X <= (Node->Origin.X + Real_X)
    && Target.Y <= ( Node->Origin.Y + Real_Y)
    && Target.X >= (Node->Origin.X - Real_X)
    && Target.Y >= (Node->Origin.Y - Real_Y);
}


FQuadNode* UQuadTreeComponent::CharIsInChildArea(FQuadNode* Node , FVector CharLoc ) const
{
	FQuadNode* RET = Node;
	if (Node->ChildrenNode.Num() == 0)
	{
		return RET;
	}
	if (Node->Origin.X <= CharLoc.X && Node->Origin.Y <= CharLoc.Y)
	{
		RET = Node->ChildrenNode[0];
	}
	else if (Node->Origin.X >= CharLoc.X && Node->Origin.Y <= CharLoc.Y)
	{
		RET = Node->ChildrenNode[1];
	}
	else if (Node->Origin.X >= CharLoc.X && Node->Origin.Y >= CharLoc.Y)
	{
		RET = Node->ChildrenNode[2];
	}
	else if (Node->Origin.X <= CharLoc.X && Node->Origin.Y >= CharLoc.Y)
	{
		RET = Node->ChildrenNode[3];
	}
	return  RET;
}
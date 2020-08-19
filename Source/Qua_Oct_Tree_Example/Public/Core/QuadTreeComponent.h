// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTypes.h"
#include "Components/ActorComponent.h"
#include "QuadTreeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUA_OCT_TREE_EXAMPLE_API UQuadTreeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuadTreeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitQuadTree(float InX,float InY,float InDivide,FVector InOrigin);
	FQuadTree* GetQuandTree()const
	{
		return QuadTree.Get();
	}
	
	bool CharIsInNodeArea(FQuadNode* Node, FVector Target,float Real_X , float Real_Y) const;
	FQuadNode* CharIsInChildArea(FQuadNode* NodeNode , FVector Target) const;
	FQuadNode* FindCharCurrentLocNode(FQuadNode* Node);


	
private:
	TSharedPtr<FQuadTree,ESPMode::ThreadSafe>QuadTree;
		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"

/**
 * 
 */

#define print(text) GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::White,text)
//USTRUCT()
struct FQuadNode
{
    
   // GENERATED_USTRUCT_BODY()
public:
    float X;
    float Y;
    float Divide;
    FVector Origin;
    //FQuadNode* ChildrenNode[2][2];
    TArray<FQuadNode*>ChildrenNode ;
    FQuadNode* ParentNode;
    bool IsValidNode()
    {
        return !ParentNode ? NULL : FMath::Abs( X / 2 /*Origin.X - ParentNode->Origin.X*/)  <= Divide && FMath::Abs( Y / 2 /*Origin.Y - ParentNode->Origin.Y*/)<=Divide;
    }

    bool operator ==(const FQuadNode& Other) const
    {
        return Origin == Other.Origin;
    }
    
    FQuadNode()
        :X(1000),Y(1000),Divide(100)
    {}
    
    //Init Child Node
    FQuadNode(float InX,float InY,float InDivide,FVector InOrigin)
        :X(InX),Y(InY),Divide(InDivide),Origin(InOrigin)
    {
    }
    
};


class FQuadTree
{
public:
    FQuadTree() = default;
    FQuadTree(FVector InOrigin,float InX, float InY ,float InDiviede)
        :Origin(InOrigin),X(InX),Y(InY),Diviede(InDiviede)
    {
        
    };
    ~FQuadTree()
    {
        
    };
public:
    FQuadNode* GetRootNode() const{return  RootNode;}
    void CreateQuanTree();
    void InitQuandTree(UWorld* world,FQuadNode* Node,FQuadNode* InParentNode);
    void CreateChildNode(FQuadNode* Node);
    void DrawQuandTree(const UWorld* world,FQuadNode* Node );
    int32 GetAllNodeNum(FQuadNode* Node,int32 i);
    FQuadNode* GetParentNode() const {return ParentNode;}
private:
    FQuadNode* RootNode;
    FQuadNode* ParentNode;
    //TODO Diviede Is Max Radius
    float X, Y , Diviede;
    FVector Origin;
    
};

inline void FQuadTree::CreateQuanTree()
{
    RootNode = new FQuadNode(X,Y,Diviede,Origin);
}

inline void FQuadTree::InitQuandTree(UWorld* world,FQuadNode* Node,FQuadNode* InParentNode)
{
    Node->ParentNode = InParentNode;
    if (Node->IsValidNode())
    {
        DrawDebugSphere(world,Node->Origin,15.f,16,FColor::Yellow,true);
        DrawQuandTree(world,Node);
        return;
    }
   
    if(Node == NULL)
        return;
    CreateChildNode(Node);
    for (auto a : Node->ChildrenNode)
    {
        InitQuandTree( world, a ,Node);
    }
}

inline void FQuadTree::CreateChildNode(FQuadNode* Node)
{
    if (Node->ChildrenNode.Num() == 0 )
    {
        Node->ChildrenNode.Add(new FQuadNode(Node->X/2,Node->Y/2,Node->Divide,Node->Origin + FVector(Node->X/4,Node->Y/4,0)));
        Node->ChildrenNode.Add(new FQuadNode(Node->X/2,Node->Y/2,Node->Divide,Node->Origin + FVector(-Node->X/4,Node->Y/4,0)));
        Node->ChildrenNode.Add(new FQuadNode(Node->X/2,Node->Y/2,Node->Divide,Node->Origin + FVector(-Node->X/4,-Node->Y/4,0)));
        Node->ChildrenNode.Add( new FQuadNode(Node->X/2,Node->Y/2,Node->Divide,Node->Origin + FVector(Node->X/4,-Node->Y/4,0)));	

    }
}

inline void FQuadTree::DrawQuandTree(const UWorld* world,FQuadNode* Node)
{
    print(Node->Origin.ToString());
    if (!Node || !Node->ParentNode)
    {
        return;
    }
    float Dis_X = FMath::Abs(Node->Origin.X - Node->ParentNode->Origin.X);
    float Dis_Y = FMath::Abs(Node->Origin.Y - Node->ParentNode->Origin.Y);
    const FVector NW = FVector( -Dis_X + Node->Origin.X,Dis_Y + Node->Origin.Y,100);
    const FVector NE = FVector(Dis_X + Node->Origin.X,Dis_Y + Node->Origin.Y,100);
    const FVector SW = FVector(-Dis_X + Node->Origin.X,-Dis_Y + Node->Origin.Y,100);
    const FVector SE = FVector(Dis_X + Node->Origin.X,-Dis_Y + Node->Origin.Y,100);
    DrawDebugLine(world,NW,NE,FColor::Green,true);
    DrawDebugLine(world,NW,SW,FColor::Green,true);
    DrawDebugLine(world,SW,SE,FColor::Green,true);
    DrawDebugLine(world,SE,NE,FColor::Green,true);
    DrawDebugLine(world,(SW+NW)/2,(SE+NE)/2,FColor::Red,true);
    DrawDebugLine(world,(SW+SE)/2,(NW+NE)/2,FColor::Red,true);
}

inline int32 FQuadTree::GetAllNodeNum(FQuadNode* Node,int32 i)
{
  
    i ++;
    if (Node->ChildrenNode.Num() == 0)
    {
        return i;
    }
   
    for (auto a : Node->ChildrenNode)
    {
        i = GetAllNodeNum(a,i);
    }
     return  i;
}



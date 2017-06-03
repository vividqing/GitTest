//
//  AVL Tree.c
//  Data_Structures
//
//  Created by 朢长安 on 2017/4/30.
//  Copyright © 2017年 Gran. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNODE AvlNode;
typedef struct AVLNODE *Position;
typedef struct AVLNODE *AvlTree;
typedef int ElementType;

AvlTree MakeEmpty(AvlTree T);

Position Find(int X, AvlTree T);

Position FindMin(AvlTree T);

Position FindMax(AvlTree T);

int Height(Position P);

static int Max(int a, int b);

static Position SingleRotateWithLeft(Position K2);

static Position SingleRotateWithRight(Position K1);

static Position DoubleRotateWithLeft(Position K3);

static Position DoubleRotateWithRight(Position K3);

AvlTree Insert(int X, AvlTree T);

AvlTree Delete(int X, AvlTree T);

int Retrieve(Position P);

struct AVLNODE {
    ElementType data;
    AvlTree Left;
    AvlTree Right;
    int Height;
};

AvlTree MakeEmpty(AvlTree T)  //将树置空
{
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(int X, AvlTree T) {
    if (T == NULL)
        return NULL;
    else if (X < T->data)
        return Find(X, T->Left);
    else if (X > T->data)
        return Find(X, T->Right);
    else
        return T;
}

Position FindMin(AvlTree T) {
    if (T != NULL)
        while (T->Left != NULL)
            T = T->Left;
    return T;
}

Position FindMax(AvlTree T) {
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;
    return T;
}

int Height(Position P)    //计算 AVL 节点高度的函数
{
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

AvlTree Insert(int X, AvlTree T) {
    if (T == NULL) {
        //如果树为空，创建并返回只有一个结点的树
        T = malloc(sizeof(AvlNode));
        if (T == NULL) {
            printf("Out of space!!!");
            exit(1);
        } else {
            T->data = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    } else if (X < T->data) {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2) {
            if (X < T->Left->data)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    } else if (X > T->data) {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2) {
            if (X < T->Right->data)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

int Max(int a, int b) {
    //return (a >= b ? a : b);
    if (a > b)
        return a;
    else
        return b;
}

//单旋转，这个函数只能在 K2 有一个左孩的情况下使用，在 K2 节点和它的左孩子之间进行旋转，更新高度，然后返回一个新的根

Position SingleRotateWithLeft(Position K2) {
    Position K1;
    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;
    
    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), K2->Height) + 1;
    
    return K1;  //新的根
}

//单旋转，这个函数只能在 K2 有一个右孩的情况下使用，在 K2 节点和它的右孩子之间进行旋转，更新高度，然后返回一个新的根

Position SingleRotateWithRight(Position K1) {
    Position K2;
    
    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;
    
    K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
    K2->Height = Max(K1->Height, Height(K2->Right)) + 1;
    
    return K2;
}

//双旋转，这个函数只适用于 K3 有一个左孩，它的左孩还有一个右孩，执行左右双旋转，返回一个新的根

Position DoubleRotateWithLeft(Position K3) {
    //旋转 K1 和 K2 之间
    K3->Left = SingleRotateWithLeft(K3->Left);
    
    //旋转 K3 和 K2 之间
    return SingleRotateWithLeft(K3);
    
}

//双旋转，这个函数只适用于 K3 有一个右孩，它的右孩还有一个左孩，执行左右双旋转，返回一个新的根

Position DoubleRotateWithRight(Position K3) {
    //旋转 K1 和 K2 之间
    K3->Right = SingleRotateWithLeft(K3->Left);
    
    //旋转 K3 和 K2 之间
    return SingleRotateWithLeft(K3);
    
}

AvlTree Delete(int X, AvlTree T) {
    Position tmpnode;
    
    if (T == NULL) {
        printf("the tree have not any treenode\n");
        exit(-1);
    } else if (X < T->data)
        T->Left = Delete(X, T->Left);
    else if (X > T->data)
        T->Right = Delete(X, T->Right);
    else if (T->Left && T->Right) {
        tmpnode = FindMin(T->Right);
        T->data = tmpnode->data;
        T->Right = Delete(T->data, T->Right);
    } else {
        tmpnode = T;
        if (T->Left == NULL)
            T = T->Right;
        else if (T->Right == NULL)
            T = T->Left;
        free(tmpnode);
    }
    return T;
}

int Retrieve(Position P) {
    return P->data;
}

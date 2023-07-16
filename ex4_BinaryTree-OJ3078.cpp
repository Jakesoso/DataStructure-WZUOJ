/*
* 3078-先序拓展创建
* 问题描述:给出二叉树的先序遍历输出(空结点用'.')表示，
*         请构造二叉树，并按中序遍历的顺序输出二叉树的结点。
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct Node
{
    ElementType data;
    struct Node* lchild;
    struct Node* rchild;
}BTNode, * BTree;

BTree preOrderExtCreate() {
    char ch = getchar();
    if (ch == '.') return NULL;
    BTNode* node = (BTNode*)malloc(sizeof(BTNode)); 
    node->data = ch;
    node->lchild = preOrderExtCreate();
    node->rchild = preOrderExtCreate();
    return node;
}

void inOrder(BTree rt) {
    if (rt != NULL) {
        inOrder(rt->lchild);
        std::cout << rt->data;
        inOrder(rt->rchild);
    }
}

int main() {
    BTree bt = preOrderExtCreate();
    inOrder(bt);
    std::cout << std::endl;
}
/*
* 3079-树状输出I
* 问题描述:给出二叉树的先序遍历输出(空结点用'.')表示，
*         请构造二叉树，并按树状输出该二叉树(竖向)。
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

void treePrint(BTree bt, int layer = 0) {
    if (bt == NULL) return;

    treePrint(bt->rchild, layer + 1);
    for (int i = 0; i < layer; i++)
        std::cout << "-";
    std::cout << bt->data << std::endl;
    treePrint(bt->lchild, layer + 1);
}

int main() {
    BTree bt = preOrderExtCreate();
    treePrint(bt);
}
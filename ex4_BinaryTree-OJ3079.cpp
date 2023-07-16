/*
* 3079-��״���I
* ��������:����������������������(�ս����'.')��ʾ��
*         �빹���������������״����ö�����(����)��
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
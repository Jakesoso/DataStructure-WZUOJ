/*
* 3079-树状输出II
* 问题描述:给出二叉树的先序遍历输出(空结点用'.')表示，
*         请构造二叉树，并按树状输出该二叉树(横向)。
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string>

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

//void treePrint(BTree bt) {
//	std::queue<BTree> q;
//	BTree node;
//	std::string output[100];
//	int layer, childNode_cnt[100];
//
//	q.push(bt);
//	layer = 0;
//	// see head node as the first chidnode
//	childNode_cnt[0] = 1;
//
//	while (!q.empty()) {
//		node = q.front(), q.pop();
//		childNode_cnt[layer]--;
//
//		if (childNode_cnt[layer] == 0) {
//			layer++;
//			childNode_cnt[layer] = 0;
//			std::cout << layer << " :layer updated!" << std::endl;
//		}
//
//		output[layer] += node->data;
//
//		if (node->lchild != NULL) {
//			q.push(node->lchild);
//			childNode_cnt[layer]++;
//		}
//		if (node->rchild != NULL) {
//			q.push(node->rchild);
//			childNode_cnt[layer]++;
//		}
//	}
//}

int main() {
    BTree bt = preOrderExtCreate();
    //treePrint(bt);
}
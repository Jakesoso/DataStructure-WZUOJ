/*
* 3095-��������������
* ����n����ֵ��������ͬ����������ֵ����˳����뵽�����������С�����������������Ĺ�����ʾ��
* ���룺��һ����һ��������n(n<200000)��������n��ÿ��һ��������
* ������ڵ���һ������������������Ĺ�����ʾ
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node {
	ElementType	 data;
	struct Node* lchild;
	struct Node* rchild;
}BSTNode, * BSTree;

BSTree createNode(ElementType data, BSTree lchild, BSTree rchild) {
	BSTree bst = (BSTree)malloc(sizeof(BSTNode));
	bst->data = data;
	bst->lchild = lchild;
	bst->rchild = rchild;
	return bst;
}

BSTree insert(BSTree bst, ElementType x) {
	if (bst == NULL)	bst = createNode(x, NULL, NULL);
	else if (x < bst->data)	bst->lchild = insert(bst->lchild, x);
	else if (x > bst->data)	bst->rchild = insert(bst->rchild, x);
	return bst;
}

void printTree(BSTree bst) {
	if (bst != NULL) {
		std::cout << bst->data;
		if (bst->lchild != NULL || bst->rchild != NULL) {
			std::cout << '(';
			printTree(bst->lchild);
			std::cout << ',';
			printTree(bst->rchild);
			std::cout << ')';
		}
	}
}

int main() {
	int k, num;
	BSTree bst = NULL;
	std::cin >> k;
	for (int i = 0; i < k; i++) {
		std::cin >> num;
		bst = insert(bst, num);
	}
	printTree(bst);
	std::cout << std::endl;
}
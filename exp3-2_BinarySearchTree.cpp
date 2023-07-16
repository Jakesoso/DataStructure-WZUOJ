#include "DataStructure-OJ.hpp"
using namespace std;

typedef int ElementType;
typedef struct Node {
	ElementType	 data;
	struct Node* lchild;
	struct Node* rchild;
}BSTNode, *BSTree;

BSTree createNode(ElementType data, BSTree lchild, BSTree rchild) {
	BSTree bst = (BSTree)malloc(sizeof(BSTNode));
	bst->data = data;
	bst->lchild = lchild;
	bst->rchild = rchild;
	return bst;
}

BSTree insert(BSTree bst, ElementType x) {
	if		(bst == NULL)	bst = createNode(x, NULL, NULL);
	else if	(x < bst->data)	bst->lchild = insert(bst->lchild, x);
	else if (x > bst->data)	bst->rchild = insert(bst->rchild, x);
	return bst;
}

void inOrder(BSTree bst) {
	if (bst != NULL) {
		inOrder(bst->lchild);
		cout << bst->data << " ";
		inOrder(bst->rchild);
	}
}

BSTNode* findMin(BSTree bst) {
	if (bst == NULL)	return NULL;
	while (bst->lchild != NULL) {
		bst = bst->lchild;
	}
	return bst;
}

BSTNode* findMax(BSTree bst) {
	if (bst == NULL)	return NULL;
	while (bst->rchild != NULL) {
		bst = bst->rchild;
	}
	return bst;
}

BSTNode* find(BSTree bst, ElementType x) {
	if		(bst == NULL)	return NULL;
	if		(x > bst->data)	find(bst->rchild, x);
	else if (x < bst->data)	find(bst->lchild, x);
	else					return bst;
}

BSTree deleteNode(BSTree bst, ElementType x) {
	if (bst == NULL)			return NULL;

	if		(x < bst->data)		bst->lchild = deleteNode(bst->lchild, x);
	else if (x > bst->data)		bst->rchild = deleteNode(bst->rchild, x);
	else {
		if (bst->lchild != NULL && bst->rchild != NULL) {
			BSTNode* minNode = findMin(bst->rchild);
			bst->data = minNode->data;
			bst->rchild = deleteNode(bst->rchild, bst->data);
		}
		else {
			BSTNode* tmp = bst;
			bst = (bst->lchild != NULL) ? bst->lchild : bst->rchild;
			free(tmp);
		}
	}
	return bst;
}

BSTree destroyBSTree(BSTree bst) {
	if (bst == NULL)	return NULL;
	destroyBSTree(bst->lchild);
	destroyBSTree(bst->rchild);
	free(bst);
}

int main() {
	BSTree bts = createNode(6, NULL, NULL);
	insert(bts, 2);
	insert(bts, 8);
	insert(bts, 1);
	insert(bts, 5);
	insert(bts, 3);
	insert(bts, 4);

	deleteNode(bts, 2);
	inOrder(bts);

}
/*
* 3098-��������������
* ����һ���������������������ʽ���Լ�ĳ������x���ڶ����������ϲ���x(����Ѿ������򲻲���)��
* ���룺�����һ���Ƕ����������ĵĹ�����ʾ�������������2000000���ַ���
*      �ڶ�����һ��������n(������2000000��)����ʾ��n����Ҫ���롣������ÿ��һ������x��
* ������Թ�������ʽ������Ķ�����������
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

const int MAX_NODE = 2000010;
char str[2000000];
// nodes list which are working on
BSTree curr_node[MAX_NODE] = { NULL };

BSTree createNode(ElementType data, BSTree lchild, BSTree rchild) {
	BSTree bst = (BSTree)malloc(sizeof(BSTNode));
	bst->data = data;
	bst->lchild = lchild;
	bst->rchild = rchild;
	return bst;
}

BSTree createTree(char s[]) {
	enum STATUS {
		UNDEFINED, ON_LEFT, ON_RIGHT,
	};
	int status = UNDEFINED;
	// the node index which is working on
	int layer = -1;
	BSTree new_node = NULL;
	char* str = s;

	while (*str != '\0') {
		if (isdigit(*str)) {
			// read all the numbers
			int data = 0;
			while (isdigit(*str)) {
				data = data * 10 + (*str - '0');
				str++;
			}
			str--;

			new_node = createNode(data, NULL, NULL);
			// working on left child
			if (status == ON_LEFT) {
				curr_node[layer]->lchild = new_node;
			}
			// working on right child
			if (status == ON_RIGHT) {
				curr_node[layer]->rchild = new_node;
			}
		}
		// begin working on next node
		else if (*str == '(') {
			status = ON_LEFT;
			layer++;
			curr_node[layer] = new_node;
		}
		else if (*str == ',') {
			status = ON_RIGHT;
		}
		// finish current node
		else if (*str == ')') {
			layer--;
		}
		str++;
	}

	// only has one node
	if (curr_node[0] == NULL) {
		curr_node[0] = new_node;
	}
	return curr_node[0];
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
	std::cin >> str;
	BSTree bst = createTree(str);
	int k, num;
	std::cin >> k;
	while (k--) {
		std::cin >> num;
		insert(bst, num);
	}
	printTree(bst);
	std::cout << std::endl;
}

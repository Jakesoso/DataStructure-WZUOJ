/*
* 3096-二叉搜索树判定
* 给定一个二叉树的广义表表示（节点值为整数），判定该二叉树是否为二叉搜索树。
* 输入：输入只有一行，为二叉树的广义表表示。该行最长不超过2000000个字符。
* 输出：如果是二叉搜索树，输出yes，否则输出no
*/

/*
* 此题判题点输入超出cmd限制
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

bool isBST(BSTree bst) {
	bool ret = true, _ret = true;
	if (bst == NULL) return true;
	if (bst->lchild != NULL) {
		if (bst->data < bst->lchild->data) {
			std::cout << "out!";
			return false;
		}
		ret = isBST(bst->lchild);
	}
	if (bst->rchild != NULL) {
		if (bst->data > bst->rchild->data) {
			std::cout << "out!";
			return false;
		}
		_ret = isBST(bst->rchild);
	}
	return (ret && _ret);
}


int main() {
	std::cin >> str;
	BSTree bst = createTree(str);
	std::cout << (isBST(bst) ? "yes" : "no") << std::endl;
}

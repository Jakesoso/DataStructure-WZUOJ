/*
* 3097-二叉搜索树查找
* 给定一个二叉搜索树（广义表形式）以及某个整数x，检查x是否在二叉搜索树上。
* 输入：输入第一行是二叉搜索树的的广义表表示。该行最长不超过2000000个字符。
*      第二行是一个正整数n，表示有n个测试。接下来每行一个整数x。
* 输出：输出总共n行，如果x在二叉搜索树上，输出yes，否则输出no。
*/


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/*
* 此题最后一个判题点用cin会超时，需要用scanf
*/

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

bool isOnBST(BSTree bst, int x) {
	Node* p = bst;
	while (p != NULL) {
		if (p->data > x)		p = p->lchild;
		else if (p->data < x)		p = p->rchild;
		else						return true;
	}
	return false;
}

int main() {
	std::cin >> str;
	//scanf("%s", str);	判题时用scanf
	BSTree bst = createTree(str);
	int k, num;
	std::cin >> k;
	while (k--) {
		std::cin >> num;
		std::cout << (isOnBST(bst, num) ? "yes" : "no") << std::endl;
	}

}

#include "DataStructure-OJ.hpp"
using namespace std;

typedef char ElementType;
typedef struct Node{
    ElementType data;
    struct Node *lchild;
    struct Node *rchild;
}BTNode,*BTree;

const int MAX_NODE = 100;

BTree createNode(ElementType data, BTree lchild, BTree rchild) {
	BTree node = (BTree)malloc(sizeof(BTNode));
	node->data = data;
	node->lchild = lchild;
	node->rchild = rchild;
	return node;
}

BTree createTree(char s[]) {
	enum STATUS{
		UNDEFINED, ON_LEFT, ON_RIGHT,
	}; 
	int status = UNDEFINED;
	// nodes list which are working on
	BTree curr_node[MAX_NODE] = { NULL };
	// the node index which is working on
	int i = -1;
	BTree new_node = NULL;
	char* str = s;
	
	while(*str != '\0') {
		if(isalpha(*str)) {
			new_node = createNode(*str, NULL, NULL);
			// working on left child
			if(status == ON_LEFT) {
				curr_node[i]->lchild = new_node;
			}
			// working on right child
			if(status == ON_RIGHT) {
				curr_node[i]->rchild = new_node;
			}
		}
		// begin working on next node
		else if(*str == '(') {
			status = ON_LEFT;
			i++;
			curr_node[i] = new_node;
		} 
		else if(*str == ',') {
			status = ON_RIGHT;
		} 
		// finish current node
		else if(*str == ')') {
			i--;
		} 
		str++;
	}
	
	// only has one node
	if(curr_node[0] == NULL) {
		curr_node[0] = new_node;
	} 
	return curr_node[0];
}

int find_lastRightParen(char s[], int left, int right) {
	for (int i = right; i >= left; i--) {
		if (s[i] == ')')	return i;
	}
	return -1;
}

int find_mid(char s[], int left, int right) {
	int layer = 0;
	for (int i = left; i <= right; i++) {
		if (s[i] == '(')					layer++;
		else if (s[i] == ')')				layer--;
		else if (s[i] == ',' && layer == 1)	return i;
	}
	return -1;
}

BTree createTree_recursion(char s[], int left, int right) {
	// head node
	BTree head_node = createNode(s[left], NULL, NULL);
	
	// only one node
	if (left == right)	return head_node;

	int pos_leftParen = left + 1;
	int pos_rightparen = find_lastRightParen(s, left, right);
	int pos_mid = find_mid(s, left, right);

	// set left child
	if (isalpha(s[pos_leftParen + 1])) {
		head_node->lchild = createTree_recursion(s, pos_leftParen + 1, pos_mid - 1);
	}

	// set right child
	if (isalpha(s[pos_mid + 1])) {
		head_node->rchild = createTree_recursion(s, pos_mid + 1, pos_rightparen - 1);
	}
	return head_node;
}

// recursion
void preOrder(BTree bt) {
	if(bt != NULL) {
		cout << bt->data;
		preOrder(bt->lchild);
		preOrder(bt->rchild);
	}
}

void inOrder(BTree rt) {
	if(rt != NULL) {
		inOrder(rt->lchild);
		cout << rt->data;
		inOrder(rt->rchild);
	}
}

void postOrder(BTree rt) {
	if(rt != NULL) {
		postOrder(rt->lchild);
		postOrder(rt->rchild);
		cout << rt->data;
	}
}

// bfs
void layerOrder(BTree rt) {
	queue<BTree> q;
	BTree node;
	
	q.push(rt);
	while(!q.empty()) {
		node = q.front(), q.pop();
		cout << node->data;
		
		if(node->lchild != NULL) {
			q.push(node->lchild);
		}
		if(node->rchild != NULL) {
			q.push(node->rchild);
		}
	}
}

void printTree(BTree bt) {
	if(bt != NULL) {
		cout << bt->data;
		if(bt->lchild != NULL || bt->rchild != NULL) {
			cout << '(';
			printTree(bt->lchild);
			cout << ',';
			printTree(bt->rchild);
			cout << ')';
		}
	}
}

void destroyTree(BTree bt) {
	if (bt->rchild != NULL)	destroyTree(bt->rchild);
	if (bt->lchild != NULL)	destroyTree(bt->lchild);
	free(bt);
}

int main() {
	char* arr = (char*)"A(B(D,),C(E,F(,H)))";
	BTree bt =  createTree_recursion(arr, 0, strlen(arr));
	//BTree bt = createTree_recursion(arr, 0, 0);
	destroyTree(bt);
}
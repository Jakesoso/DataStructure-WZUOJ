#include "DataStructure-OJ.hpp"
using namespace std;

typedef int ElementType;

typedef struct Node{
	ElementType data;
	struct Node  *next;
}Node, *LinkList;

LinkList createList() {
	LinkList L = (LinkList)malloc(sizeof(Node));
	L->next = NULL;
	return L;
}

void printList(LinkList L) {
	LinkList p = L->next;
	while(p != NULL) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

int getLength(LinkList L) {
	int length = 0;
	LinkList p = L->next;
	while(p != NULL) {
		length++;
		p = p->next;
	}
	return length;
}

void insertHead(LinkList L, ElementType x) {
	// create node
	LinkList node = (LinkList)malloc(sizeof(Node));
	node->data = x;
	
	// insert into list
	node->next = L->next;
	L->next = node;
}

void insertTail(LinkList L, ElementType x) {
	// create node
	LinkList node = (LinkList)malloc(sizeof(Node));
	node->data = x;
	node->next = NULL;
	
	// find the insert position
	LinkList pre = L;
	while(pre->next != NULL)
		pre = pre->next;
		
	// insert into list
	pre->next = node;
}

int insertList(LinkList L, int i, ElementType x) {	
	// check the index i
	int length = getLength(L);
	if(i < 1 || i > length + 1)
		return 0;
	
	// create node
	LinkList node = (LinkList)malloc(sizeof(Node));
	if(node == NULL) 
		return 0;
	node->data = x;
	
	// locate to the insert position(pre)
	LinkList pre = L;
	for(int k = 1; k < i; k++) {
		pre = pre->next;
	}
	
	// insert into list
	if(i == length + 1)
		insertTail(L, x);
	else{
		node->next = pre->next;
		pre->next = node;
	}
	
	return 1;
}

Node* find(LinkList L, ElementType x) {
	LinkList p = L->next;
	LinkList res = NULL;
	
	while(p != NULL) {
		if(p->data == x) {
			res = p;
			break;
		}
		p = p->next;
	}
	
	return res;
}

Node* locate(LinkList L, int i) {
	// check the index i
	int length = getLength(L);
	if(i < 1 || i > length + 1)
		return NULL;
	
	// locate to the insert position(pre)
	LinkList p = L;
	for(int k = 0; k < i; k++) {
		p = p->next;
	}
	
	return p;
}

int delNode(LinkList L, ElementType x) {
	// find the pre of x
	LinkList pre = L;
	
	while(pre->next != NULL) {
		if(pre->next->data == x)
			break;
		pre = pre->next;
	}
	
	if(pre->next == NULL)
		return 0;
	
	// delete
	pre->next = pre->next->next;
	return 1;
}

// save the delete element
int delNode(LinkList L, int i, ElementType *px) {
	// check the index i
	int length = getLength(L);
	if(i < 1 || i > length)
		return 0;
	
	// locate to the insert position(pre)
	LinkList pre = L;
	for(int k = 1; k < i; k++) {
		pre = pre->next;
	}
	
	// save
	*px = pre->next->data;
	
	// delete
	pre->next = pre->next->next;
	return 1;
}

void clearList(LinkList L) {
	LinkList pre = L->next;
	LinkList p = pre->next;
	
	while(p != NULL) {
		free(pre);
		pre = p;
		p = p->next;
	}
	L->next = NULL;
}

void destroyList(LinkList L) {
	clearList(L);
	free(L);
}
#include "DataStructure-OJ.hpp"
using namespace std; 

typedef int ElementType;
typedef struct Node
{
    ElementType data;
    struct Node *next;
} Node, *LinkStack;

LinkStack createStack() {
	LinkStack S = (LinkStack)malloc(sizeof(Node));
	S->next = NULL;
	return S;
}

int push(LinkStack S, ElementType x) {
	LinkStack node = (LinkStack)malloc(sizeof(Node));
	if(node == NULL) {
		return 0;
	}
	node->data = x;
	node->next = S->next;
	S->next = node;
	return 1;
}

int empty(LinkStack S) {
	return (S->next == NULL) ? 1 : 0;
}

int pop(LinkStack S) {
	if(empty(S)) {
		return 0;
	}
	LinkStack node = S->next;
	S->next = node->next;
	free(node);
	return 1;
}

ElementType getTop(LinkStack S) {
	return S->next->data;
}

void clearStack(LinkStack S) {
	while(!empty(S)) {
		pop(S);
	}
}

void destroyStack(LinkStack S) {
	clearStack(S);
	free(S);
}

#include "DataStructure-OJ.hpp"
using namespace std; 

typedef int ElementType;
typedef struct Node{
    ElementType data;
    struct Node *next;
} QNode;
typedef struct{
    QNode *front; //¶ÓÊ×
    QNode *rear;  //¶ÓÎ²
} LinkQueue;

LinkQueue* createQueue() {
	LinkQueue* Q = (LinkQueue*)malloc(sizeof(LinkQueue));
	Q->front = NULL;
	Q->rear = NULL;
	
	return Q;
}

int push(LinkQueue *Q, ElementType x) {
	QNode* node = (QNode*)malloc(sizeof(QNode));
	if(node == NULL) {
		return 0;
	}
	
	node->data = x;
	node->next = NULL;
	
	// for empty queue
	if(Q->front == NULL) {
		Q->front = node;
		Q->rear = node;
	}
	else{
		Q->rear->next = node;
		Q->rear = node;
	}
	return 1; 
}

int empty(LinkQueue *Q) {
	return (Q->front == NULL) ? 1 : 0;
}

int pop(LinkQueue *Q) {
	if(empty(Q)) {
		return 0;
	}
	QNode* p = Q->front;
	Q->front = p->next;
	free(p);
	// if delete last node
	if(Q->front == NULL) {
		Q->rear = NULL;
	}
	return 1;
}

ElementType front(LinkQueue *Q) {
	return Q->front->data;
}

void clearQueue(LinkQueue *Q) {
	if(empty(Q)) {
		return;
	}
	QNode* pre = Q->front;
	QNode* p = pre->next;
	while(p != NULL) {
		free(pre);
		pre = p;
		p = p->next;
	} 
	Q->front = NULL;
	Q->rear = NULL;
}

void destroyQueue(LinkQueue *Q) {
	while(Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	//Q->front = NULL;
	//Q->rear = NULL;
	//free(Q);
}


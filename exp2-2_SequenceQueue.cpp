#include "DataStructure-OJ.hpp"
using namespace std;

typedef int ElementType;
typedef struct{
	ElementType *array;
	int front;      //队首位置
	int rear;       //尾指下一个位置
	int length;     //长度
	int capacity;   //总容量
}SeqQueue;

SeqQueue* createQueue(int capacity) {
	SeqQueue* Q = (SeqQueue*)malloc(sizeof(SeqQueue));
	Q->array = (ElementType*)malloc(capacity * sizeof(ElementType));
	Q->front = 0;
	Q->rear = 0;
	Q->length = 0;
	Q->capacity = capacity;
	return Q;
}

int full(SeqQueue *Q) {
	return Q->length == Q->capacity;
}

int push(SeqQueue *Q, ElementType x) {
	if(full(Q)) {
		return 0;
	}
	Q->array[Q->rear] = x;
	Q->rear = (Q->rear + 1) % Q->capacity;
	Q->length++;
	return 1;
}

int empty(SeqQueue *Q) {
	return Q->length == 0 ? 1 : 0;
}

int pop(SeqQueue *Q, ElementType *x) {
	if(empty(Q)) {
		return 0;
	}
	*x = Q->array[Q->front];
	Q->length--;
	Q->front = (Q->front + 1) % Q->capacity;
	return 1;
}

ElementType front(SeqQueue *Q) {
	return Q->array[Q->front];
}

void clearQueue(SeqQueue *Q) {
	Q->length = 0;
	Q->front = 0;
	Q->rear = 0;
}

void destroyQueue(SeqQueue *Q) {
	free(Q->array);
	free(Q);
}
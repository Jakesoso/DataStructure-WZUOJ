#include "DataStructure-OJ.hpp"
using namespace std;

typedef int ElementType;
typedef struct{
	ElementType *array; //存放数据的指针
	int length;	 		//已有数据个数
	int capacity;  		//容量
}SeqList;

SeqList* createList(int capacity) {
	SeqList* L = (SeqList*)malloc(sizeof(SeqList));
	
	L->capacity = capacity;
	L->length = 0;
	L->array = (ElementType*)malloc(capacity * sizeof(ElementType));
	
	return L;
}

void destroyList(SeqList *L) {
	free(L->array);
	free(L);
}

int isEmpty(SeqList *L) {
	return (L->length > 0) ? 0 : 1;
}

void printList(SeqList *L) {
	int length = L->length;
	ElementType* head = L->array;
	
	for(int i = 0; i < length; i++) {
		cout << *(head+i) << " ";
	}
	cout << endl;
}

int getLength(SeqList *L) {
	return L->length;
}

int insertList(SeqList *L, int i, ElementType x) {
	int cap = L->capacity;
	int len = L->length;
	ElementType* arr = L->array;
	
	if(i < 1 || i-1 > len || cap == len)
		return 0;
	for(int k = len - 1; k >= i - 1; k--) {
	}
	arr[i-1] = x;
	L->length++;
	
	return 1; 
}

void mergeList(SeqList *LA, SeqList *LB, SeqList *LC) {
	ElementType* arr_a = LA->array;
	ElementType* arr_b = LB->array;
	int i = 0, j = 0;
	
	while(i < LA->length || j < LB->length) {
		if(i >= LA->length) {
			//insertList(LC, i+j+1, arr_b[j]);
			LC->array[i+j] =  arr_b[j];
			j++;
		}
		if(j >= LB->length) {
			//insertList(LC, i+j+1, arr_a[i]);
			LC->array[i+j] =  arr_a[i];
			i++;
		}
		else{
			if(arr_a[i] < arr_b[j]) {
				//insertList(LC, i+j+1, arr_a[i]);
				LC->array[i+j] =  arr_a[i];
				i++;
			}
			else{
				//insertList(LC, i+j+1, arr_b[j]);
				LC->array[i+j] =  arr_b[j];
				j++;
			}
		}
		LC->length++;
	}	
}


int find(SeqList *L, ElementType x) {
	for(int i = 0; i < L->length; i++) {
		if(x == L->array[i]) return i+1;
	}
	return -1;
}

int getElement(SeqList *L, int i, ElementType *p) {
	int cap = L->capacity;
	int len = L->length;
	
	if(i < 1 || i > len)
		return 0;
	*p = L->array[i-1];
	return 1;
}

int delElement(SeqList *L, int i, ElementType *p) {
	int cap = L->capacity;
	int len = L->length;
	
	// getElement
	if(i < 1 || i > len)
		return 0;
	*p = L->array[i-1];
	
	// delete
	for(int k = i; k < len; k++)
		L->array[k-1] = L->array[k];
	L->length--;
	
	return 1;	
}

void delRepeatElement(SeqList *L) {
	ElementType *p = (ElementType*)malloc(sizeof(ElementType));
	
	for(int i = 0; i < L->length; i++) {
		for(int j = 0; j < i; j++) {
			if(L->array[j] == L->array[i]) {	
				delElement(L, i+1, p);
				i--;
				break;
			}
		}
	}
}

void clearList(SeqList *L) {
	L->length = 0;
}

/* FOR OJ TEST*/
//int main()
//{
//	int size_a, size_b;
//	cin >> size_a;
//	
//    SeqList *a=createList(size_a);
//    for(int i = 1; i <= size_a; i++) {
//    	int n;
//    	cin >> n;
//    	insertList(a, i, n);
//	}
//	
//	cin >> size_b;
//	
//    SeqList *b=createList(size_b);
//    for(int i = 1; i <= size_b; i++) {
//    	int n;
//    	cin >> n;
//    	insertList(b, i, n);
//	}
//	
//	SeqList *c=createList(size_a+size_b);
//	
//	mergeList(a, b, c);
//	
//	printList(c);
//	
//	
//    
//}




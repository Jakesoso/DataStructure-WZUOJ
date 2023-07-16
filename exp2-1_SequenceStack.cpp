#include "DataStructure-OJ.hpp"
using namespace std;

typedef int ElementType;
typedef struct{
    ElementType *array; //存放栈数据
    int top;	 		//栈顶
    int capacity;  		//容量
} SeqStack;

SeqStack* createStack(int capacity) {
	SeqStack* S = (SeqStack*)malloc(sizeof(SeqStack));
	S->top = -1;
	S->capacity = capacity;
	S->array = (ElementType*)malloc(capacity * sizeof(ElementType));
	return S;
}

int full(SeqStack *S) {
	return S->top == S->capacity - 1;
}

int push(SeqStack *S, ElementType x) {
	if(full(S)) {
		return 0;
	}	
	S->top++;
	S->array[S->top] = x;
	return 1;
}

int empty(SeqStack *S) {
	return (S->top == -1) ? 1 : 0;
}

int pop(SeqStack *S) {
	if(empty(S)) {
		return 0;
	}
	S->top--;
	return 1;
}

ElementType top(SeqStack *S) {
	return S->array[S->top];
}

void clearStack(SeqStack *S) {
	S->top = -1;
}

void destroyStack(SeqStack *S) {
	free(S->array);
	free(S);
}

int match_brackets(char a, char b) {
	if(a == '(' && b == ')' || b == '(' && a == ')')
		return 1;
	if(a == '[' && b == ']' || b == '[' && a == ']')
		return 1;
	if(a == '{' && b == '}' || b == '{' && a == '}')
		return 1;
	return 0;
}

void vaild_brackets() {
	char ch;
	SeqStack *S = createStack(1000);
	while(cin >> ch) {
		if(empty(S)) {
			push(S, ch);
		}
		else{
			if(match_brackets(ch, top(S))) {
				pop(S);
			}
			else{
				push(S, ch);
			}
		}
	}
	if(empty(S)) {
		cout << "yes\n";
	}
	else{
		cout << "no\n";
	}
}

int to_int(char ch) {
	return int(ch) - '0';
}

int operate(int a, int b, char op) {
	switch(op) {
		case '+':
			return a + b;
			break;
		case '-':
			return a - b;
			break;
		case '*':
			return a * b;
			break;
		case '/':
			return a / b;
			break;
	}
}

void rpn() {
	SeqStack *S = createStack(100);
	char ch;
	int a, b;
	
	while(cin >> ch) {
		if(isdigit(ch)) {
			push(S, to_int(ch));
		}
		else{
			a = top(S), pop(S);
			b = top(S), pop(S);
			push(S, operate(b, a, ch));
		}
	}
	
	cout << top(S) << endl;
}

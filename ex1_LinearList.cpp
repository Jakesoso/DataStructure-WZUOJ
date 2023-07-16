#include "DataStructure-OJ.hpp"
using namespace std;

typedef struct Node{
    int  coef;	//系数(coefficient)
    int  exp;	//指数(exponent)
    struct Node* next;
} PolyNode, *PolyList;

PolyList createList() {
    PolyList L = (PolyList)malloc(sizeof(PolyNode));
    L->next = NULL;
    return L;
}

void insertTail(PolyList L, int coef, int exp) {
	// create node
	PolyList node = (PolyList)malloc(sizeof(Node));
	node->coef = coef;
	node->exp = exp;
	node->next = NULL;

	// find the insert position
	PolyList pre = L;
	while (pre->next != NULL)
		pre = pre->next;

	// insert into list
	pre->next = node;
}

void printList(PolyList L) {
	PolyList p = L->next;
	int flag = 0;
	
	// check the list
	// if empty print "0"
	if (p == NULL) {
		cout << 0 << endl;
		return;
	}
	while (p != NULL) {
		int coef = p->coef;
		int exp = p->exp;
		
		// 0x^k == 0
		if(coef != 0) {
			// symbol
			if(coef > 0 && flag) {
				cout << "+";
			}
			else if(coef < 0) {
				cout << "-";
			}
			
			// coef
			// 1*x == x but not for 1*x^0
			if(abs(coef) != 1 || exp == 0) {
				cout << abs(coef);
			}
			
			// exp
			if(exp == 1) {
				cout << "x";
			} 
			// exp != 1 && exp != 0
			else if(exp != 0) {
				cout << "x^" << exp;
			}
			
		}
		// next node
		p = p->next;
		flag = 1;
	}
	cout << endl;
}

void derivative(PolyList L) {
	PolyList p = L->next;
	PolyList pre = L;
	while (p != NULL) {
		// (k*x^0)dx = 0
		if (p->exp != 0) {
			p->coef = p->coef * p->exp;
			p->exp -= 1;
		}
		else {
			pre->next = NULL;
			free(p);
			break;
		}
		pre = p;
		p = p->next;
	}
}

void polyAdd(PolyList LA, PolyList LB,PolyList LC) {
	PolyList pa = LA->next;
	PolyList pb = LB->next;
	while(pa != NULL && pb != NULL) {
		if(pa->exp == pb->exp) {
			if(pa->coef + pb->coef != 0) {
				insertTail(LC, pa->coef + pb->coef, pa->exp);
			}
			pa = pa->next, pb = pb->next;
		}
		else if(pa->exp > pb->exp) {
			insertTail(LC, pa->coef, pa->exp);
			pa = pa->next;
		}
		else{
			insertTail(LC, pb->coef, pb->exp);
			pb = pb->next;
		}
	}
	
	while(pa == NULL && pb != NULL) {
		insertTail(LC, pb->coef, pb->exp);
		pb = pb->next;
	}
	
	while(pb == NULL && pa != NULL) {
		insertTail(LC, pa->coef, pa->exp);
		pa = pa->next;
	}
}

void polySub(PolyList LA, PolyList LB,PolyList LC) {
	PolyList pa = LA->next;
	PolyList pb = LB->next;
	while(pa != NULL && pb != NULL) {
		if(pa->exp == pb->exp) {
			if(pa->coef - pb->coef != 0) {
				insertTail(LC, pa->coef - pb->coef, pa->exp);
			}
			pa = pa->next, pb = pb->next;
		}
		else if(pa->exp > pb->exp) {
			insertTail(LC, pa->coef, pa->exp);
			pa = pa->next;
		}
		else{
			insertTail(LC, -pb->coef, pb->exp);
			pb = pb->next;
		}
	}
	
	while(pa == NULL && pb != NULL) {
		insertTail(LC, -pb->coef, pb->exp);
		pb = pb->next;
	}
	
	while(pb == NULL && pa != NULL) {
		insertTail(LC, pa->coef, pa->exp);
		pa = pa->next;
	}
}

int main() {
	PolyList LA = createList();
	PolyList LB = createList();
	PolyList LC = createList();
	int n, c, e;
	cin >> n;
	while(n--) {
		cin >> c >> e;
		insertTail(LA, c, e);
	}
	
	cin >> n;
	while(n--) {
		cin >> c >> e;
		insertTail(LB, c, e);
	}
	polyAdd(LA,LB,LC);
	//derivative(L);
	printList(LC);
	
} 

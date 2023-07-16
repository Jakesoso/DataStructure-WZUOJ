/*
* 3131-�ϲ�����
* ����һ��������n����n���ˣ���ŷֱ�Ϊ0,1,2...n-1���տ�ʼÿ���˶���һֻ���顣
* ���ڽ���m�κϲ���������x��y���ڵ���ֻ����ϲ���������֪���������˸���x��y�Ƿ���ͬһֻ���顣
* ���룺�����һ����һ��������n(n<=100000).
*       �ڶ�����һ��������m(m<=100000)��
*       ������m��ÿ������������x��y(0<x,y<n)����ʾ��x��y���ڵĶ���ϲ���
*       �ٽ�������һ��������k����ʾ��k����ѯ��
*       ���k��ÿ������������a��b(0<a,b<n)����ʾ��Ҫ��ѯa��b�Ƿ���ͬһֻ���顣
* ���������ܹ�k�У�ÿ����ѯ���һ�У����a��b��ͬһֻ�������yes���������no��
*/

#include <iostream>
#include <stdlib.h>

typedef int ElementType;
typedef struct {
    int* parent;
    int size;
}SNode, * Set;

Set createSet(int size) {
    int* parent = (int*)malloc(size * sizeof(int));
    Set set = (Set)malloc(sizeof(SNode));
    set->parent = parent;
    set->size = size;
    return set;
}

void initSet(Set S) {
    for (int i = 0; i < S->size; i++)
        //S->parent[i] = -1;
        // ���ڵ�ĸ��׾�Ϊ�Լ�
        S->parent[i] = i;
}

int findSet(Set S, int x) {
    if (x < 0 || x >= S->size)  return  -1;
    //if (S->parent[x] == -1)     return  x;
    if (S->parent[x] == x)      return  x;
    S->parent[x] = findSet(S, S->parent[x]);
}

void unionSet(Set S, int x, int y) {
    int rootX = findSet(S, x), rootY = findSet(S, y);
    if (rootX != rootY) {
        S->parent[rootX] = rootY;
    }
}

bool isTogether(Set S, int x, int y) {
    int rootX = findSet(S, x), rootY = findSet(S, y);
    if (rootX != rootY) return false;
    else return true;
}

int main() {
    // m, k ���� x, y�ϲ� a, b��ѯ
    int n, m, k, x, y, a, b;

    // create
    std::cin >> n;
    Set s = createSet(n);
    initSet(s);

    // union
    std::cin >> m;
    while (m--) {
        std::cin >> x >> y;
        unionSet(s, x, y);
    }

    // find
    std::cin >> k;
    while (k--) {
        std::cin >> a >> b;
        std::cout << (isTogether(s, a, b) ? "yes" : "no") << std::endl;
    }
    return 0;
}
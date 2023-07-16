#include "DataStructure-OJ.hpp"

typedef int ElementType;
typedef struct {
    int* parent;
    int size;
}SNode, * Set;

/*
* �����Set createSet(int size)������
* �ú�����������Ϊsize�Ĳ��鼯�����ظò��鼯�� 
*/
Set createSet(int size) {
    int* parent = (int*)malloc(size * sizeof(int));
    Set set = (Set)malloc(sizeof(SNode));
    set->parent = parent;
    set->size = size;
    return set;
}

/*
* �����void initSet(Set S)������ 
* �ú�����ʼ�����鼯S���������ڵ��parentΪ-1�� 
*/
void initSet(Set S) {
    for (int i = 0; i < S->size; i++) 
        S->parent[i] = -1;
}

/*
* �����int findSet(Set S,int x)������
* �ú������ҽڵ�x�ĸ��ڵ㣬�����ظ��ڵ��š�
* �ڲ��ҹ�����ͬʱѹ��·����
* ���и��ڵ��parentΪ-1.
*/
int findSet(Set S, int x) {
    // invalid x
    if (x < 0 || x >= S->size)  return  -1;
    if (S->parent[x] == -1)     return  x;
    S->parent[x] = findSet(S, S->parent[x]);
}

/*
* �����void unionSet(Set S,int x,int y)������ 
* �ú�����x��y���ڵ���������(����)�ϲ���
*/
void unionSet(Set S, int x, int y) {
    // ����ͨ
    int rootX = findSet(S, x), rootY = findSet(S, y);
    if (rootX != rootY) {
        S->parent[rootX] = rootY;
    }
}

/*
* �����void destroySet(Set S)������ 
* �ú������ٲ��鼯S��
*/
void destroySet(Set S) {
    free(S->parent);
    free(S);
}

int main() {
    
    return 0;
}
#include "DataStructure-OJ.hpp"

typedef int ElementType;
typedef struct {
    int* parent;
    int size;
}SNode, * Set;

/*
* 请设计Set createSet(int size)函数。
* 该函数创建容量为size的并查集并返回该并查集。 
*/
Set createSet(int size) {
    int* parent = (int*)malloc(size * sizeof(int));
    Set set = (Set)malloc(sizeof(SNode));
    set->parent = parent;
    set->size = size;
    return set;
}

/*
* 请设计void initSet(Set S)函数。 
* 该函数初始化并查集S，子树根节点的parent为-1。 
*/
void initSet(Set S) {
    for (int i = 0; i < S->size; i++) 
        S->parent[i] = -1;
}

/*
* 请设计int findSet(Set S,int x)函数。
* 该函数查找节点x的根节点，并返回根节点编号。
* 在查找过程中同时压缩路径。
* 其中根节点的parent为-1.
*/
int findSet(Set S, int x) {
    // invalid x
    if (x < 0 || x >= S->size)  return  -1;
    if (S->parent[x] == -1)     return  x;
    S->parent[x] = findSet(S, S->parent[x]);
}

/*
* 请设计void unionSet(Set S,int x,int y)函数。 
* 该函数将x和y所在的两个集合(子树)合并。
*/
void unionSet(Set S, int x, int y) {
    // 不连通
    int rootX = findSet(S, x), rootY = findSet(S, y);
    if (rootX != rootY) {
        S->parent[rootX] = rootY;
    }
}

/*
* 请设计void destroySet(Set S)函数。 
* 该函数销毁并查集S。
*/
void destroySet(Set S) {
    free(S->parent);
    free(S);
}

int main() {
    
    return 0;
}
/*
* 3131-合并队伍
* 给定一个正整数n，有n个人，编号分别为0,1,2...n-1，刚开始每个人独立一只队伍。
* 现在进行m次合并操作，把x和y所在的两只队伍合并。现在想知道任意两人个人x和y是否在同一只队伍。
* 输入：输入第一行是一个正整数n(n<=100000).
*       第二行是一个正整数m(m<=100000)。
*       接下来m行每行两个正整数x和y(0<x,y<n)，表示把x和y所在的队伍合并。
*       再接下来是一个正整数k，表示有k个查询。
*       最后k行每行两个正整数a和b(0<a,b<n)，表示需要查询a和b是否在同一只队伍。
* 输出：输出总共k行，每个查询输出一行，如果a和b在同一只队伍输出yes，否则输出no。
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
        // 根节点的父亲就为自己
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
    // m, k 次数 x, y合并 a, b查询
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
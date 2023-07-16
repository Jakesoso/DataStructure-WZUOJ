#include "DataStructure-OJ.hpp"

#define MAXVEX 1000         //最大顶点数
typedef char VertexType;

typedef struct ENode {
    int adjVertex;          //该边所指的顶点编号
    int weight;             //边权
    struct ENode* nextEdge; //下一条边
} ENode;

typedef struct VNode {
    VertexType data;        //顶点信息
    int visited;            //遍历标记. 1:已遍历  0:未遍历
    ENode* firstEdge;       //第一条出边
} VNode;

typedef struct {
    VNode vexs[MAXVEX];
    int vertexNum, edgeNum; //点数和边数
}AdjGraph, * Graph;

/*
* 该函数创建一个空图并返回。
*/
Graph createGraph() {
    Graph g = (Graph)malloc(sizeof(AdjGraph));
    g->edgeNum = 0, g->vertexNum = 0;
    return g;
}

/*
* 该函数在图个中找顶点v并返回其编号，如果不存在则返回-1。
*/
int locateVertex(Graph g, VertexType v) {
    for (int i = 0; i < g->vertexNum; i++) {
        if (v == g->vexs[i].data) 
            return i;
    }
    return -1;
}

/*
* 该函数在图g中增加顶点v（放在最后），如果已存在则什么都不做。
*/
void addVertex(Graph g, VertexType v) {
    if (locateVertex(g, v) != -1) return;

    int last_index = g->vertexNum;
    g->vexs[last_index].data = v;
    g->vexs[last_index].firstEdge = NULL;
    g->vertexNum++;
}

/*
* 该函数在图g中查找第i号顶点到第j号顶点的边，并返回其指针。
* 如果找不到返回空指针。已知第i和j号顶点在图中。
*/
ENode* findEdge(Graph g, int i, int j) {
    ENode* p;
    for (p = g->vexs[i].firstEdge;
        p != NULL && p->adjVertex != j;
        p = p->nextEdge);
    return p;
}

/*
* 该函数在图g插入边v1v2（权为w）。插入的边结点作为边链表的第1个结点。
* 如果顶点不存在，则什么也不做。如果待插入的边已存在, 存储小权值。
*/
void addEdge(Graph g, VertexType v1, VertexType v2, int w) {
    // find the position of vertex
    int v1_pos = locateVertex(g, v1);
    int v2_pos = locateVertex(g, v2);
    if (v1_pos == -1 || v2_pos == -1) return;
    
    // find edge
    ENode *e1, *e2;
    for (e1 = g->vexs[v1_pos].firstEdge; 
        e1 != NULL && e1->adjVertex != v2_pos; e1 = e1->nextEdge);
    for (e2 = g->vexs[v2_pos].firstEdge; 
        e2 != NULL && e2->adjVertex != v1_pos; e2 = e2->nextEdge);

    // if edge already existed
    if (e1 != NULL && e2 != NULL) {
        e1->weight = e2->weight = std::min(e1->weight, w);
        return;
    }

    // edge not exist
    e1 = (ENode*)malloc(sizeof(ENode)), e2 = (ENode*)malloc(sizeof(ENode));
    e1->weight = e2->weight = w;
    e1->adjVertex = v2_pos, e2->adjVertex = v1_pos;
    e1->nextEdge = g->vexs[v1_pos].firstEdge, e2->nextEdge = g->vexs[v2_pos].firstEdge;
    g->vexs[v1_pos].firstEdge = e1, g->vexs[v2_pos].firstEdge = e2;
    g->edgeNum++;
}

/*
* 该函数返回图g中顶点v的度，已知顶点在图中。 
*/
int degree(Graph g, VertexType v) {
    int v_pos = locateVertex(g, v);
    int cnt = 0;

    for (ENode* e = g->vexs[v_pos].firstEdge; e != NULL; e = e->nextEdge) {
        cnt++;
    }
    return cnt;
}

/*
* 该函数在图g中删除边xy，如果删除不成功，则什么都不做。
*/
void delEdge(Graph g, VertexType x, VertexType y) {
    int x_pos = locateVertex(g, x);
    int y_pos = locateVertex(g, y);
    if (x_pos == -1 || y_pos == -1) return;

    ENode* x_e = g->vexs[x_pos].firstEdge, * pre;
    ENode* y_e = g->vexs[y_pos].firstEdge;
    // edge not exist
    if (x_e == NULL || y_e == NULL) return;

    // if first edge is right egde
    if (x_e->adjVertex == y_pos) {
        g->vexs[x_pos].firstEdge = x_e->nextEdge;
        free(x_e);
    }
    // find the right edge position and delete
    else {
        while (x_e != NULL && x_e->adjVertex != y_pos) {
            pre = x_e;
            x_e = x_e->nextEdge;
        }
        // not found
        if (x_e == NULL) return;
        pre->nextEdge = x_e->nextEdge;
        free(x_e);
    }

    if (y_e->adjVertex == x_pos) {
        g->vexs[y_pos].firstEdge = y_e->nextEdge;
        free(y_e);
    }
    // find the right edge position and delete
    else {
        while (y_e != NULL && y_e->adjVertex != x_pos) {
            pre = y_e;
            y_e = y_e->nextEdge;
        }
        // not found
        if (y_e == NULL) return;
        pre->nextEdge = y_e->nextEdge;
        free(y_e);
    }
    g->edgeNum--;
}

/*
* 该函数在图g中删除顶点v，如果删除不成功，则什么都不做。
*/
void delVertex(Graph g, VertexType v) {
    int v_pos = locateVertex(g, v);
    if (v_pos == -1) return;

    ENode *p = g->vexs[v_pos].firstEdge, *pre;
    
    // delete all the edges
    while (p != NULL) {
        pre = p;
        p = p->nextEdge;
        delEdge(g, g->vexs[pre->adjVertex].data, v);
    }

    // delete vertex
    g->vexs[v_pos] = g->vexs[g->vertexNum - 1];
    g->vertexNum--;

    for (int i = 0; i < g->vertexNum; i++) {
        p = g->vexs[i].firstEdge;
        while (p != NULL) {
            if (p->adjVertex == g->vertexNum) {
                p->adjVertex = v_pos;
            }
            p = p->nextEdge;
        }
    } 
}

/*
* 该函数从序号为i的节点开始，深度优先遍历g中的节点。已知i号节点一定在图中
*/
void DFS(Graph g, int i) {
    g->vexs[i].visited = 1;
    for (ENode* p = g->vexs[i].firstEdge; p != NULL; p = p->nextEdge) {
        if (g->vexs[p->adjVertex].visited) continue;
        DFS(g, p->adjVertex);
    }
}

/*
* 该函数从序号为i的节点开始，广度优先遍历g中的节点。已知i号节点一定在图中
*/
void BFS(Graph g, int i) {
    std::queue<int> q;

    q.push(i);
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        if (g->vexs[front].visited) continue;
        g->vexs[front].visited = 1;
        ENode* p = g->vexs[front].firstEdge;
        while (p != NULL) {
            if (!g->vexs[p->adjVertex].visited) {
                q.push(p->adjVertex);
            }
            p = p->nextEdge;
        }
    }
}

/*
* 该函数判断图g中两个点x和y是否连通，连通返回1，否则返回0。
*/
int connect(Graph g, VertexType x, VertexType y) {
    int x_pos = locateVertex(g, x);
    int y_pos = locateVertex(g, y);

    DFS(g, x_pos);
    return g->vexs[y_pos].visited;
}

/*
* 该函数返回图g的连通分支数。
*/
int connectedComps(Graph g) {
    int cnt = 0;
    for (int i = 0; i < g->vertexNum; i++) {
        if (g->vexs[i].visited) continue;
        cnt++;
        DFS(g, i);
    }
    return cnt;
}

/*
* 该函数销毁图g。
*/
void destroyGraph(Graph g) {
    for (int i = 0; i < g->vertexNum; i++) {
        ENode* p = g->vexs[i].firstEdge;
        ENode* pre = p;
        while (p != NULL) {
            pre = p;
            p = p->nextEdge;
            free(pre);
        }
    }
    free(g);
}

int main() {
    
    return 0;
}
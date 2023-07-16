#include "DataStructure-OJ.hpp"

#define MAXVEX 100
typedef char VertexType;
typedef int EdgeType;

typedef struct {
    VertexType vexs[MAXVEX];        //顶点表
    EdgeType edge[MAXVEX][MAXVEX];  //邻接矩阵 即边表
    int visited[MAXVEX];            //遍历标记 1:已遍历 0:未遍历
    int vertexNum, edgeNum;
}MGraph, * Graph;

/*
* 请设计Graph createGraph()函数。 
* 该函数创建一个空图，并返回图指针。 
*/
Graph createGraph() {
    Graph g = (Graph)malloc(sizeof(MGraph));
    g->edgeNum = 0, g->vertexNum = 0;
    return g;
}

/*
* 请设计int locateVertex(Graph g,VertexType v)函数。
* 该函数在图g中查找顶点v，并返回该顶点的下标。 如果图中无此顶点，返回-1。 
*/
int locateVertex(Graph g, VertexType v) {
    for (int i = 0; i < g->vertexNum; i++) {
        if (g->vexs[i] == v) return i;
    }
    return -1;
}

/*
* 请设计void addVertex(Graph g,VertexType v)函数。
* 该函数在图g中插入顶点v。
* 如果图中已经有该顶点，则什么都不做。 
* 如果图中不存在该顶点，则把该顶点插入到顶点表的最后。 
*/
void addVertex(Graph g, VertexType v) {
    if (locateVertex(g, v) != -1) return;
    int vnum = g->vertexNum;
    g->vexs[vnum] = v;
    g->vertexNum++;
    for (int i = 0; i < vnum; i++) {
        g->edge[i][vnum] = g->edge[vnum][i] = 0;
    }
}

/*
* 请设计void addEdge(Graph g, VertexType x, VertexType y)函数。 
* 该函数在图g中插入一条无向边(x,y)。 如果图中已经有该边或者顶点x、y不存在，则什么都不做。 
* 已知边的两个顶点是不同的顶点。
*/
void addEdge(Graph g, VertexType x, VertexType y) {
    int x_pos = locateVertex(g, x);
    int y_pos = locateVertex(g, y);

    if (x_pos == -1 || y_pos == -1) return;
    if (g->edge[x_pos][y_pos] == 1) return;
    g->edge[x_pos][y_pos] = g->edge[y_pos][x_pos] = 1;
    g->edgeNum++;
}

/*
* 请设计void delEdge(Graph g,VertexType x,VertexType y)函数。 
* 该函数在图g中删除边xy，如果图中无顶点x或者y或者没有边xy，则什么都不做。
* 已知边的两个顶点是不同的顶点。
*/
void delEdge(Graph g, VertexType x, VertexType y) {
    int x_pos = locateVertex(g, x);
    int y_pos = locateVertex(g, y);

    if (x_pos == -1 || y_pos == -1) return;
    if (g->edge[x_pos][y_pos] == 0) return;
    g->edge[x_pos][y_pos] = g->edge[y_pos][x_pos] = 0;
    g->edgeNum--;
}

/*
* 请设计void delVertex(Graph g,VertexType v)函数。 
* 该函数在图g中删顶点v，如果图中无顶点v，则什么都不做。
*/
void delVertex(Graph g, VertexType v) {
    int v_pos = locateVertex(g, v);
    if (v_pos == -1) return;
    // delete vertex
    g->vexs[v_pos] = g->vexs[g->vertexNum - 1];
    g->vertexNum--;
    // delete relative edge
    for (int i = 0; i <= g->vertexNum; i++) {
        if (g->edge[v_pos][i]) g->edgeNum--;
    }
    // restore last vertax
    for (int i = 0; i < g->vertexNum; i++) {
        g->edge[v_pos][i] = g->edge[i][v_pos] = g->edge[i][g->vertexNum];
    }
}

/*
* 请设计int degree(Graph g,VertexType v)函数。 
* 该函数返回顶点v的度，已知顶点在图中。
*/
int degree(Graph g, VertexType v) {
    int v_pos = locateVertex(g, v);
    if (v_pos == -1) return -1;

    int cnt = 0;
    for (int i = 0; i < g->vertexNum; i++) {
        if (g->edge[v_pos][i]) {
            cnt++;
        }
    }
    return cnt;
}

/*
* 请设计void DFS(Graph g, int i)函数。 
* 该函数从序号为i的顶点开始深度优先遍历图G(已遍历的点visited值标记为1)。
* 已知未遍历的点visited值标记为0。
*/
void DFS(Graph g, int i) {
    g->visited[i] = 1;
    for (int j = 0; j < g->vertexNum; j++) {
        if (g->visited[j] || !g->edge[i][j])
            continue;
        DFS(g, j);
    }
}

/*
* 请设计void BFS(Graph g, int i)函数。
* 该函数从序号为i的顶点开始广度优先遍历图G(已遍历的点visited值标记为1)。
*/
void BFS(Graph g, int i) {
    std::queue<int> q;
    int front;

    q.push(i);
    while (!q.empty()) {
        front = q.front(), q.pop();
        if (g->visited[front]) continue;

        g->visited[front] = 1;
        for (int j = 0; j < g->vertexNum; j++) {
            if (g->edge[front][j]) q.push(j);
        }
    }
}


/*
* 请设计int connect(Graph g, VertexType v, VertexType u)函数。
* 该函数判断图中两个顶点v和w是否连通，连通返回1，不连通返回0。
*/
int connect(Graph g, VertexType v, VertexType u) {
    int v_pos = locateVertex(g, v);
    int u_pos = locateVertex(g, u);

    DFS(g, v_pos);
    return g->visited[u_pos];
}

/*
* 请设计int connectedComps(Graph g)函数。
* 该函数返回图g的连通分支数。
*/
int connectedComps(Graph g) {
    int cnt = 0;
    for (int i = 0; i < g->vertexNum; i++) {
        if (g->visited[i]) continue;
        BFS(g, i);
        cnt++;
    }
    return cnt;
}

/*
* 请设计int distance(Graph g,VertexType v, VertexType u)函数。
* 该函数返回图中两个顶点v和w之间的距离(最短连通路上边的数目)。提示：连通返回距离，不连通返回0。
*/
int distance(Graph g, VertexType v, VertexType u) {
    std::queue<int> q;
    int dis[MAXVEX];
    memset(dis, -1, sizeof(dis));

    int v_pos = locateVertex(g, v);
    int u_pos = locateVertex(g, u);

    q.push(v_pos);
    dis[v_pos] = 0;
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        for (int i = 0; i < g->vertexNum; i++) {
            // not connectable
            if (g->edge[front][i] == 0 || dis[i] != -1) 
                continue;

            dis[i] = dis[front] + 1;
            q.push(i);
        }
    }
    if (dis[u_pos] == -1)   return 0;
    else                    return dis[u_pos];
}

/*
* 请设计void destroyGraph(Graph g)函数。
* 该函数销毁图g。
*/
void destroyGraph(Graph g) {
    free(g);
}

int main() {
    return 0;
}
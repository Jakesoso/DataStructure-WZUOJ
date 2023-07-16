#include "DataStructure-OJ.hpp"

#define MAXVEX 100
typedef char VertexType;
typedef int EdgeType;

typedef struct {
    VertexType vexs[MAXVEX];        //�����
    EdgeType edge[MAXVEX][MAXVEX];  //�ڽӾ��� ���߱�
    int visited[MAXVEX];            //������� 1:�ѱ��� 0:δ����
    int vertexNum, edgeNum;
}MGraph, * Graph;

/*
* �����Graph createGraph()������ 
* �ú�������һ����ͼ��������ͼָ�롣 
*/
Graph createGraph() {
    Graph g = (Graph)malloc(sizeof(MGraph));
    g->edgeNum = 0, g->vertexNum = 0;
    return g;
}

/*
* �����int locateVertex(Graph g,VertexType v)������
* �ú�����ͼg�в��Ҷ���v�������ظö�����±ꡣ ���ͼ���޴˶��㣬����-1�� 
*/
int locateVertex(Graph g, VertexType v) {
    for (int i = 0; i < g->vertexNum; i++) {
        if (g->vexs[i] == v) return i;
    }
    return -1;
}

/*
* �����void addVertex(Graph g,VertexType v)������
* �ú�����ͼg�в��붥��v��
* ���ͼ���Ѿ��иö��㣬��ʲô�������� 
* ���ͼ�в����ڸö��㣬��Ѹö�����뵽��������� 
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
* �����void addEdge(Graph g, VertexType x, VertexType y)������ 
* �ú�����ͼg�в���һ�������(x,y)�� ���ͼ���Ѿ��иñ߻��߶���x��y�����ڣ���ʲô�������� 
* ��֪�ߵ����������ǲ�ͬ�Ķ��㡣
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
* �����void delEdge(Graph g,VertexType x,VertexType y)������ 
* �ú�����ͼg��ɾ����xy�����ͼ���޶���x����y����û�б�xy����ʲô��������
* ��֪�ߵ����������ǲ�ͬ�Ķ��㡣
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
* �����void delVertex(Graph g,VertexType v)������ 
* �ú�����ͼg��ɾ����v�����ͼ���޶���v����ʲô��������
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
* �����int degree(Graph g,VertexType v)������ 
* �ú������ض���v�Ķȣ���֪������ͼ�С�
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
* �����void DFS(Graph g, int i)������ 
* �ú��������Ϊi�Ķ��㿪ʼ������ȱ���ͼG(�ѱ����ĵ�visitedֵ���Ϊ1)��
* ��֪δ�����ĵ�visitedֵ���Ϊ0��
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
* �����void BFS(Graph g, int i)������
* �ú��������Ϊi�Ķ��㿪ʼ������ȱ���ͼG(�ѱ����ĵ�visitedֵ���Ϊ1)��
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
* �����int connect(Graph g, VertexType v, VertexType u)������
* �ú����ж�ͼ����������v��w�Ƿ���ͨ����ͨ����1������ͨ����0��
*/
int connect(Graph g, VertexType v, VertexType u) {
    int v_pos = locateVertex(g, v);
    int u_pos = locateVertex(g, u);

    DFS(g, v_pos);
    return g->visited[u_pos];
}

/*
* �����int connectedComps(Graph g)������
* �ú�������ͼg����ͨ��֧����
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
* �����int distance(Graph g,VertexType v, VertexType u)������
* �ú�������ͼ����������v��w֮��ľ���(�����ͨ·�ϱߵ���Ŀ)����ʾ����ͨ���ؾ��룬����ͨ����0��
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
* �����void destroyGraph(Graph g)������
* �ú�������ͼg��
*/
void destroyGraph(Graph g) {
    free(g);
}

int main() {
    return 0;
}
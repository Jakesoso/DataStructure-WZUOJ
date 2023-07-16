#include "DataStructure-OJ.hpp"

#define MAXVEX 1000         //��󶥵���
typedef char VertexType;

typedef struct ENode {
    int adjVertex;          //�ñ���ָ�Ķ�����
    int weight;             //��Ȩ
    struct ENode* nextEdge; //��һ����
} ENode;

typedef struct VNode {
    VertexType data;        //������Ϣ
    int visited;            //�������. 1:�ѱ���  0:δ����
    ENode* firstEdge;       //��һ������
} VNode;

typedef struct {
    VNode vexs[MAXVEX];
    int vertexNum, edgeNum; //�����ͱ���
}AdjGraph, * Graph;

/*
* �ú�������һ����ͼ�����ء�
*/
Graph createGraph() {
    Graph g = (Graph)malloc(sizeof(AdjGraph));
    g->edgeNum = 0, g->vertexNum = 0;
    return g;
}

/*
* �ú�����ͼ�����Ҷ���v���������ţ�����������򷵻�-1��
*/
int locateVertex(Graph g, VertexType v) {
    for (int i = 0; i < g->vertexNum; i++) {
        if (v == g->vexs[i].data) 
            return i;
    }
    return -1;
}

/*
* �ú�����ͼg�����Ӷ���v��������󣩣�����Ѵ�����ʲô��������
*/
void addVertex(Graph g, VertexType v) {
    if (locateVertex(g, v) != -1) return;

    int last_index = g->vertexNum;
    g->vexs[last_index].data = v;
    g->vexs[last_index].firstEdge = NULL;
    g->vertexNum++;
}

/*
* �ú�����ͼg�в��ҵ�i�Ŷ��㵽��j�Ŷ���ıߣ���������ָ�롣
* ����Ҳ������ؿ�ָ�롣��֪��i��j�Ŷ�����ͼ�С�
*/
ENode* findEdge(Graph g, int i, int j) {
    ENode* p;
    for (p = g->vexs[i].firstEdge;
        p != NULL && p->adjVertex != j;
        p = p->nextEdge);
    return p;
}

/*
* �ú�����ͼg�����v1v2��ȨΪw��������ı߽����Ϊ������ĵ�1����㡣
* ������㲻���ڣ���ʲôҲ���������������ı��Ѵ���, �洢СȨֵ��
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
* �ú�������ͼg�ж���v�Ķȣ���֪������ͼ�С� 
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
* �ú�����ͼg��ɾ����xy�����ɾ�����ɹ�����ʲô��������
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
* �ú�����ͼg��ɾ������v�����ɾ�����ɹ�����ʲô��������
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
* �ú��������Ϊi�Ľڵ㿪ʼ��������ȱ���g�еĽڵ㡣��֪i�Žڵ�һ����ͼ��
*/
void DFS(Graph g, int i) {
    g->vexs[i].visited = 1;
    for (ENode* p = g->vexs[i].firstEdge; p != NULL; p = p->nextEdge) {
        if (g->vexs[p->adjVertex].visited) continue;
        DFS(g, p->adjVertex);
    }
}

/*
* �ú��������Ϊi�Ľڵ㿪ʼ��������ȱ���g�еĽڵ㡣��֪i�Žڵ�һ����ͼ��
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
* �ú����ж�ͼg��������x��y�Ƿ���ͨ����ͨ����1�����򷵻�0��
*/
int connect(Graph g, VertexType x, VertexType y) {
    int x_pos = locateVertex(g, x);
    int y_pos = locateVertex(g, y);

    DFS(g, x_pos);
    return g->vexs[y_pos].visited;
}

/*
* �ú�������ͼg����ͨ��֧����
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
* �ú�������ͼg��
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
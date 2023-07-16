#include "DataStructure-OJ.hpp"

#define MAXVEX 100 /*��󶥵���*/
typedef char VertexType;

struct AOENetworkStruct;
typedef struct AOENetworkStruct* AOENetwork;

typedef struct ENode {
    int adjVertex;  //�ߵ��յ���
    int weight;     //��Ȩ
    int earliest;   //����翪ʼʱ��
    int latest;     //�����ʼʱ��
    struct ENode* nextEdge;  //��һ����
} ENode;

typedef struct VNode {
    VertexType data;    //������Ϣ
    int inDegree;       //���
    int earliest;       //�¼����緢��ʱ��
    int latest;         //�¼�������ʱ��
    ENode* firstEdge; //��һ������
} VNode;

struct AOENetworkStruct {
    VNode vexs[MAXVEX];    //���
    int vertexNum, edgeNum; //�������ͻ���
};

AOENetwork createGraph();


int main() {

    return 0;
}
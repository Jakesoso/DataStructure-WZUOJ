#include "DataStructure-OJ.hpp"

#define MAXVEX 100 /*最大顶点数*/
typedef char VertexType;

struct AOENetworkStruct;
typedef struct AOENetworkStruct* AOENetwork;

typedef struct ENode {
    int adjVertex;  //边的终点编号
    int weight;     //边权
    int earliest;   //活动最早开始时间
    int latest;     //活动最晚开始时间
    struct ENode* nextEdge;  //下一条边
} ENode;

typedef struct VNode {
    VertexType data;    //顶点信息
    int inDegree;       //入度
    int earliest;       //事件最早发生时间
    int latest;         //事件最晚发生时间
    ENode* firstEdge; //第一条出边
} VNode;

struct AOENetworkStruct {
    VNode vexs[MAXVEX];    //点表
    int vertexNum, edgeNum; //顶点数和弧数
};

AOENetwork createGraph();


int main() {

    return 0;
}
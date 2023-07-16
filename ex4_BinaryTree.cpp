#include "DataStructure-OJ.hpp"

typedef char ElementType;
typedef struct Node
{
    ElementType data;
    struct Node* lchild;
    struct Node* rchild;
}BTNode, * BTree;


// �ú������ض�����rt������(����)������������Ϊ0��
int getDepth(BTree rt) {
    if (rt == NULL) return 0;
    return std::max(getDepth(rt->lchild), getDepth(rt->rchild)) + 1;
}

// �ú������ض�����rt��Ҷ�ӽ����Ŀ��
int getLeafNum(BTree rt) {
    if (rt == NULL) return 0;
    if (rt->lchild == NULL && rt->rchild == NULL) {
        return 1;
    }    
    return getLeafNum(rt->rchild) + getLeafNum(rt->lchild);
}

// �ú����������˳�����������rt��Ҷ�ӽ�㣬
// ÿ����������Ӧ���ַ����ַ�����û���κζ���������Ϣ��
void leafNode(BTree rt) {
    if (rt == NULL) return;
    if (rt->lchild == NULL && rt->rchild == NULL) {
        std::cout << rt->data;
    }
    leafNode(rt->lchild);
    leafNode(rt->rchild);
}

// �ú������ض�����rt�Ľ������
int getNum(BTree rt) {
    if (rt == NULL) return 0;
    return getNum(rt->rchild) + getNum(rt->lchild) + 1;
}

// �ú�����������չ������˳�����������bt�Ľ�㡣
// ÿ���ڵ������Ӧ���ַ����ַ�����û���κζ���������Ϣ�� 
// ������ν����չ��ָ�սڵ����һ��'.'��
// ���������ʾ�Ķ����� A(B, C)������չ�������ΪAB..C..
/*
void preOrderExt(BTree bt) {
    if (bt == NULL) return;
    std::cout << bt->data;
    if (bt->lchild == NULL) std::cout << ".";
    preOrderExt(bt->lchild);
    if (bt->rchild == NULL) std::cout << ".";
    preOrderExt(bt->rchild);
}
*/

void preOrderExt(BTree bt){
    if (bt == NULL){
        std::cout << ".";
        return;
    }
    std::cout << bt->data;
    preOrderExt(bt->lchild);
    preOrderExt(bt->rchild);
}


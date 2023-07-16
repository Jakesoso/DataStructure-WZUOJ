#include "DataStructure-OJ.hpp"

typedef char ElementType;
typedef struct Node
{
    ElementType data;
    struct Node* lchild;
    struct Node* rchild;
}BTNode, * BTree;


// 该函数返回二叉树rt的树高(树深)，空树的树高为0。
int getDepth(BTree rt) {
    if (rt == NULL) return 0;
    return std::max(getDepth(rt->lchild), getDepth(rt->rchild)) + 1;
}

// 该函数返回二叉树rt的叶子结点数目。
int getLeafNum(BTree rt) {
    if (rt == NULL) return 0;
    if (rt->lchild == NULL && rt->rchild == NULL) {
        return 1;
    }    
    return getLeafNum(rt->rchild) + getLeafNum(rt->lchild);
}

// 该函数按先序的顺序输出二叉树rt的叶子结点，
// 每个结点输出对应的字符，字符后面没有任何多余的输出信息。
void leafNode(BTree rt) {
    if (rt == NULL) return;
    if (rt->lchild == NULL && rt->rchild == NULL) {
        std::cout << rt->data;
    }
    leafNode(rt->lchild);
    leafNode(rt->rchild);
}

// 该函数返回二叉树rt的结点数。
int getNum(BTree rt) {
    if (rt == NULL) return 0;
    return getNum(rt->rchild) + getNum(rt->lchild) + 1;
}

// 该函数按先序拓展遍历的顺序输出二叉树bt的结点。
// 每个节点输出对应的字符，字符后面没有任何多余的输出信息。 
// 这里所谓的拓展是指空节点输出一个'.'，
// 比如广义表表示的二叉树 A(B, C)先序拓展遍历输出为AB..C..
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


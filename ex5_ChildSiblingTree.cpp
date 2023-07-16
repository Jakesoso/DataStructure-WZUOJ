#include "DataStructure-OJ.hpp"

typedef char ElementType;
typedef struct CSNode {
    ElementType data;
    struct CSNode* child;
    struct CSNode* sibling;
}CSTNode, * CSTree;

CSTNode* createNode(ElementType data, CSNode* child, CSNode* sibling) {
    CSTNode* node = (CSTNode*)malloc(sizeof(CSTNode));
    node->data = data;
    node->child = child;
    node->sibling = sibling;
    return node;
}


// ���CSTree createTree(char s[])������
// �ú������ַ���s����һ�����������ַ���s�ǽ��ɡ�(������)������, ���Լ���Сд�ַ����ɵ����Ĺ�����ʾ��
// ��A(B(D, E, F), C(G))���ַ���s��'\0'��β��
// ������ʱ����һ�ֵ������ս����ֵ�˳�����ӡ�
CSTree _createTree(char s[]) {
    const int MAX_NODE = 100;
    enum STATUS {
        UNDEFINED, ON_CHILD,
    }; 
    CSTNode* curr_node[MAX_NODE] = { NULL };
    int status = UNDEFINED;
    int layer = -1;
    char* str = s;
    int flag = 0;
    CSTNode* new_node = NULL;

    while (*str != '\0') {
        if (isalpha(*str)) {
            new_node = createNode(*str, NULL, NULL);
            // working on child
            if (status == ON_CHILD) {
                // first child put into child node
                if (!flag) curr_node[layer]->child = new_node;
                // other children put into child's sibling node
                else {
                    // insert into the last child's sibling node
                    CSTNode* node = curr_node[layer]->child;
                    while (node->sibling != NULL) {
                        node = node->sibling;
                    }
                    node->sibling = new_node;
                }
            }
        }
        // get child node
        else if (*str == '(') {
            flag = 0;
            status = ON_CHILD;
            layer++;
            curr_node[layer] = new_node;
        }
        // after one child
        else if (*str == ',') {
            flag = 1;
        }
        // finish current node
        else if (*str == ')') {
            layer--;
        }
        str++;
    }
    // when there's only one node
    if (curr_node[0] == NULL) return new_node;

    return curr_node[0];
}


// �����CSTree createTree()������ �ú����ӱ�׼���봴��һ������
// �����ж��У���ʾ���Ĺ�����ȱ����������������£�
// A
// BC#
// DEF#
// G#
// #
// #
// #
// #
CSTree createTree() {
    std::queue<CSTree> q;
    char data, datas[20];

    // add first element to queue
    std::cin >> data;
    CSTNode* head = createNode(data, NULL, NULL);
    q.push(head);

    while (!q.empty()) {
        // pop up an element and set its child
        CSTNode* node = q.front();
        q.pop();
        std::cin >> datas;

        for (int i = 0; datas[i] != '#'; i++) {
            CSTNode* child = createNode(datas[i], NULL, NULL);
            q.push(child);

            // first child put into child node
            if (i == 0) 
                node->child = child;

            // other children put into child's sibling node
            else{
                CSTNode* tmp = node->child;
                while (tmp->sibling != NULL) {
                    tmp = tmp->sibling;
                }
                tmp->sibling = child;
            }
        }
    }

    return head;
}

void preOrder(CSTree root) {
    CSTNode* p;
    if (root == NULL) return;

    // print root
    std::cout << root->data;
    // print left child
    preOrder(root->child);
    // print right children
    for (p = root->child; p != NULL; p = p->sibling)
        preOrder(p->sibling);
}

void postOrder(CSTree root) {
    CSTNode* p;
    if (root == NULL) return;
   
    // print left child
    postOrder(root->child);
    // print right children
    for (p = root->child; p != NULL; p = p->sibling)
        postOrder(p->sibling);
    // print root
    std::cout << root->data;
}

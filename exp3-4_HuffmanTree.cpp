#include "DataStructure-OJ.hpp"

int left(int i);
int right(int i);
int parent(int i);
void swap(Heap H, int i, int smallest);
Heap createHeap(int capacity);

typedef int KeyType;
typedef struct {
	KeyType value;
	int weight;
} Node;

typedef struct HTNode {
	KeyType value;	//节点数值
	int weight;		//节点权
	HTNode* lchild;
	HTNode* rchild;
	int depth;
	bool operator < (const HTNode& a) const {
		return (weight < a.weight) || (weight == a.weight && value < a.value);
	}
} HTNode, * HuffmanTree;

typedef HuffmanTree ElementType;
typedef struct {
	ElementType* data; //数据
	int size;	 		//大小
	int capacity;  		//容量
} HNode, * Heap;

/*
请设计void heapify(Heap H,int i)函数。
该函数把以i为根的子树调整为最小堆。 已知结点i的左子树和右子树已经是最小堆。
其中堆H数据的每个元素是一个指针，该指针指向哈夫曼树的一个节点NTNode。
结构NTNode已经重载了 < 运算符，你可以直接使用。
求节点i的左孩子与右孩子，以及交换两个节点
int left(int i);
int right(int i);
void swap(H,i,smallest);
函数已经定义，你可以直接调用。
*/
void heapify(Heap H, int i) {
	int cur_i = i, min = i;
	while (true) {
		if (left(cur_i) <= H->size && (*(H->data[left(cur_i)]) < *(H->data[cur_i]))) {
			min = left(cur_i);
		}
		if (right(cur_i) <= H->size && (*(H->data[right(cur_i)]) < *(H->data[min]))) {
			min = right(cur_i);
		}
		if (min == cur_i) return;

		swap(H, cur_i, min);
		heapify(H, min);
		cur_i = min;
	}
}

/*
请设计void initHeap(Heap H,Node data[],int n)函数。
该函数用data数组初始化最小堆(优先队列)。
 数据在data[1]到data[n]中，value表示节点的数值，weight表示对应数值的权。
其中堆H数据的每个元素是一个指针，该指针指向哈夫曼树的一个节点。
该函数中需要分配data[1..n]对应的哈夫曼节点并对其成员赋值； 并把堆的数据初始化。
保持子堆性质
void heapify(Heap H,int i);
函数已经定义，你可以直接调用。
*/
void initHeap(Heap H, Node data[], int n) {
	H->size = n;
	for (int i = 1; i <= n; i++) {
		HuffmanTree x = (HuffmanTree)malloc(sizeof(HTNode));
		x->value = data[i].value;
		x->weight = data[i].weight;
		x->lchild = x->rchild = NULL;
		H->data[i] = x;
	}
	for (int i = n / 2; i >= 1; i--) {
		heapify(H, i);
	}
}

/*
* 请设计ElementType front(Heap H)函数。
* 该函数返回最小堆H的队首数据，已知最小堆H非空。
*/
ElementType front(Heap H) {
	return H->data[1];
}

/*
请设计void push(Heap H,ElementType x)函数。
该函数将数据x进入优先队列(最小堆)，已知堆不满。
 结构HTNode已经重载了 < 运算符，你可以直接使用。
以下函数以及定义，你可以直接调用。
int parent(int i);
void swap(Heap H, int i, int j);
*/
void push(Heap H, ElementType x) {
	H->size++;
	H->data[H->size] = x;
	int cur_pos = H->size;
	while (cur_pos > 1) {
		int father_pos = parent(cur_pos);
		if (*H->data[cur_pos] < *H->data[father_pos]) {
			swap(H, cur_pos, father_pos);
		}
		cur_pos = father_pos;
	}
}

/*
请设计void pop(Heap H)函数。
该函数将优先队列(最小堆)的队首数据出队，已知堆不空。
以下函数以及定义好，你可以直接调用。
void heapify(Heap H,int i);
*/
void pop(Heap H) {
	H->data[1] = H->data[H->size];
	H->size--;
	heapify(H, 1);
}

/*
请设计HuffmanTree createHuffmanTree(Node data[],int n)函数。
该函数创建哈夫曼树并返回。
参数data[1]...data[n]保存哈夫曼树的节点信息， 其中value表示节点的数值，weight表示对应数值的权。
已知所有叶节点的数值互不相同，权值为不超过100个正整数。
创建哈夫曼树中间节点时，中间节点数值为左右孩子节点中数值较小者，并且较小权值的子节点作为左孩子。
以下函数已经定义好，你可以直接调用。
Heap createHeap(int capacity);
void initHeap(Heap H,Node data[],int n);
void destroyHeap(Heap H);
ElementType front(Heap H);
void pop(Heap H);
void push(Heap H,ElementType x);
*/
HuffmanTree createHuffmanTree(Node data[], int n) {
	Heap heap = createHeap(n);
	initHeap(heap, data, n);
	ElementType left_child, right_child, new_node;
	for (int i = 1; i < n; i++){
		new_node = (ElementType)malloc(sizeof(HTNode));
		left_child = front(heap), pop(heap);
		right_child = front(heap), pop(heap);
		new_node->lchild = left_child;
		new_node->rchild = right_child;
		new_node->weight = left_child->weight + right_child->weight;
		new_node->value = std::min(left_child->value, right_child->value);
		push(heap, new_node);
	}
	return front(heap);
}

/*
请设计void huffmanCode(HuffmanTree HT,int code[],int depth)函数。
该函数按先序遍历的顺序输出哈夫曼树所有叶节点的值和编码，值与编码以“:”隔开（7:01000）。
每个叶节点的编码输出一行，编码采用左0右1的编码方案。
参数code[]存放当前节点的编码(从code[0]开始保存)，depth表示当前节点的层次 。
*/
void huffmanCode(HuffmanTree HT, int code[], int depth) {
	// only print leaf node
	if (HT->lchild == NULL && HT->rchild == NULL){
		std::cout << HT->value << ":";
		for (int i = 0; i < depth; i++) std::cout << code[i];
		std::cout << "\n";
		return;
	}
	code[depth] = 0;
	huffmanCode(HT->lchild, code, depth + 1);
	code[depth] = 1;
	huffmanCode(HT->rchild, code, depth + 1);
}

/*
请设计void initDepth(HuffmanTree HT,int depth)函数。
该函数初始化哈夫曼树HT中每个节点的深度depth。其中根节点深度为0.
*/
void initDepth(HuffmanTree HT, int depth) {
	HT->depth = depth;
	if (HT->lchild != NULL) initDepth(HT->lchild, depth + 1);
	if (HT->rchild != NULL) initDepth(HT->rchild, depth + 1);
}

/*
请设计int getWPL(HuffmanTree HT)函数。
该函数返回哈夫曼树HT的带权路径长度。
其中哈夫曼树HT每个节点的weight为该节点的权，depth为该接节点的深度(树根深度为0).
*/
int getWPL(HuffmanTree HT) {
	if (HT->lchild == NULL && HT->rchild == NULL) {
		return HT->weight * HT->depth;
	}
	return getWPL(HT->lchild) + getWPL(HT->rchild);
}

int main() {

}

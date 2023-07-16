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
	KeyType value;	//�ڵ���ֵ
	int weight;		//�ڵ�Ȩ
	HTNode* lchild;
	HTNode* rchild;
	int depth;
	bool operator < (const HTNode& a) const {
		return (weight < a.weight) || (weight == a.weight && value < a.value);
	}
} HTNode, * HuffmanTree;

typedef HuffmanTree ElementType;
typedef struct {
	ElementType* data; //����
	int size;	 		//��С
	int capacity;  		//����
} HNode, * Heap;

/*
�����void heapify(Heap H,int i)������
�ú�������iΪ������������Ϊ��С�ѡ� ��֪���i�����������������Ѿ�����С�ѡ�
���ж�H���ݵ�ÿ��Ԫ����һ��ָ�룬��ָ��ָ�����������һ���ڵ�NTNode��
�ṹNTNode�Ѿ������� < ������������ֱ��ʹ�á�
��ڵ�i���������Һ��ӣ��Լ����������ڵ�
int left(int i);
int right(int i);
void swap(H,i,smallest);
�����Ѿ����壬�����ֱ�ӵ��á�
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
�����void initHeap(Heap H,Node data[],int n)������
�ú�����data�����ʼ����С��(���ȶ���)��
 ������data[1]��data[n]�У�value��ʾ�ڵ����ֵ��weight��ʾ��Ӧ��ֵ��Ȩ��
���ж�H���ݵ�ÿ��Ԫ����һ��ָ�룬��ָ��ָ�����������һ���ڵ㡣
�ú�������Ҫ����data[1..n]��Ӧ�Ĺ������ڵ㲢�����Ա��ֵ�� ���Ѷѵ����ݳ�ʼ����
�����Ӷ�����
void heapify(Heap H,int i);
�����Ѿ����壬�����ֱ�ӵ��á�
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
* �����ElementType front(Heap H)������
* �ú���������С��H�Ķ������ݣ���֪��С��H�ǿա�
*/
ElementType front(Heap H) {
	return H->data[1];
}

/*
�����void push(Heap H,ElementType x)������
�ú���������x�������ȶ���(��С��)����֪�Ѳ�����
 �ṹHTNode�Ѿ������� < ������������ֱ��ʹ�á�
���º����Լ����壬�����ֱ�ӵ��á�
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
�����void pop(Heap H)������
�ú��������ȶ���(��С��)�Ķ������ݳ��ӣ���֪�Ѳ��ա�
���º����Լ�����ã������ֱ�ӵ��á�
void heapify(Heap H,int i);
*/
void pop(Heap H) {
	H->data[1] = H->data[H->size];
	H->size--;
	heapify(H, 1);
}

/*
�����HuffmanTree createHuffmanTree(Node data[],int n)������
�ú��������������������ء�
����data[1]...data[n]������������Ľڵ���Ϣ�� ����value��ʾ�ڵ����ֵ��weight��ʾ��Ӧ��ֵ��Ȩ��
��֪����Ҷ�ڵ����ֵ������ͬ��ȨֵΪ������100����������
�������������м�ڵ�ʱ���м�ڵ���ֵΪ���Һ��ӽڵ�����ֵ��С�ߣ����ҽ�СȨֵ���ӽڵ���Ϊ���ӡ�
���º����Ѿ�����ã������ֱ�ӵ��á�
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
�����void huffmanCode(HuffmanTree HT,int code[],int depth)������
�ú��������������˳�����������������Ҷ�ڵ��ֵ�ͱ��룬ֵ������ԡ�:��������7:01000����
ÿ��Ҷ�ڵ�ı������һ�У����������0��1�ı��뷽����
����code[]��ŵ�ǰ�ڵ�ı���(��code[0]��ʼ����)��depth��ʾ��ǰ�ڵ�Ĳ�� ��
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
�����void initDepth(HuffmanTree HT,int depth)������
�ú�����ʼ����������HT��ÿ���ڵ�����depth�����и��ڵ����Ϊ0.
*/
void initDepth(HuffmanTree HT, int depth) {
	HT->depth = depth;
	if (HT->lchild != NULL) initDepth(HT->lchild, depth + 1);
	if (HT->rchild != NULL) initDepth(HT->rchild, depth + 1);
}

/*
�����int getWPL(HuffmanTree HT)������
�ú������ع�������HT�Ĵ�Ȩ·�����ȡ�
���й�������HTÿ���ڵ��weightΪ�ýڵ��Ȩ��depthΪ�ýӽڵ�����(�������Ϊ0).
*/
int getWPL(HuffmanTree HT) {
	if (HT->lchild == NULL && HT->rchild == NULL) {
		return HT->weight * HT->depth;
	}
	return getWPL(HT->lchild) + getWPL(HT->rchild);
}

int main() {

}

#include "DataStructure-OJ.hpp"

typedef int ElementType;
typedef struct {
	ElementType* data;
	int size;
	int capacity;
}HNode, * Heap;

Heap createHeap(int capacity) {
	Heap heap = (Heap)malloc(sizeof(HNode));
	heap->data = (ElementType*)malloc(sizeof(ElementType) * (capacity + 1));
	heap->size = 0;
	heap->capacity = capacity;
	return heap;
}

// 该函数返回堆中序号为i的结点的父结点序号，已知参数i>1。
int parent(int i) {
	return i / 2;
}

// 该函数返回堆中序号为i的结点的左子结点序号，已知给定的i的左子结点必定存在。
int left(int i) {
	return i * 2;
}

// 该函数返回堆中序号为i的结点的右子结点序号，已知给定的i的右子结点必定存在。
int right(int i) {
	return i * 2 + 1;
}

// 该函数判断堆H是否已满，如果已满返回1，否则返回0。
int full(Heap H) {
	return H->size >= H->capacity;
}

// 该函数判断堆H是否空堆，如果是空堆返回1，否则返回0。
int empty(Heap H) {
	return H->size == 0;
}

// 该函数交换堆H中序号为i和j的数据，已知序号i和j都是有效的。
void swap(Heap H, int i, int j) {
	std::swap(H->data[i], H->data[j]);
}

// 该函数把堆H中序号为i结点数据数值增大为x(同时保持H仍然是最大堆)，
// 已知序号i是有效的，如果x小于堆H中序号为i的结点数据，则什么都不做。
void increase(Heap H, int i, ElementType x) {
	int* arr = H->data;
	if (x < arr[i])	return;
	arr[i] = x;

	int cur_pos = i, parent_pos = parent(cur_pos);
	while (arr[cur_pos] > arr[parent_pos] && cur_pos > 1) {
		swap(H, cur_pos, parent_pos);
		cur_pos = parent_pos;
		parent_pos = parent(cur_pos);
	}
}

// 该函数在最大堆H中插入数据x。如果插入成功返回1，否则返回0。
int insert(Heap H, ElementType x) {
	if (full(H)) return 0;

	// insert a minimal number in bottom
	int* arr = H->data;
	H->size++;
	arr[H->size] = -10000;

	// increase this minimal number to exact insert number
	increase(H, H->size, x);

	return 1;
}

// 该函数把以 i 为根的子树调整为最大堆。
// 已知结点 i 的左子树和右子树已经是最大堆。
void heapify(Heap H, int i) {
	int* arr = H->data;
	int cur_pos = i, left_pos, right_pos, maxChild_pos;

	while (true) {
		left_pos = left(cur_pos), right_pos = right(cur_pos);
		// no more child tree, so put this head to the last
		if (left_pos > H->size || right_pos > H->size) {
			// no left child, proper postion
			if (left_pos > H->size) {
				return;
			}
			// has left child, no right child, check the left child
			if (arr[cur_pos] < arr[left_pos]) {
				swap(H, cur_pos, left_pos);
			}
			return;
		}
		// get the max between left tree and right tree
		maxChild_pos = arr[left_pos] > arr[right_pos] ? left_pos : right_pos;
		// proper postion
		if (arr[cur_pos] >= arr[maxChild_pos]) return;
		// swap with max
		swap(H, cur_pos, maxChild_pos);
		cur_pos = maxChild_pos;
	}
}

// 已知H是一个空堆，数据空间足够。
// 该函数把data[]数组中的数据(总共n个，从data[1]到data[n])初始化最大堆。
void initHeap(Heap H, ElementType data[], int n) {
	for (int i = 1; i <= n; i++) {
		insert(H, data[i]);
	}
}

// 该函数对最大堆H中的数据排序。
void heapSort(Heap H) {
	int size = H->size;
	while (H->size > 0) {
		swap(H, 1, H->size);
		H->size--;
		heapify(H, 1);
	}
	H->size = size;
}

// 该函数销毁堆。
void destroyHeap(Heap H) {
	if (H->data != NULL) {
		if (H->data != NULL) free(H->data);
		free(H);
	}
}

// 该函数返回优先队列H的队首数据，已知优先队列H非空。
ElementType front(Heap H) {
	return H->data[1];
}

// 已有优先队列H（最大堆），该函数将数据x入队，入队成功返回1，否则返回0。
int push(Heap H, ElementType x) {
	return insert(H, x);
}

// 已知优先队列H（最大堆）非空，该函数将H中的队首数据出队。
void pop(Heap H) {
	H->data[1] = H->data[H->size];
	H->size--;
	heapify(H, 1);
}

int main() {
	Heap heap = createHeap(100);
	insert(heap, 1);
	insert(heap, 2);
	insert(heap, 3);
	insert(heap, 4);
	insert(heap, 5);
	insert(heap, 6);
	
	heap->data[1] = -1;
	heap->data[2] = 5;
	heap->data[3] = 4;
	for (int i = 1; i <= heap->size; i++) {
		std::cout << heap->data[i] << std::endl;
	}
	std::cout << std::endl;
	heapify(heap, 1);

	for (int i = 1; i <= heap->size; i++) {
		std::cout << heap->data[i] << std::endl;
	}
}
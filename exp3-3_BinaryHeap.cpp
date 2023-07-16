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

// �ú������ض������Ϊi�Ľ��ĸ������ţ���֪����i>1��
int parent(int i) {
	return i / 2;
}

// �ú������ض������Ϊi�Ľ������ӽ����ţ���֪������i�����ӽ��ض����ڡ�
int left(int i) {
	return i * 2;
}

// �ú������ض������Ϊi�Ľ������ӽ����ţ���֪������i�����ӽ��ض����ڡ�
int right(int i) {
	return i * 2 + 1;
}

// �ú����ж϶�H�Ƿ������������������1�����򷵻�0��
int full(Heap H) {
	return H->size >= H->capacity;
}

// �ú����ж϶�H�Ƿ�նѣ�����ǿնѷ���1�����򷵻�0��
int empty(Heap H) {
	return H->size == 0;
}

// �ú���������H�����Ϊi��j�����ݣ���֪���i��j������Ч�ġ�
void swap(Heap H, int i, int j) {
	std::swap(H->data[i], H->data[j]);
}

// �ú����Ѷ�H�����Ϊi���������ֵ����Ϊx(ͬʱ����H��Ȼ������)��
// ��֪���i����Ч�ģ����xС�ڶ�H�����Ϊi�Ľ�����ݣ���ʲô��������
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

// �ú���������H�в�������x���������ɹ�����1�����򷵻�0��
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

// �ú������� i Ϊ������������Ϊ���ѡ�
// ��֪��� i �����������������Ѿ������ѡ�
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

// ��֪H��һ���նѣ����ݿռ��㹻��
// �ú�����data[]�����е�����(�ܹ�n������data[1]��data[n])��ʼ�����ѡ�
void initHeap(Heap H, ElementType data[], int n) {
	for (int i = 1; i <= n; i++) {
		insert(H, data[i]);
	}
}

// �ú���������H�е���������
void heapSort(Heap H) {
	int size = H->size;
	while (H->size > 0) {
		swap(H, 1, H->size);
		H->size--;
		heapify(H, 1);
	}
	H->size = size;
}

// �ú������ٶѡ�
void destroyHeap(Heap H) {
	if (H->data != NULL) {
		if (H->data != NULL) free(H->data);
		free(H);
	}
}

// �ú����������ȶ���H�Ķ������ݣ���֪���ȶ���H�ǿա�
ElementType front(Heap H) {
	return H->data[1];
}

// �������ȶ���H�����ѣ����ú���������x��ӣ���ӳɹ�����1�����򷵻�0��
int push(Heap H, ElementType x) {
	return insert(H, x);
}

// ��֪���ȶ���H�����ѣ��ǿգ��ú�����H�еĶ������ݳ��ӡ�
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
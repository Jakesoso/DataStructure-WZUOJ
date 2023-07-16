#include "DataStructure-OJ.hpp"

#define USED 1
#define EMPTY 0

typedef int ElementType;

typedef struct {
    ElementType key; //�ؼ�����
    int flag;        //״̬��־��USED(������)��EMPTY(����)
}Cell;

typedef struct {
    Cell* cells;    //ɢ�б��ָ��
    int capacity;   //ɢ�б�����
    int size;       //ɢ�б��С
}HashTable;

int judge(int x) {
    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0) return 0;
    return 1;
}

int nextPrime(int n) {
    while (!judge(n)) n++;
    return n;
}

/*
* �ú�������һ����������Ϊcapacity
* (��С��capacity����С����)��ɢ�б�������ָ�롣
*/
HashTable* create(int capacity) {
    HashTable* h = (HashTable*)malloc(sizeof(HashTable));
    int cap = nextPrime(capacity);
    h->cells = (Cell*)malloc(cap * sizeof(Cell));
    h->capacity = cap;
    h->size = 0;
    return h;
}

/*
* �ú�������ؼ���key��ɢ��ֵ
* ������ɢ��ֵ�򵥵�ȡΪkey��ɢ�б�������������
*/
int hash(HashTable* h, ElementType key) {
    return key % h->capacity;
}

/*
* �ú�����ɢ�б��в���һ����(key�Ѿ���Ż��߿ղ�)�����������key�������ظò۵��±ꡣ 
* ������ڳ�ͻ������ƽ��̽�ⷨ��di=i^2�������ͻ��
*/
int find(HashTable* h, ElementType key) {
    int cnt = 0;
    int k = key % h->capacity;
    while (h->cells[k].flag && h->cells[k].key != key) {
        int tmp = (cnt % 2 ? -1 : 1) * (cnt / 2 + 1) * (cnt / 2 + 1);
        k += tmp;
        while (k < 0) k += h->capacity;
        if (k >= h->capacity) k %= h->capacity;
        cnt++;
    }
    return k;
}

/*
* �ú�����ɢ�б��в���һ��key�����key�Ѿ����ڣ���ʲô�������� 
*/
void insert(HashTable* h, ElementType key) {
    int pos = find(h, key);
    if (h->cells[pos].flag) return;
    h->cells[pos].key = key;
    h->cells[pos].flag = 1;
    h->size++;
}

/*
* �ú�����ɢ�б���ɢ�У����´���һ��������С��2*capacity�������������ݲ��б�
* ����ԭ���ݲ��е����ݲ�����б�
*/
void rehash(HashTable* h) {
    //int keys[100000] = {0}; to pass the OJ, big array is needed
    int keys[100] = {0};
    int cnt = 1;

    // get all keys
    for (int i = 0; i < h->capacity; i++) {
        if (h->cells[i].flag) {
            keys[cnt] = h->cells[i].key;
            cnt++;
        }
    }
    
    // set new list
    int cap = nextPrime(2 * h->capacity);
    free(h->cells);
    h->cells = (Cell*)malloc(cap * sizeof(Cell));
    h->size = 0;
    h->capacity = cap;

    // insert keys
    for (int i = 1; i <= cnt; i++) {
        insert(h, keys[i]);
    }
}

/*
* �ú�����ɢ�б��в���һ��key�����key�Ѿ����ڣ���ʲô�������� 
* ���ɢ�б��в�ռ�ȳ���50%�����ɢ�б�����ɢ�С�
*/
void insert(HashTable* h, ElementType key) {
    int pos = find(h, key);
    if (h->cells[pos].flag) return;

    h->cells[pos].key = key;
    h->cells[pos].flag = 1;
    h->size++;

    // rehash if over 50%
    if (2 * h->size > h->capacity) {
        rehash(h);
    }
}

/*
* �ú�������ɢ�б�h
*/
void destroy(HashTable* h) {
    free(h->cells);
    free(h);
}

int main() {
    return 0;
}


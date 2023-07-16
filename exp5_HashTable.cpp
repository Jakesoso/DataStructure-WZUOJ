#include "DataStructure-OJ.hpp"

#define USED 1
#define EMPTY 0

typedef int ElementType;

typedef struct {
    ElementType key; //关键数字
    int flag;        //状态标志：USED(槽已用)或EMPTY(空闲)
}Cell;

typedef struct {
    Cell* cells;    //散列表槽指针
    int capacity;   //散列表容量
    int size;       //散列表大小
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
* 该函数创建一个容量至少为capacity
* (不小于capacity的最小素数)的散列表并返回其指针。
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
* 该函数计算关键字key的散列值
* 本题中散列值简单的取为key对散列表容量的余数。
*/
int hash(HashTable* h, ElementType key) {
    return key % h->capacity;
}

/*
* 该函数在散列表中查找一个槽(key已经存放或者空槽)用来存放数据key，并返回该槽的下标。 
* 如果存在冲突，则用平方探测法（di=i^2）解决冲突。
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
* 该函数在散列表中插入一个key，如果key已经存在，则什么都不做。 
*/
void insert(HashTable* h, ElementType key) {
    int pos = find(h, key);
    if (h->cells[pos].flag) return;
    h->cells[pos].key = key;
    h->cells[pos].flag = 1;
    h->size++;
}

/*
* 该函数对散列表重散列：重新创建一个槽数不小于2*capacity的素数个的数据槽列表
* 并把原数据槽中的数据插入槽列表。
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
* 该函数在散列表中插入一个key，如果key已经存在，则什么都不做。 
* 如果散列表中槽占比超过50%，则对散列表重新散列。
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
* 该函数销毁散列表h
*/
void destroy(HashTable* h) {
    free(h->cells);
    free(h);
}

int main() {
    return 0;
}




typedef struct ELEMENT{
	int key;
	int maxPos;
	int minPos;
} ELEMENT;

typedef struct HEAP{
	int capacity;
	int size;
	int ADT;
	ELEMENT **A;
	ELEMENT **a;
} HEAP;

void printElement(ELEMENT* a);
void swap (ELEMENT** a, ELEMENT** b);
void buildHeap (HEAP* heap);
void max_heapify (ELEMENT **a, int i, int n);
void min_heapify (ELEMENT **a, int i, int n);
ELEMENT* extract_max (ELEMENT** a, int n);
ELEMENT* extract_min (ELEMENT** a, int n);
void delete_max (ELEMENT** a, int pos, int n);
void delete_min (ELEMENT** a, int pos, int n);
void max_heap_increase_key (ELEMENT** a, int i, int key);
void max_heap_decrease_key (ELEMENT** a, int n, int i, int key);
void min_heap_decrease_key (ELEMENT** a, int i, int key);
void min_heap_increase_key (ELEMENT** a, int n, int i, int key);
void min_heap_insert (ELEMENT** a, int n, int key);
void max_heap_insert (ELEMENT** a, int n, int key);
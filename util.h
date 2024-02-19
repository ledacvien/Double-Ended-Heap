// Author: Dac Vien Le
// CSE 310
// Prof Xue
#include "heap.h"
#include <iostream>

int* posKey (int command, char str[]);
int interpret (char str[]);
void readFile (HEAP* heap, int capacity);
void printHeap (FILE* fp, HEAP* heap);
void writeFile (HEAP* heap);
void extractMax (HEAP* heap);
void extractMin (HEAP* heap);
void insertKey (HEAP* heap, int key);
void increaseKey (HEAP* heap, int pos, int key);
void decreaseKey (HEAP* heap, int pos, int key);
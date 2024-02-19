// Author: Dac Vien Le
// CSE 310
// Prof Xue

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

using namespace std;

int interpret (char str[])
{
	if (strcmp(str, (char*)"Stop") == 0)
		return 0;
	if (strcmp(str, (char*)"Print") == 0)
		return 1;
	if (strcmp(str, (char*)"Read") == 0)
		return 2;
	if (strcmp(str, (char*)"Write") == 0)
		return 3;
	if (strcmp(str, (char*)"Insert") == 0)
		return 4;
	if (strcmp(str, (char*)"ExtractMax") == 0)
		return 5;
	if (strcmp(str, (char*)"ExtractMin") == 0)
		return 6;
	if (strcmp(str, (char*)"IncreaseKey") == 0)
		return 7;
	if (strcmp(str, (char*)"DecreaseKey") == 0)
		return 8;
	return 9;
}

int* posKey (int command, char str[])
{
	if (*str == '\0')
		return NULL;

	int* a = (int*)malloc(2*sizeof(int));
	a[0] = 0;
	a[1] = 0;
	int i = 0;

	char s[10];
	int j = 0;
	for (i = 1; str[i] != '\0' && str[i] != ' '; ++i, ++j)
	{
		s[j] = str[i];
	}
	s[j] = '\0';
	a[0] = atoi(s);

	if (str[i] != '\0')
	{
		j = 0;
		for (i++; str[i] != '\0' && str[i] != ' '; ++i, ++j)
		{
			s[j] = str[i];
		}
		s[j] = '\0';
		a[1] = atoi(s);
	}

	if (command == 7 || command == 8)
	{
		if (i < 4)
			return NULL;
	}
	if (command == 4)
	{
		if (i < 2)
			return NULL;
	}
	return a;
}

void readFile (HEAP* heap, int capacity)
{
	FILE *fp = fopen("HEAPifile.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Cannot open file HEAPifile.txt\n");
		return;
	}

	int n;
	fscanf(fp,"%d", &n);

	if (capacity < n)
	{
		fprintf(stderr, "Error: Heap overflow\n");
		return;
	}
	
	if (heap == NULL)
	{
		fprintf(stderr, "Error: Cannot allocate memory for heap\n");
		return;
	}
	heap->size = n;

	capacity++;
	heap->A = (ELEMENT**)malloc(capacity*sizeof(ELEMENT*));
	heap->a = (ELEMENT**)malloc(capacity*sizeof(ELEMENT*));

	if (heap->A == NULL)
	{
		fprintf(stderr, "Error: Cannot allocate memory for max heap array\n");
		return;
	}
	if (heap->a == NULL)
	{
		fprintf(stderr, "Error: Cannot allocate memory for min heap array\n");
		return;
	}

	for (int i = 1; i <= n; ++i)
	{
		int x; 
		fscanf(fp, "%d", &x);

		ELEMENT* data = (ELEMENT*)malloc(sizeof(ELEMENT));
		data->key = x;
		data->maxPos = i;
		data->minPos = i;

		heap->A[i] = data;
		heap->a[i] = data;
	}		
	fclose(fp);
	buildHeap(heap);
}

void printHeap (FILE* fp, HEAP* heap)
{
	fprintf(fp, "capacity=%d, size=%d\n", heap->capacity, heap->size);

	int n = heap->size;
	// 1 : max heap
	// 2 : min heap
	// 3 : double heap 
	if (heap->ADT != 2 && heap->A != NULL && heap->size > 0)
	{
		fprintf(fp, "MaxHeap: ");
		for (int i = 1; i < n; ++i)
			fprintf(fp, "%d, ", heap->A[i]->key);
		fprintf(fp, "%d\n", heap->A[n]->key);
	}
	if (heap->ADT != 1 && heap->a != NULL && heap->size > 0)
	{
		fprintf(fp, "MinHeap: ");
		for (int i = 1; i < n; ++i)
			fprintf(fp, "%d, ", heap->a[i]->key);
		fprintf(fp, "%d\n", heap->a[n]->key);
	}
}

void writeFile (HEAP* heap)
{
	FILE *fp = fopen("HEAPofile.txt", "w");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Cannot open file HEAPofile.txt\n");
		return;
	}
	printHeap(fp, heap);
	fclose(fp);
}

void extractMax (HEAP* heap)
{
	if (heap == NULL || heap->ADT == 2 || heap->size == 0)
	{
		fprintf(stderr, "Error: ExtractMax in a min heap or a null/empty heap\n");
		return;
	}

	ELEMENT* maxKey = extract_max(heap->A, heap->size);
	printf("ExtractMax: %d\n", maxKey->key);

	if (heap->ADT == 3)
	{
		delete_min(heap->a, maxKey->minPos, heap->size);
	}
	heap->size -= 1;
}

void extractMin (HEAP* heap)
{
	if (heap == NULL || heap->ADT == 1 || heap->size == 0)
	{
		fprintf(stderr, "Error: ExtractMin in a max heap or a null/empty heap\n");
		return;
	}

	ELEMENT* minKey = extract_min(heap->a, heap->size);
	printf("ExtractMin: %d\n", minKey->key);

	if (heap->ADT == 3)
	{
		delete_max(heap->A, minKey->maxPos, heap->size);
	}
	heap->size -= 1;
}

void insertKey (HEAP* heap, int key)
{
	if (heap == NULL || heap->capacity == heap->size)
	{
		fprintf(stderr, "Error: InsertKey to a null/full heap\n");
		return;
	}

	heap->size++;
	int n = heap->size;

	ELEMENT* data = (ELEMENT*)malloc(sizeof(ELEMENT));
	data->maxPos = n;
	data->minPos = n;

	heap->A[n] = data;
	heap->a[n] = data;

	if (heap->ADT != 2)
	{
		max_heap_insert(heap->A, n, key);
	}
	if (heap->ADT != 1)
	{
		min_heap_insert(heap->a, n, key);
	}
}

void increaseKey (HEAP* heap, int pos, int key)
{
	if (heap == NULL || heap->ADT == 2 || heap->size == 0)
	{
		fprintf(stderr, "Error: IncreaseKey in a min heap or a null/empty heap\n");
		return;
	}

	if (pos > heap->size || key <= heap->A[pos]->key)
	{
		fprintf(stderr, "Error: Invalid position or newKey in IncreaseKey\n");
		return;
	}

	int minPos = heap->A[pos]->minPos;
	max_heap_increase_key(heap->A, pos, key);
	if (heap->ADT == 3)
	{
		min_heap_increase_key(heap->a, heap->size, minPos, key);
	}
}

void decreaseKey (HEAP* heap, int pos, int key)
{
	if (heap == NULL || heap->ADT == 1 || heap->size == 0)
	{
		fprintf(stderr, "Error: DecreaseKey in a max heap or a null/empty heap\n");
		return;
	}

	if (pos > heap->size || key >= heap->a[pos]->key)
	{
		fprintf(stderr, "Error: Invalid position or newKey in DecreaseKey\n");
		return;
	}

	int maxPos = heap->a[pos]->maxPos;
	min_heap_decrease_key(heap->a, pos, key);
	if (heap->ADT == 3)
	{
		max_heap_decrease_key(heap->A, heap->size, maxPos, key);
	}

}
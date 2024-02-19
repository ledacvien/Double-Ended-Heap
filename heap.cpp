#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

using namespace std;

void swap (ELEMENT** a, ELEMENT** b)
{
	ELEMENT *t = *a;
	*a = *b;
	*b = t;
}

void max_heapify (ELEMENT **a, int i, int n)
{
		int left = i*2;
		int right = i*2 + 1;
		int largest;

		if (left <= n && a[left]->key > a[i]->key)
			largest = left;
		else 
			largest = i;
		if (right <= n && a[right]->key > a[largest]->key)
			largest = right;

		if (largest != i)
		{
			swap (a[largest], a[i]);
			// change the maxHeap position in two element
			a[largest]->maxPos = largest;
			a[i]->maxPos = i;
			max_heapify (a, largest, n);
		}
}

void min_heapify (ELEMENT **a, int i, int n)
{
		int left = i*2;
		int right = i*2 + 1;
		int smallest;

		if (left <= n && a[left]->key < a[i]->key)
			smallest = left;
		else 
			smallest = i;
		if (right <= n && a[right]->key < a[smallest]->key)
			smallest = right;

		if (smallest != i)
		{
			swap (a[smallest], a[i]);
			// change the maxHeap position in two element
			a[smallest]->minPos = smallest;
			a[i]->minPos = i;
			min_heapify (a, smallest, n);
		}
}

void buildHeap (HEAP* heap)
{
	if (heap->ADT != 2)
		for (int i = heap->size/2; i > 0; --i)
			max_heapify (heap->A, i, heap->size);

	if (heap->ADT != 1)
		for (int i = heap->size/2; i > 0; --i)
			min_heapify (heap->a, i, heap->size);
}

ELEMENT* extract_max (ELEMENT** a, int n)
{
	ELEMENT* ans = a[1];
	a[1] = a[n];
	a[1]->maxPos = 1;
	max_heapify(a, 1, n - 1);
	return ans;
}

ELEMENT* extract_min (ELEMENT** a, int n)
{
	ELEMENT* ans = a[1];
	a[1] = a[n];
	a[1]->maxPos = 1;
	min_heapify(a, 1, n - 1);
	return ans;
}

void delete_max (ELEMENT** a, int pos, int n)
{
	//cout << pos << ' ' << a[pos]->key << ' ' << n << ' ' << a[n]->key << endl; 
	a[pos] = a[n];
	a[pos]->maxPos = pos;
	n--;
	if (a[pos]->key > a[pos/2]->key)
	{
		while (pos > 1 && a[pos]->key > a[pos/2]->key)
		{
			swap(a[pos], a[pos/2]);
			a[pos]->minPos = pos;
			a[pos/2]->minPos = pos/2;
			pos = pos >> 1;
		}
	}
	else{
		max_heapify(a, pos, n);
	}
}

void delete_min (ELEMENT** a, int pos, int n)
{
	//cout << pos << ' ' << a[pos]->key << ' ' << n << ' ' << a[n]->key << endl;
	a[pos] = a[n];
	a[pos]->minPos = pos;
	n--;
	if (a[pos]->key < a[pos/2]->key)
	{
		while (pos > 1 && a[pos]->key < a[pos/2]->key)
		{
			swap(a[pos], a[pos/2]);
			a[pos]->minPos = pos;
			a[pos/2]->minPos = pos/2;
			pos = pos >> 1;
		}
	}
	else{
		min_heapify(a, pos, n);
	}
}

void max_heap_increase_key (ELEMENT** a, int i, int key)
{
	// pos and key validation is handled in util.cpp
	a[i]->key = key;
	while (i > 1 && a[i/2]->key < a[i]->key)
	{
		swap (a[i/2], a[i]);
		a[i/2]->maxPos = i/2;
		a[i]->maxPos = i;
		i = i >> 1;
	}
}

void max_heap_decrease_key (ELEMENT** a, int n, int i, int key)
{
	// pos and key validation is handled in util.cpp
	a[i]->key = key;
	max_heapify(a, i, n);
}

void min_heap_decrease_key (ELEMENT** a, int i, int key)
{
	// pos and key validation is handled in util.cpp
	a[i]->key = key;
	while (i > 1 && a[i/2]->key > a[i]->key)
	{
		swap (a[i/2], a[i]);
		a[i/2]->minPos = i/2;
		a[i]->minPos = i;
		i = i >> 1;
	}
}

void min_heap_increase_key (ELEMENT** a, int n, int i, int key)
{
	// pos and key validation is handled in util.cpp
	a[i]->key = key;
	min_heapify(a, i, n);
}

void min_heap_insert (ELEMENT** a, int n, int key)
{
	// heap size is increase in util.cpp
	// 2 heap is connected in util.cpp
	a[n]->key = 123456789;
	min_heap_decrease_key (a, n, key);
}

void max_heap_insert (ELEMENT** a, int n, int key)
{
	// heap size is increase in util.cpp
	// 2 heap is connected in util.cpp
	a[n]->key = -123456789;
	max_heap_increase_key (a, n, key);
}

void printElement(ELEMENT* a)
{
	printf("Key=%d\tmaxPos=%d\tminPos=%d\n", a->key, a->maxPos, a->minPos);
	return;
}
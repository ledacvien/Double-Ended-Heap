// Author: Dac Vien Le
// CSE 310
// Prof Xue

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

using namespace std;

int main(int argc, char const *argv[])
{

	if (argc < 3)
	{
		fprintf(stderr, "Usage: ./PJ2 DataStructure Capacity\n");
		fprintf(stderr, "       DataStructure should be in {MaxHeap, MinHeap, DoubleHeap}\n");
		fprintf(stderr, "       Capacity must be a positive integer\n");
		exit(1);
		return 0;
	}

	int ADT;
	int capacity = atoi(argv[2]);
	if ((strcmp(argv[1], "MinHeap") != 0 && strcmp(argv[1], "MaxHeap") != 0 && strcmp(argv[1], "DoubleHeap") != 0) 
		|| (capacity <= 0))
	{
		fprintf(stderr, "Usage: ./PJ2 DataStructure Capacity\n");
		fprintf(stderr, "       DataStructure should be in {MaxHeap, MinHeap, DoubleHeap}\n");
		fprintf(stderr, "       Capacity must be a positive integer\n");
		exit(1);
		return 0;
	}

	if (strcmp(argv[1], "MaxHeap") == 0)
		ADT = 1;
	if (strcmp(argv[1], "MinHeap") == 0)
		ADT = 2;
	if (strcmp(argv[1], "DoubleHeap") == 0)
		ADT = 3;

	
	HEAP heap = {capacity, 0, ADT};

	while (1)
	{
		char word[50];
		scanf("%s", word);

		// Get command (then switch case will get the "positon" and/or "key")
		int command = interpret(word);	

		int* posAndKey = NULL;
		if (command == 4 || command == 7 || command == 8)
		{
			*word = '\0';
			cin.getline(word, 50);
			posAndKey = posKey(command, word);
			if (posAndKey == NULL)
				command = 9;
		}

		int key, position;

		if (command == 0)		// Stop
			break;
		
		switch (command)
		{
			case 1:		// Print to stdout
				printHeap(stdout, &heap);
				break;
			case 2:		// Read .txt file
				readFile(&heap, capacity);
				break;
			case 3:		// Write to .txt file
				writeFile(&heap);
				break;
			case 4:		// Insert Key
				key = *posAndKey;
				insertKey(&heap, key);
				break;
			case 5:		// ExtractMax
				extractMax(&heap);
				break;
			case 6:		// ExtractMin
				extractMin(&heap);
				break;
			case 7:		// IncreaseKey Position Key
				position = *posAndKey;
				key = *(posAndKey+1);
				increaseKey(&heap, position, key);
				break;
			case 8:		// DecreaseKey Position Key
				position = *posAndKey;
				key = *(posAndKey+1);
				decreaseKey(&heap, position, key);
				break;
			default:
				fprintf(stderr, "Error: Invalid command\n");
		}

		delete []posAndKey;
	}
	
	return 0;
}

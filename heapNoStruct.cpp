#include <iostream>

using namespace std;

void swap (int& a, int& b);
void max_heapify (int a[], int i, int n);
void min_heapify (int a[], int i, int n);
int extract_min (int a[], int& n);
int extract_max (int a[], int& n);
void heap_increase_key (int a[], int i, int key);
void min_heap_decrease_key (int a[], int i, int key);
void max_heap_insert (int a[], int& n, int key);
void min_heap_insert (int a[], int& n, int key);
void printArr (int a[], int n);


void max_heapify (int a[], int i, int n)
{
		int left = i*2;
		int right = i*2 + 1;
		int largest;

		if (left <= n && a[left] > a[i])
			largest = left;
		else 
			largest = i;
		if (right <= n && a[right] > a[largest])
			largest = right;

		if (largest != i)
		{
			swap (a[largest], a[i]);
			max_heapify (a, largest, n);
		}
}

void swap (int& a, int& b)
{
	int t = a; a = b; b = t;
}

int extract_max (int a[], int& n)
{
	int ans = a[1];
	a[1] = a[n];
	n--;
	max_heapify(a, 1, n);
	return ans;
}

void max_heap_increase_key (int a[], int i, int key)
{
		if (key < a[i])
			cout << "Invalid" << endl;
		else{
			a[i] = key;
			// int parent = i/2;
			while (i > 1 && a[i/2] < a[i])
			{
				swap (a[i/2], a[i]);
				i = i >> 1;
			}
		}
}

void max_heap_insert (int a[], int& n, int key)
{
		n++;
		a[n] = -123456789;
		max_heap_increase_key (a, n, key);
}

void printArr (int a[], int n)
{
	for (int i = 1; i <= n; ++i)
		printf("a[%d]=%d\n", i, a[i]);
	cout << endl;
}


void min_heapify (int a[], int i, int n)
{
		int left = i*2;
		int right = i*2 + 1;
		int smallest;

		if (left <= n && a[left] < a[i])
			smallest = left;
		else 
			smallest = i;
		if (right <= n && a[right] < a[smallest])
			smallest = right;

		if (smallest != i)
		{
			swap (a[smallest], a[i]);
			min_heapify (a, smallest, n);
		}
}

int extract_min (int a[], int& n)
{
	int ans = a[1];
	swap (a[1], a[n]);
	n--;
	min_heapify(a, 1, n);
	return ans;
}


void min_heap_decrease_key (int a[], int i, int key)
{
		if (key > a[i])
			cout << "Invalid" << endl;
		else{
			a[i] = key;
			// int parent = i/2;
			while (i > 1 && a[i/2] > a[i])
			{
				swap (a[i/2], a[i]);
				i = i >> 1;
			}
		}
}

void min_heap_insert (int a[], int& n, int key)
{
		n++;
		a[n] = 123456789;
		min_heap_decrease_key (a, n, key);
}

void minHeap (int a[], int n)
{
	// extract min
	int pop = extract_min (a, n);

	// increase key
	//min_heap_decrease_key (a, 9, 0);

	// insert key
	//min_heap_insert (a, n, -1);

	printArr (a, n);
}

void maxHeap (int a[], int n)
{
		// extract max
		int pop = extract_max (a, n);
		
		// increase key
		//max_heap_increase_key (a, 10, 18);

		// heap insert
		//max_heap_insert (a, n, 19);
		
		printArr (a, n+1);
}

int main()
{
		//int a[] = {-1, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1};
		//int a[] = {-1, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
		int n = 10;

		//maxHeap (a, n);		
		char c[100];
		char s[100];
		scanf("%s", c);
		scanf("%s", s);
		scanf("%d", &n);

		cout << c << ' ' << s << ' ' << n << endl;
		//minHeap (a, n);
		return 0;
}
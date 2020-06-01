//https://www.pbinfo.ro/?pagina=probleme&id=2632

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void swap(int *x, int *y);

class MinHeap
{
	int *harr; 
	int capacity; 
	int heap_size; 
public:
	// Constructor 
	MinHeap(int capacity);

	void MinHeapify(int i);

	int parent(int i) { return (i - 1) / 2; }

	int left(int i) { return (2 * i + 1); }

	int right(int i) { return (2 * i + 2); }

	int extractMin();


	void insertKey(int k);
};

MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nNu e loc destul\n";
		return;
	}

	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}



int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	int root = harr[0];
	harr[0] = harr[heap_size - 1];
	heap_size--;
	MinHeapify(0);

	return root;
}

void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
int main()
{
	int n, temp,suma=0;
	cin >> n;
	MinHeap h(n);
	for(int i=0;i<n;i++)
	{
		cin >> temp;
		h.insertKey(temp);
	}
	for(int i=0;i<n-1;i++)
	{
		temp= h.extractMin()+ h.extractMin();
		suma += temp;
		h.insertKey(temp);
	}
	cout << suma;
	return 0;
}
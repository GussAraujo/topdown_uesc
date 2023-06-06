#include <iostream>
using namespace std;

int leftChild(int i)
{
    return 3 * i + 1;
}

int middleChild(int i)
{
    return 3 * i + 2;
}

int rightChild(int i)
{
    return 3 * i + 3;
}

int parent(int i)
{
    return (i - 1) / 3;
}

void maxHeapify(int *heap, int heapSize, int i)
{
    int largest = i;
    int l = leftChild(i);
    int m = middleChild(i);
    int r = rightChild(i);

    if (l < heapSize && heap[l] > heap[largest])
        largest = l;

    if (m < heapSize && heap[m] > heap[largest])
        largest = m;

    if (r < heapSize && heap[r] > heap[largest])
        largest = r;

    if (largest != i)
    {
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, heapSize, largest);
    }
}

void insertIntoMaxHeap(int *heap, int &heapSize, int value)
{
    heap[heapSize] = value;
    int currentIndex = heapSize;
    heapSize++;

    while (currentIndex != 0 && heap[parent(currentIndex)] < heap[currentIndex])
    {
        int temp = heap[currentIndex];
        heap[currentIndex] = heap[parent(currentIndex)];
        heap[parent(currentIndex)] = temp;
        currentIndex = parent(currentIndex);
    }

    maxHeapify(heap, heapSize, 0);
}

void buildMaxHeap(int *heap, int heapSize)
{
    for (int i = (heapSize - 1) / 3; i >= 0; i--)
        maxHeapify(heap, heapSize, i);
}

void printHeap(const int *heap, int heapSize)
{
    for (int i = 0; i < heapSize; i++)
        cout << heap[i] << " ";
    cout << endl;
}

int main()
{
    int n = 0;

    while (cin >> n)
    {
        int heap[n];
        int heapSize = 0;

        for (int i = 0; i < n; i++)
        {
            int value;
            cin >> value;
            insertIntoMaxHeap(heap, heapSize, value);
        }

        printHeap(heap, heapSize);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_HEAP_SIZE 500

int comparisons;

typedef struct Heap heap;
struct Heap {
	int size;
	int data[MAX_HEAP_SIZE];
};

heap* create_heap()
{
	heap* new_heap = (heap*) malloc(sizeof(heap));
	int i;
	for (i = 0; i < MAX_HEAP_SIZE; ++i)
	{
		new_heap->data[i] = 0;
	}
	new_heap->size = 0;
	return new_heap;
}

int get_parent_index(heap *heap, int i)
{
	return i/2;
}

void swap(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void enqueue(heap *heap, int item)
{
	if (heap->size >= MAX_HEAP_SIZE) 
	{
		printf("Heap overflow");
	} 
	else 
	{
		heap->data[++heap->size] = item;
		int key_index = heap->size;
		int parent_index = get_parent_index(heap, heap->size);
		while (parent_index >= 1 && heap->data[key_index] > heap->data[parent_index]) 
		{
			swap(&heap->data[key_index], &heap->data[parent_index]);
			key_index = parent_index;
			parent_index = get_parent_index(heap, key_index);
			comparisons++;
		}
	}
}

int main()
{
	int i, p;
	heap *new_heap = create_heap();
	srand(time(NULL));

	FILE *file = fopen("tableheap.txt", "w");

	fprintf(file, "%s\n", "size,comparisons");

	for (i = 0; i < 500; ++i)
	{
		comparisons = 0;
		p = rand() % 500;
		enqueue(new_heap, p);

		fprintf(file, "%d,%d\n", new_heap->size, comparisons);
	}

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons;

typedef struct Node node;
struct Node {
	int item;
	int priority;
	node *next;
};

typedef struct priority_queue priority_queue;
struct priority_queue {
	node *head;
	int size;
};

priority_queue* create_queue()
{
	priority_queue *new_queue = (priority_queue*) malloc(sizeof(priority_queue));
	new_queue->head = NULL;
	new_queue->size = 0;
	return new_queue;
}

int is_empty(priority_queue *pq)				
{
	if (pq->size == 0) return 1;
	else return 0;
}

void enqueue(priority_queue *pq, int i, int p)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = i;
	new_node->priority = p;
	if ((is_empty(pq))  || (p > pq->head->priority)) 
	{
		new_node->next = pq->head;
		pq->head = new_node;
		pq->size++;
		comparisons++;
	} 
	else 
	{
		node *current = pq->head;
		while ((current->next != NULL) && (current->next->priority > p)) 
		{
			current = current->next;
			comparisons++;
		}
		new_node->next = current->next;
		current->next = new_node;
		pq->size++;
	}
}

void print_pq(node *head)		
{
	if(head == NULL) return;
	printf("[%d]",head->priority);
	if(head->next == NULL) printf("\n");
	else printf(" -> ");
	print_pq(head->next);
}

int main()
{
	int i, p;
	priority_queue *pq = create_queue();

	srand(time(NULL));

	FILE *file = fopen("tablepq.txt", "w");

	fprintf(file, "%s\n", "size,comparisons");

	for (i = 0; i < 500; ++i)
	{
		comparisons = 0;
		p = rand() % 500;
		enqueue(pq, i, p);

		fprintf(file, "%d,%d\n", pq->size, comparisons);
	}

	//print_pq(pq->head);
	
	return 0;
}
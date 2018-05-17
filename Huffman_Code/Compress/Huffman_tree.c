#include "Huffman_tree.h"

struct Binary_tree {
	unsigned char byte;
	unsigned long long int frequency;
	struct Binary_tree *left;
	struct Binary_tree *right;
	struct Binary_tree *next;
};

struct Priority_queue {
	int size;
	binary_tree *head;
};

binary_tree *create_tree (binary_tree *left, binary_tree *right, unsigned char byte, unsigned long long int frequency) {
    binary_tree *new_tree = malloc(sizeof(binary_tree));
    new_tree->next = NULL;
    new_tree->left = left;
    new_tree->right = right;
    new_tree->byte = byte;
    new_tree->frequency = frequency;
    return new_tree;
}

binary_tree *enqueue (priority_queue *pq, binary_tree *left, binary_tree *right, unsigned long long int frequency, unsigned char byte) {
	binary_tree *new_tree = create_tree(left, right, byte, frequency);
	if((is_empty(pq)) || (frequency <= pq->head->frequency)) {
		new_tree->next = pq->head;
		pq->head = new_tree;
	} else {
		binary_tree *current = pq->head;
		while((current->next != NULL) && (current->next->frequency < frequency)) {
			current = current->next;
		}
		new_tree->next = current->next;
		current->next = new_tree;
	}
	pq->size++;
	return new_tree;
}

binary_tree *dequeue(priority_queue *pq) {
	if(is_empty(pq)) {
		printf("Queue Underflow!\n");
		return NULL;
	} else {
		binary_tree *dequeued = pq->head;
		pq->head = pq->head->next;
		dequeued->next = NULL;
		return dequeued;
	}
}

binary_tree *create_tree_bytes (priority_queue *queue, int size_tree) {
	binary_tree *tree = malloc(sizeof(binary_tree));
	tree->left = dequeue(queue);
	tree->right = dequeue(queue);
	unsigned long long int sum_frequency = tree->left->frequency + tree->right->frequency;
	tree = enqueue(queue, tree->left, tree->right, sum_frequency, '*');
	return tree;
}
void print_pre_order (binary_tree *tree, FILE *file_write) {
	if(tree != NULL) {
		if(tree->left == NULL && tree->right == NULL && tree->byte == '*') {
			fputc('\\', file_write);	
		}
		if(tree->byte == '\\') {
			fputc('\\', file_write);
		}
		fputc(tree->byte, file_write);
		print_pre_order(tree->left, file_write);
		print_pre_order(tree->right, file_write);
	}
}


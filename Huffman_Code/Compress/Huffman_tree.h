
#ifndef PROJECTHUFFMAN_HUFFMAN_TREE_H
#define PROJECTHUFFMAN_HUFFMAN_TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Huffman_dictionary.h"
#include "Compress.h"

typedef struct Binary_tree binary_tree;

typedef struct Priority_queue priority_queue;

binary_tree *create_tree (binary_tree *left, binary_tree *right, unsigned char byte, unsigned long long int frequency);

binary_tree *enqueue (priority_queue *pq, binary_tree *left, binary_tree *right, unsigned long long int frequency, unsigned char byte);

binary_tree *dequeue(priority_queue *pq);

binary_tree *create_tree_bytes (priority_queue *queue, int size_tree);

void print_pre_order (binary_tree *tree, FILE *file_write);

#endif

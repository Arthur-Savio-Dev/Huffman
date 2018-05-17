
#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "Huffman_tree.h"
#include "Huffman_binary.h"
#include "Compress.h"

typedef struct Binary_tree binary_tree;

int get_trash_size(FILE* file);

int get_tree_size(FILE* file);

unsigned char* get_pre_order(FILE* file, int tree_size);

binary_tree *create_empty_tree();

binary_tree *add_node(unsigned char byte, int frq);

binary_tree *rebuild_tree(binary_tree *tree, int tree_size, unsigned char *string_tree);

int get_file_size(FILE *file, int tree_size);

void search_tree(FILE *file, FILE *new_file, binary_tree *tree, int k, int trash_size, int tree_size);

void read_bytes_decompress(char directory[], char new_directory[]);

#endif


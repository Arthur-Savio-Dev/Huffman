#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Huffman_tree.h"
#include "Huffman_dictionary.h"
#include "Huffman_binary.h"

typedef struct Node node;

typedef struct Hash_table hash_table;

typedef struct Binary_tree binary_tree;

typedef struct Priority_queue priority_queue;

typedef struct Priority_queue_dictionary queue_dictionary;

bool is_empty (priority_queue *pq);

hash_table *create_hash ();

priority_queue *create_queue();

int make_size_trash (hash_table *hash);

void set_last_byte (unsigned char last_byte[], FILE *file_write);

void write_file (binary_tree *tree, hash_table *hash, char directory[], char new_directory[], int size_tree);

void compress (binary_tree *tree, char directory[], char new_directory[], int size_tree);

void read_bytes_compress (char directory[], char new_directory[], int size_tree);

#endif

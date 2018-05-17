#ifndef PROJECTHUFFMAN_HUFFMAN_DICTIONARY_H
#define PROJECTHUFFMAN_HUFFMAN_DICTIONARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Compress.h"
#include "Huffman_tree.h"

typedef struct Node node;

typedef struct Hash_table hash_table;

typedef struct Binary_tree binary_tree;

node *create_list();

hash_table *add_hash_dictionary (hash_table *hash, unsigned char byte, unsigned long long int frequency, unsigned char bits[]);

void encode (hash_table *hash, binary_tree *tree, int c, unsigned char bits[]);

#endif

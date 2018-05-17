
#include "Huffman_dictionary.h"

struct Node {
	unsigned char byte;
    unsigned char bits[16];
	unsigned long long int frequency;
	struct Node *next;
};

struct Hash_table{
	int size;
	node *table[256];
};

struct Binary_tree {
	unsigned char byte;
	unsigned long long int frequency;
	struct Binary_tree *left;
	struct Binary_tree *right;
	struct Binary_tree *next;
};

node *create_list() {
    node *list = malloc(sizeof(list));
    list->next = NULL;
    return list;
}

hash_table *add_hash_dictionary (hash_table *hash, unsigned char byte, unsigned long long int frequency, unsigned char bits[]) {
	int h = byte % 257;
	if(hash->table[h] == NULL) {
		node *new_node = malloc(sizeof(node));
		strcpy(new_node->bits, bits);
		new_node->byte = byte;
		new_node->frequency = frequency;
		hash->table[h] = new_node;
		hash->size++;
	}
	return hash;
}

void encode (hash_table *hash, binary_tree *tree, int c, unsigned char bits[]) {
	if(tree->left != NULL) {
	    bits[c] = '0';
        c++;
		encode(hash, tree->left, c, bits);
        bits[c--] = '\0';
	}
	if(tree->right != NULL) {
	    bits[c] = '1';
        c++;
		encode(hash, tree->right, c, bits);
        bits[c--] = '\0';
	}
	if(tree->left == NULL && tree->right == NULL) {
		hash = add_hash_dictionary(hash, tree->byte, tree->frequency, bits);
		c = 0;
		int h = tree->byte % 257;
	}
}


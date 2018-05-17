#include "Compress.h"

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

struct Priority_queue {
	int size;
	binary_tree *head;
};

struct Priority_queue_dictionary {
	node *head_dictionary;
};

bool is_empty (priority_queue *pq) {
    if(pq->head == NULL)
        return true;
    else
        return false;
}

hash_table *create_hash () {
	hash_table *new_hash = malloc(sizeof(hash_table));
	new_hash->size = 0;
	int i;
	for(i = 0; i < 256; i++) {
		new_hash->table[i] = NULL;
	}
	return new_hash;
}

hash_table *add_hash (hash_table *hash, unsigned char byte) {
	int h = byte % 257;
	if(hash->table[h] == NULL) {
		node *new_node = malloc(sizeof(node));
		new_node->byte = byte;
		new_node->frequency = 1;
		hash->table[h] = new_node;
		hash->size++;
	} else {
		hash->table[h]->frequency++;
	}
	return hash;
}

priority_queue *create_queue () {
	priority_queue *queue = malloc(sizeof(priority_queue));
	queue->head = NULL;
	queue->size = 0;
	return queue;
}

int make_size_trash (hash_table *hash) {
	int size = 0, i, t, h;
	for(i = 0; i < 256; i++) {
		if(hash->table[i] != NULL) {
			size += hash->table[i]->frequency * strlen(hash->table[i]->bits);
		}
	}
	size = 8 - (size % 8);
	return size;
}
void set_last_byte (unsigned char last_byte[], FILE *file_write) {
	bool control = false;
	int k = 7, i;
	unsigned char bit_write = 0;
	for(i = 0; i < strlen(last_byte); i++) {
		if(control) {
			if(last_byte[i] == '1') {
				bit_write = set(bit_write, k);
			}
			k--;
		}
		if(last_byte[i] == '.') {
			control = true;
		}
	}
	fputc(bit_write, file_write);
}

void write_file (binary_tree *tree, hash_table *hash, char directory[], char new_directory[], int size_tree) {
	FILE *file = fopen(directory, "rb");
	FILE *file_write = fopen(new_directory, "wb");
	unsigned char string[3] = "000", tree_trash_size[16], string2[13] = "0";
	unsigned char byte, bit_write = 0, string_bit[8], last_byte[8];
	int h, i, k = 8;

	tree_trash_size[0] = '\0';
	string[3] = '\0';

	int size_trash = make_size_trash(hash);
	to_binary(size_trash, string, 0);
	strcpy(tree_trash_size, string);

	to_binary(size_tree, string2, 0);
	for(i = 3; i < 16 - strlen(string2); i++) {
		tree_trash_size[i] = '0';
		tree_trash_size[i + 1] = '\0';
	}
	strcat(tree_trash_size, string2);
	for(i = 0; i < 16; i++) {
		k--;
		if(tree_trash_size[i] == '1') {
			bit_write = set(bit_write, k);
		}
		if(k == 0) {
			fputc(bit_write, file_write);
			k = 8;
			bit_write = '\0';
		}
	}

	print_pre_order(tree, file_write);

	while(!feof(file)) {
		fread(&byte, sizeof(byte), 1, file);
		h = byte % 257;
		strcpy(string_bit, hash->table[h]->bits);
		
		for(i = 0; i < strlen(string_bit); i++) {
			k--;
			if(string_bit[i] == '1') {
				bit_write = set(bit_write, k);
			}
			if(k == 0) {
				fputc(bit_write, file_write);
				k = 8;
				bit_write = 0;
				string_bit[i] = '.';
				strcpy(last_byte, string_bit);
			}
		}
	}
	if(strlen(last_byte) > 0) {
		set_last_byte(last_byte, file_write);
	} 
	fclose(file_write);
}

void compress (binary_tree *tree, char directory[], char new_directory[], int size_tree) {
	unsigned char bits[16] = "";
    hash_table *hash = create_hash();
	encode(hash, tree, 0, bits);
	
	printf("The file is be compress...\n");
	write_file(tree, hash, directory, new_directory, size_tree);
}

void read_bytes_compress (char directory[], char new_directory[], int size_tree) {
    priority_queue *pq = create_queue();
    hash_table *hash = create_hash();
    binary_tree *tree = malloc(sizeof(binary_tree));
    node *current;
    int i = 0;
	unsigned char string;
	FILE *file = fopen(directory, "rb");

	if(file == NULL) {
		printf("File could not be found!\n");
		exit(0);
	}
	while(!feof(file)) {
		fread(&string, sizeof(string), 1, file);
		if(!feof(file)) {
			hash = add_hash(hash, string);
		}
	}
	for(i = 0; i < 256; i++) {
		current = hash->table[i];
		if(current != NULL) {
			tree = enqueue(pq, NULL, NULL, current->frequency, current->byte);
			size_tree++;
			if(tree->byte == '*' || tree->byte == '\\')
				size_tree++;
		}
	}

	while(pq->size != 1) {
		pq->size -= 2;
		tree = create_tree_bytes(pq, size_tree);
		size_tree++;
	}
	compress(tree, directory, new_directory, size_tree);
	printf("Your file was successfully compressed!! \n");
	printf("%d\n", size_tree);
	fclose(file);
}
#include "Decompress.h"

typedef struct Binary_tree binary_tree;

struct Binary_tree {
	unsigned char byte;
	unsigned long long int frequency;
	struct Binary_tree *left;
	struct Binary_tree *right;
	struct Binary_tree *next;
};

int get_trash_size(FILE* file){
	int i, trash_size = 0;
	rewind(file);
	unsigned char aux1;
	fscanf(file, "%c", &aux1);

	for(i = 7; i >= 5; --i)
	{
		if(aux1 & (1 << i))
		{
			trash_size += pow(2, (i-5));
		}
	}

	rewind(file);
	return trash_size;
}

int get_tree_size(FILE* file){
	int i, aux_position = 12, tree_size = 0;
	unsigned char byte1, byte2;
	fscanf(file, "%c%c", &byte1, &byte2);

	for (i = 4; i >= 0; --i)
	{
		if (byte1 & (1 << i))
		{
			tree_size += pow(2, aux_position);
		}
		--aux_position;
	}

	for (i = 7; i >= 0; --i)
	{
		if (byte2 & (1 << i))
		{
			tree_size +=  pow(2, aux_position);
		}
		--aux_position;
	}
	return tree_size;
}

unsigned char* get_pre_order(FILE* file, int tree_size){
	int i;
	unsigned char* tree = (unsigned char*) malloc(tree_size * sizeof(unsigned char));

	for (i = 0; i < tree_size; ++i){
		fscanf(file, "%c", &tree[i]);
	}
	return tree;
}

binary_tree *create_empty_tree(){
	return NULL;
}

binary_tree *add_node(unsigned char byte, int frq){
	binary_tree *node = (binary_tree*) malloc(sizeof(binary_tree));
	node->byte = byte;
	node->frequency = frq;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	return node;
}

int control=0;

binary_tree *rebuild_tree(binary_tree *tree, int tree_size, unsigned char *string_tree){
    binary_tree *new_node_tree;
    if(control >= tree_size) {
        return NULL;
    }

    if(string_tree[control] == '*') {
        new_node_tree = add_node(string_tree[control], 0);
        control++;
        new_node_tree->left = rebuild_tree(tree, tree_size, string_tree);
        control++;
        new_node_tree->right = rebuild_tree(tree, tree_size, string_tree);
    }
    else
    	{
    		if (string_tree[control] == '\\')
    		{
                      control++;
    			new_node_tree = add_node(string_tree[control], 0);
    		}
    		else
    		{
    			new_node_tree = add_node(string_tree[control], 0);
    		}
    	}

    return new_node_tree;
}

int get_file_size(FILE *file, int tree_size){
	unsigned long long int size = 0;
	unsigned char byte;

	while(!feof(file)) {
		fread(&byte, sizeof(byte), 1, file);
		size++;
	}
	rewind(file);
	//printf("Size: %lld\n", size-1);
	return size-1;
}

void search_tree(FILE *file, FILE *new_file, binary_tree *tree, int k, int trash_size, int tree_size){
	binary_tree *root, *aux;
	int  i, file_size, comeco = 1;
	unsigned char byte, buffer;

	root = tree;
	aux = tree;
	file_size = get_file_size(file, tree_size);

	fseek(file, 2+tree_size, SEEK_SET);

	while(comeco<file_size) {
		fread(&byte, sizeof(byte), 1, file);
		comeco++;
		for(i=7;i>=0;i--){
			buffer = byte;
			if(aux->left == NULL && aux->right == NULL){			
				fprintf(new_file, "%c", aux->byte);
				aux = root;
			}

			if(isBitiSet(byte, i)){
				aux = aux->right;
			}else if(!isBitiSet(byte, i)){
				aux = aux->left;
			}
		}
	}
	fread(&byte, sizeof(byte), 1, file);
	i = 8;
	while(i >= trash_size){
		
		if(aux->left == NULL && aux->right == NULL){			
			fprintf(new_file, "%c", aux->byte);
			aux = root;
		}
		else if(isBitiSet(byte, i)){
			i--;
			aux = aux->right;
		}else if(!isBitiSet(byte, i)){
			i--;
			aux = aux->left;
		}
	}
}

void read_bytes_decompress(char directory[], char new_directory[]) {
	FILE *file = fopen(directory, "rb");
	FILE *new_file = fopen(new_directory, "w");
	
	int i, trash_size, tree_size;
	trash_size = get_trash_size(file);
	tree_size = get_tree_size(file);
	unsigned char *pre_order_tree = NULL;
  	pre_order_tree = get_pre_order(file, tree_size);
  	binary_tree *rebuilded_tree = malloc(sizeof(binary_tree));
	rebuilded_tree = rebuild_tree(rebuilded_tree, tree_size,  pre_order_tree);
	search_tree(file, new_file, rebuilded_tree, 0, trash_size, tree_size);
	fclose(file);
	fclose(new_file);
}


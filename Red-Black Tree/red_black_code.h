#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef RED_BLACK_CODE_H_
#define RED_BLACK_CODE_H_

typedef struct Red_black red_black;

typedef struct root_rb root;

//Creates an empty tree and sets it as root
root_rb *create_root_tree ();

//Creates a new node of the tree
red_black *add_red_black (int data);

//Checks the value of the node's brother. If they're equals, returns the parameter node. Else, it returns the node's brother.
red_black *brother_node (red_black *rb);

//Returns the father of a node's brother
red_black *uncle_node (red_black *rb);

//Returns the grandfather node of the tree
red_black *grand_father_node (red_black *rb);

//Checks the color of a node
int node_color (red_black *rb);

//Changes the color of a node, but doesn't affect the values or content of the tree
void change_color (red_black *rb);

/*B node changes place with A node.
A node becomes the left son of B node.
B node recieves the color of A node and A node turns to red, may a color correction for A node be necessary*/
void left_rotate (red_black *node_a);

/*The A node changes position with B node and becomes B node's right son.
B node recieves the color of A node and A node becomes red*/
void right_rotate (red_black *node_a);

//Replaces a node with a new node, according to the value
void replace_node (root *root_tree, red_black *rb, red_black *new_rb);

/* Verifies if the root is NULL and creates a new root if needs, or it inserts the new node and colors the tree*/
void insert_red_black (red_black *rb, void *data);

//Recolors the tree to maintain the right properties of a red-black tree
void case1 (root *root_tree, red_black *rb);
void case2 (root *root_tree, red_black *rb);
void case3 (root *root_tree, red_black *rb);
void case4 (root *root_tree, red_black *rb);
void case5 (root *root_tree, red_black *rb);

//Deletes a node of the tree and checks the properties to rebalance and maintain the properties
void delete_red_black (Root *root_tree, int value);

void delete_case1 (root *root_tree, red_black *rb);
void delete_case2 (root *root_tree, red_black *rb);
void delete_case3 (root *root_tree, red_black *rb);
void delete_case4 (root *root_tree, red_black *rb);
void delete_case5 (root *root_tree, red_black *rb);
void delete_case6 (root *root_tree, red_black *rb);

//Prints the tree in pre order
void print_pre_order (root *root_tree);

//Prints the tree in order
void print_in_order (red_black *rb);

//Returns the node with maximum value
red_black *node_max (red_black *rb);

//Searches a value on the tree
red_black *search(root *root_rb, int value);

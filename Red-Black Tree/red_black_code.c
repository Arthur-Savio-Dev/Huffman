/*
 * Red-Black's Code
 *
 *  Created on: 17 de abr de 2018
 *      Author: Arthur
 */

#include "red_black_code.h"

#define RED 1
#define BLACK 0

struct Red_black {
	struct Red_black *left;
	struct Red_black *right;
	struct Red_black *parent;
	int color;
	int data;
};

struct root_rb {
	red_black *root_tree;
};

red_black *add_red_black (int data) {
	red_black *new_rb = malloc(sizeof(red_black));
	new_rb->left = NULL;
	new_rb->right = NULL;
	new_rb->parent = NULL;
	new_rb->data = data;
	new_rb->color = RED;
	return new_rb;
}

root *create_root_tree () {
	root *root_rb = malloc(sizeof(root));
	root_rb->root_tree = NULL;
	return root_rb;
}

red_black *grand_father_node (red_black *rb) {
	return rb->parent->parent;
}

red_black *brother_node (red_black *rb) {
	if(rb == rb->parent->left)
		return rb->parent->right;
	else
		return rb->parent->left;
}

red_black *uncle_node (red_black *rb) {
	return brother_node(rb->parent);
}

red_black *node_max (red_black *rb) {
	while(rb->right != NULL) {
		rb = rb->right;
	}
	return rb;
}

int node_color (red_black *rb) {
	if(rb == NULL)
		return BLACK;
	else
		return rb->color;
}

void left_rotate (red_black *node_a, root *root_rb) {
	red_black *node_b = node_a->right;
	replace_node(root_rb, node_a, node_b);
	node_a->right = node_b->left;
	if(node_b->left != NULL)
		node_b->left->parent = node_a;
	node_b->left = node_a;
	node_a->parent = node_b;
}

void right_rotate (red_black *node_a, root *root_rb) {
	red_black *node_b = node_a->left;
	replace_node(root_rb, node_a, node_b);
	node_a->left = node_b->right;
	if(node_b->right != NULL) {
		node_b->right->parent = node_a;
	}
	node_b->right = node_a;
	node_a->parent = node_b;
}

void replace_node (root *root_rb, red_black *rb, red_black *new_rb) {
	if(rb->parent == NULL) {
		root_rb->root_tree = new_rb;
	} else {
		if(rb == rb->parent->left)
			rb->parent->left = new_rb;
		else
			rb->parent->right = new_rb;
	}
	if(new_rb != NULL) {
		new_rb->parent = rb->parent;
	}
}

void insert_red_black (root *root_rb, int data) {
	red_black *new_red_black = add_red_black(data);
	if(root_rb->root_tree == NULL) {
		root_rb->root_tree = new_red_black;
	} else {
		red_black *rb = root_rb->root_tree;
		for(;;) {
			if(data == rb->data) {
				free(new_red_black);
				return;
			} else if (data < rb->data) {
				if(rb->left == NULL) {
					rb->left = new_red_black;
					break;
				} else {
					rb = rb->left;
				}
			} else {
				if(rb->right == NULL) {
					rb->right = new_red_black;
					break;
				} else {
					rb = rb->right;
				}
			}
		}
		new_red_black->parent = rb;
	}
	case1(root_rb, new_red_black);
}

void case1 (root *root_tree, red_black *rb) {
	if(rb->parent == NULL)
		rb->color = BLACK;
	else
		case2(root_tree, rb);
}

void case2 (root *root_tree, red_black *rb) {
	if(rb->parent->color == BLACK)
		return;
	else
		case3(root_tree, rb);
}

void case3 (root *root_tree, red_black *rb) {
	if(node_color(uncle_node(rb)) == BLACK) {
		case4(root_tree, rb);
	} else {
		rb->parent->color = BLACK;
		uncle_node(rb)->color = BLACK;
		grand_father_node(rb)->color = RED;
		case1(root_tree, grand_father_node(rb));
	}
}

void case4 (root *root_tree, red_black *rb) {
	if((rb == rb->parent->right) && (rb->parent == grand_father_node(rb)->left)) {
		left_rotate(rb->parent, root_tree);
		rb = rb->left;
	} else if ((rb == rb->parent->left) && (rb->parent == grand_father_node(rb)->right)) {
		right_rotate(rb->parent, root_tree);
		rb = rb->right;
	}
	case5(root_tree, rb);
}

void case5 (root *root_tree, red_black *rb) {
	rb->parent->color = BLACK;
	grand_father_node(rb)->color = RED;

	if((rb == rb->parent->left) && (rb->parent == grand_father_node(rb)->left)) {
		right_rotate(grand_father_node(rb), root_tree);
	} else {
		left_rotate(grand_father_node(rb), root_tree);
	}
}

red_black *search(root *root_rb, int value) {
	red_black *rb = root_rb->root_tree;
	while(rb != NULL) {
		if(value == rb->data) {
			return rb;
		} else if (value < rb->data) {
			rb = rb->left;
		} else {
			rb = rb->right;
		}
	}
	return rb;
}

void delete_red_black (root *root_tree, int value) {
	red_black *child;
	red_black *rb = search(root_tree, value);
	if(rb == NULL)
		return;
	if(rb->left != NULL && rb->right != NULL) {
		red_black *max = node_max(rb->left);
		rb->data = max->data;
		rb = max;
	}

	if(rb->right == NULL) {
		child = rb->left;
	} else {
		child = rb->right;
	}

	if(rb->color == BLACK) {
		rb->color = node_color(child);
		delete_case1 (root_tree, rb);
	}
	replace_node(root_tree, rb, child);
	if(rb->parent == NULL && child != NULL)
		child->color = BLACK;
	free(rb);
}

void delete_case1 (root *root_tree, red_black *rb) {
	if(rb->parent == NULL)
		return;
	else
		delete_case2(root_tree, rb);
}

void delete_case2 (root *root_tree, red_black *rb) {
	if(brother_node(rb)->color == RED) {
		rb->parent->color = RED;
		brother_node(rb)->color = BLACK;
		if(rb == rb->parent->left) {
			left_rotate(rb->parent, root_tree);
		} else {
			right_rotate(rb->parent, root_tree);
		}
	}
	delete_case3(root_tree, rb);
}

void delete_case3 (root *root_tree, red_black *rb) {
	if(node_color(rb->parent) == BLACK && node_color(brother_node(rb)) == BLACK && node_color(brother_node(rb)->right) == BLACK && node_color(brother_node(rb)->left) == BLACK) {
		brother_node(rb)->color = RED;
		delete_case1(root_tree, rb->parent);
	} else {
		delete_case4(root_tree, rb);
	}
}

void delete_case4 (root *root_tree, red_black *rb) {
	if (node_color(rb->parent) == RED && node_color(brother_node(rb)) == BLACK && node_color(brother_node(rb)->left) == BLACK && node_color(brother_node(rb)->right) == BLACK) {
		brother_node(rb)->color = RED;
		rb->parent->color = BLACK;
	} else {
		delete_case5(root_tree, rb);
	}
}

void delete_case5 (root *root_tree, red_black *rb) {
	if (rb == rb->parent->left && node_color(brother_node(rb)) == BLACK && node_color(brother_node(rb)->left) == RED && node_color(brother_node(rb)->right) == BLACK) {
	    brother_node(rb)->color = RED;
	    brother_node(rb)->left->color = BLACK;
	    right_rotate(brother_node(rb), root_tree);
	} else if (rb == rb->parent->right && node_color(brother_node(rb)) == BLACK && node_color(brother_node(rb)->right) == RED
			&& node_color(brother_node(rb)->left) == BLACK) {
	    brother_node(rb)->color = RED;
	    brother_node(rb)->right->color = BLACK;
	    left_rotate(brother_node(rb), root_tree);
	}
	    delete_case6(root_tree, rb);
}

void delete_case6 (root *root_tree, red_black *rb) {
	brother_node(rb)->color = node_color(rb->parent);
	rb->parent->color = BLACK;
	if (rb == rb->parent->left) {
		brother_node(rb)->right->color = BLACK;
	    left_rotate(rb->parent, root_tree);
	} else {
		brother_node(rb)->left->color = BLACK;
	    right_rotate(rb->parent, root_tree);
	}
}

void print_pre_order (red_black *rb) {
	if(rb != NULL) {
		printf("Value: %d Color:%d\n", rb->data, rb->color);
		print_pre_order(rb->left);
		print_pre_order(rb->right);
	}
}

void print_in_order (red_black *rb) {
	if(rb != NULL) {
		print_in_order(rb->left);
		printf("Value: %d ", rb->data);
		if(rb->color == 0)
			printf("Color: BLACK\n");
		else
			printf("Color: RED\n");
		print_in_order(rb->right);
	}
}

int main () {
	root *rt = create_root_tree ();

	insert_red_black (rt, 8);
	insert_red_black (rt, 9);
	insert_red_black (rt, 15);
	insert_red_black (rt, 22);
	insert_red_black (rt, 5);
	insert_red_black (rt, 2);

	//delete_red_black(rt, 15);
	//delete_red_black(rt, 22);

	red_black *rb = rt->root_tree;
	print_in_order (rb);

	return 0;
}

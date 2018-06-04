#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "btree.h"

Node* get_new_node(int data) {

	Node* ret = malloc(sizeof(Node));
	ret->left = NULL;
	ret->right = NULL;
	ret->parent = NULL;
	ret->data = data;

	return ret;
}

void display_data(Node* node) {

	if (node != NULL) {
		printf("%d->", node->data);
	}
	else { 
		printf("[]->"); 
	}
}

void display_node(Node* node) {

	printf("\n");
	printf("\t%d\n", node->data);
	printf("       /  \\\n");

	if (node->left != NULL)
		printf("      %d", node->left->data);
	else 
		printf("      X");

	if (node->right != NULL)
		printf("   %d\n", node->right->data);  
	else
		printf("   X");

	printf("\n");
}

int compare_nodes(Node* lhs, Node* rhs) { 
	if (lhs != NULL && rhs != NULL) {
		if (lhs->data == rhs->data) 
			return 0;
		else if (lhs->data > rhs->data)
			return 1;
		else 
			return -1;
	} 
	else if (lhs != NULL)
		return 1;
	else if (rhs != NULL)
		return -1;
	else 
		return 0;
}

void show_tree(Node* node, fptr_display display) {
	display(node);
	printf("\n");

}

void in_order(Node* root_node, fptr_display display) {

	if (root_node != NULL) {
		in_order(root_node->left, display);
		display(root_node);
		in_order(root_node->right, display);
	}
}

void add_node(Node** root_marker, fptr_compare compare, int value) {

	Node* new_node = get_new_node(value);
	Node* root = *root_marker;
	if (root == NULL) {
		root = new_node;
		*root_marker = root;
		return;
	}

	// loop.  invariant: we are at a root node 
	// if the data is less than root go left, otherwise go right
	while (1) {
		if (compare(root,new_node) >= 0) {
			// go left
			// if there is no current left node add the new node and break
			if (root->left == NULL) {
				root->left = new_node;
				break;

			} else {
				root = root->left;
			}
		} 
		else {
			// go right
			if (root->right == NULL) {
				root->right = new_node;
				break;
			}
			else {
				root = root->right;
			}
		}
	}
}

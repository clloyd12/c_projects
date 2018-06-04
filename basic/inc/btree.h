#ifndef BTREE_H
#define BTREE_H

struct _node {
	struct _node* left;
	struct _node* right;
	struct _node* parent;
	int data;
};

typedef struct _node Node;

// pointer to a function
typedef int (*fptr_compare)(Node* lhs, Node* rhs);
typedef void (*fptr_display)(Node* node);

int compare_nodes(Node* lhs, Node* rhs);  
void display_data(Node* node);
void display_node(Node* node); 
void show_tree(Node* node, fptr_display display); 
void add_node(Node** root_marker, fptr_compare compare, int value); 
void in_order(Node* root_node, fptr_display display); 


#endif



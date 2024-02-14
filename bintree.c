#include "bintree.h"
#include "str.h"
#include <stdlib.h>
#include <stdio.h>

BinTreeNode * malloc_bintreenode(int data) {
	BinTreeNode * node = (BinTreeNode *)malloc(sizeof(BinTreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void free_bintreenode(BinTreeNode * node) {
	free(node); //We are not responsible for freeing its children
}

void recursive_node_free(BinTreeNode * root);

BinTree * malloc_bintree() {
	BinTree * tree = (BinTree *)malloc(sizeof(BinTree));
	tree->root = NULL;
	return tree;
}

void recursive_node_free(BinTreeNode * root) {
	if (root == NULL) {
		return;
	}
	if (root->left != NULL) {
		recursive_node_free(root->left);
	}
	if (root->right != NULL) {
		recursive_node_free(root->right);
	}
	root->left = NULL;
	root->right = NULL;
	free_bintreenode(root);
}

void free_bintree(BinTree * tree) {
	recursive_node_free(tree->root);
	free(tree);
}

BinTreeNode* tree_getroot(BinTree *tree) {
	return tree->root;
}

void tree_add(BinTree *tree, int data) {
	if (tree->root == NULL) {
		tree->root = malloc_bintreenode(data);
		return;
	}
	BinTreeNode * current = tree->root;
	while (1) {
		if (data < current->data) {
			if (current->left == NULL) {
				current->left = malloc_bintreenode(data);
				return;
			}
			current = current->left;
		} else {
			if (current->right == NULL) {
				current->right = malloc_bintreenode(data);
				return;
			}
			current = current->right;
		}
	}
}

void tree_remove(BinTree *tree, int data) {
	BinTreeNode * current = tree->root;
	BinTreeNode * parent = NULL;
	while (current != NULL) {
		if (data < current->data) {
			parent = current;
			current = current->left;
		} else if (data > current->data) {
			parent = current;
			current = current->right;
		} else {
			if (current->left == NULL && current->right == NULL) {
				if (parent == NULL) {
					tree->root = NULL;
				} else if (parent->left == current) {
					parent->left = NULL;
				} else {
					parent->right = NULL;
				}
				free_bintreenode(current);
				return;
			} else if (current->left == NULL) {
				if (parent == NULL) {
					tree->root = current->right;
				} else if (parent->left == current) {
					parent->left = current->right;
				} else {
					parent->right = current->right;
				}
				free_bintreenode(current);
				return;
			} else if (current->right == NULL) {
				if (parent == NULL) {
					tree->root = current->left;
				} else if (parent->left == current) {
					parent->left = current->left;
				} else {
					parent->right = current->left;
				}
				free_bintreenode(current);
				return;
			} else {
				BinTreeNode * replacement = current->right;
				while (replacement->left != NULL) {
					replacement = replacement->left;
				}
				current->data = replacement->data;
				tree_remove(tree, replacement->data);
				return;
			}
		}
	}

}

BinTreeNode* tree_find(BinTree *tree, int data) {
	BinTreeNode * current = tree->root;
	while (current != NULL) {
		if (data < current->data) {
			current = current->left;
		} else if (data > current->data) {
			current = current->right;
		} else {
			return current;
		}
	}
	return NULL;
}

//The return of this would be the total rows completed thus far
int recursive_node_print(BinTreeNode * root, String * str, int row) {
	if (root == NULL) {
		return row;
	}
	int deepLeft, deepRight;
	if (root->right != NULL) {
		deepRight = recursive_node_print(root->right, str, row + 1);
	} else {
		deepRight = row;
	}
	if (root->left != NULL) {
		deepLeft = recursive_node_print(root->left, str, row + 1);
	} else {
		deepLeft = row;
	}
	//We can now see how many rows are under this one
	int deep = deepLeft > deepRight ? deepLeft : deepRight;
	//Depth tells us how many spaces to add
	string_insert_int(str, 0, root->data);
	for (int i = 0; i < deep; i++) {
		string_insert(str, 0, ' ');
	}
	
	return deep;
	
}

void tree_print(BinTree *tree) {
	//This is a recursive function that constructs a string from str.h
	String * str = malloc_string();
	//we must now recursively build the string
	recursive_node_print(tree->root, str, 0);
	//print the string
	char * cstr = string_to_cstr(str);
	printf("%s\n", cstr);
	//free the string
	free(cstr);
	free_string(str);
}



/**
 * @file bst.c
 * @author John Nguyen (jn866@drexel.edu)
 * @date 2024-02-14
 * @section DESCRIPTION
 * 
 * This file contains the implementation of a binary search tree
 */

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

/**
	Create a new empty Binary Search Tree
	@return Pointer to empty BST
 */
BST* newBST();

/**
	Free all the memory allocated to the BST
	@param T is the tree to delete from memory
 */
void deleteBST(BST* T);

/**
	Insert a value into the BST. Ignore duplicates.
	@param T is the tree to insert into
	@param target is the value to insert
 */
void insert(BST* T, int target);

/**
	Find a value in the BST.
	@param T is the tree to search
	@param target is the value to search for
	@return true if found and false if not in tree
 */
bool find(BST* T, int target);

/**
	Delete a value from the tree
	@param T is the tree to delete from
	@param target is the value to delete
 */
void deleteFromTree(BST* T, int target);

/**
	Find the Minimum in the BST.
	@param T is the tree to search for the min
	@return The smallest number in the tree
 */
int min(BST* T);

/**
	Print the tree in inorder to stdout. End with newline
	@param T is the tree to print
 */
void inorder(BST* T);

/**
	Print the tree in preorder to stdout. End with newline
	@param T is the tree to print
 */
void preorder(BST* T);

/**
	Print the tree in postorder to stdout. End with newline
	@param T is the tree to print
 */
void postorder(BST* T);

/**
	Find the height of the tree.
	@param T is tree to check the height on
	@param The number of edges in longest path to root. -1 for null tree.
 */
int height(BST* T);

/*
    These methods act on Nodes.
    They can be implemented recursively.
    Most of the previous methods just call these on the root.
*/

/**
	Recursively print the tree inorder. End with a space.
	@param current is the node to print
 */
void inorderWalker(Node* current);

/**
	Recursively print the tree preorder. End with a space.
	@param current is the node to print
 */
void preorderWalker(Node* current);

/**
	Recursively print the tree postorder. End with a space
	@param current is the node to print
 */
void postorderWalker(Node* current);

/**
	Insert a value starting at a node recursively.
	@param target is the value to insert
	@param current is the node to start at
	@return Updated pointer to node after changes
 */
Node* insertValue(int target, Node* current);

/**
	Find a value in the tree starting at node recursively.
	@param target is the value to search for
	@param current is the node to start at
	@return True if found and False if not found
 */
bool findValue(int target, Node* current);

/**
	Find the minimum value starting at node recursively
	@param current is the node to start looking at
	@return The minimum of the section of the three starting at current
 */
int findMin(Node* current);

/**
	Find the height of a node. Null has height -1.
	@param current is the node to find the height of
	@return The height of the node in question
 */
int nodeHeight(Node* current);

/*
	Delete a value from the BST starting at node recursively.
	@param target is the value to delete
	@param current is the node to start at
	@return The updated node pointer
 */
Node* deleteValue(int target, Node* current);

/**
	Delete a specific node.
	@param current is the node to delete
	@return Updated pointer to replace node in the tree
 */
Node* deleteNode(Node* current);

BST* newBST() {
    BST* tree = malloc(sizeof(BST));
    tree->root = NULL;
    return tree;
}

Node* deleteNode(Node* node) {
	if (node == NULL) {
		return node;
	}

	node->left = deleteNode(node->left);
	node->right = deleteNode(node->right);

	free(node);
	return node;
}

void deleteBST(BST *T) {
	if (T->root == NULL) {
		return;
	}

	T->root = deleteNode(T->root);
}

Node* insertValue(int target, Node* current) {
    if (current == NULL) {
        Node* node = malloc(sizeof(Node));
        node->left = NULL;
        node->right = NULL;
        node->value = target;
        return node;
    }

    if (current->value == target) {
        return current;
    }

    if (target < current->value) {
        current->left = insertValue(target, current->left);
        return current;
    } else {
        current->right = insertValue(target, current->right);
        return current;
    }
}

void insert(BST* T, int target) {
    T->root = insertValue(target, T->root);
}

Node* deleteValue(int target, Node* node) {
	if (node == NULL) {
		return NULL;
	}

	if (node->value > target) {
		node->left = deleteValue(target, node->left);
		return node;
	} else if (node->value < target) {
		node->right = deleteValue(target, node->right);
		return node;
	}

	if (node->left == NULL) {
		Node* temp = node->right;
		free(node);
		return temp;
	} else if (node->right == NULL) {
		Node* temp = node->left;
		free(node);
		return temp;
	} else {
		Node* succParent = node;
		Node* succ = node->right;
		while (succ->left != NULL) {
			succParent = succ;
			succ = succ->left;
		}

		if (succParent != node) {
			succParent->left = succ->right;
		} else {
			succParent->right = succ->right;
		}

		node->value = succ->value;

		free(succ);
		return node;
	}
}

void deleteFromTree(BST* T, int target) {
	if (T->root == NULL) {
		return;
	}
	T->root = deleteValue(target, T->root);
}

bool findValue(int target, Node* current) {
	if (current == NULL) {
		return false;
	}

	if (current->value == target) {
		return true;
	}

	if (target < current->value) {
		return findValue(target, current->left);
	} else {
		return findValue(target, current->right);
	}
}

bool find(BST* T, int target) {
	return findValue(target, T->root);
}

int findMin(Node* node) {
	if (node->left == NULL) {
		return node->value;
	} else {
		return findMin(node->left);
	}
}

int min (BST* T) {
	return findMin(T->root);
}

void inorderWalker(Node* node) {
	if (node == NULL) {
		return;
	}

	inorderWalker(node->left);

	printf("%d ", node->value);

	inorderWalker(node->right);
}

void inorder(BST* T) {
	if (T->root == NULL) {
		printf("\n");
		return;
	}

	inorderWalker(T->root);
	printf("\n");
}

void preorderWalker(Node* node) {
	if (node == NULL) {
		return;
	}

	printf("%d ", node->value);

	preorderWalker(node->left);

	preorderWalker(node->right);
}

void preorder(BST* T) {
	if (T->root == NULL) {
		printf("\n");
		return;
	}

	preorderWalker(T->root);
	printf("\n");
}

void postorderWalker(Node* node) {
	if (node == NULL) {
		return;
	}

	postorderWalker(node->left);

	postorderWalker(node->right);

	printf("%d ", node->value);
}

void postorder(BST* T) {
	if (T->root == NULL) {
		printf("\n");
		return;
	}

	postorderWalker(T->root);
	printf("\n");
}

int nodeHeight(Node* node) {
	if (node == NULL) {
		return 0;
	} else {
		int leftDepth = nodeHeight(node->left);
		int rightDepth = nodeHeight(node->right);

		if(leftDepth > rightDepth) {
			return (leftDepth + 1);
		} else {
			return (rightDepth + 1);
		}
	}
}

int height(BST *T) {
	if (T->root == NULL) {
		return -1;
	} else {
		return (nodeHeight(T->root)-1);
	}
}
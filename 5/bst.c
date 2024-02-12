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

insertHelper(Node* current, int val) {
    if (current == NULL) {
        Node* node = malloc(sizeof(Node));
        node->left = NULL;
        node->right = NULL;
        node->value = val;
        return node;
    }

    if (current->value == val) {
        return current;
    }

    if (val < current->value) {
        current->left = insertHelper(current->left, val);
        return current;
    } else {
        current->right = insertHelper(current->right, val);
        return current;
    }
}

void insert(BST* T, int target) {
    T->root = insertHelper(T->root, target);
}

Node* deleteHelper(Node* node, int target) {
	if (node == NULL) {
		return;
	}

	if (node->value > target) {
		node->left = deleteHelper(node->left, target);
		return node;
	} else if (node->value < target) {
		node->right = deleteHelper(node->right, target);
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
	T->root = deleteHelper(T->root, target);
}

bool searchHelper(Node* current, int target) {
	if (current == NULL) {
		return false;
	}

	if (current->value == target) {
		return true;
	}

	if (target < current->value) {
		return searchHelper(current->left, target);
	} else {
		return searchHelper(current->right, target);
	}
}

bool find(BST* T, int target) {
	return searchHelper(T->root, target);
}

int minHelper(Node* node) {
	if (node->left == NULL) {
		return node->value;
	} else {
		return minHelper(node->left);
	}
}

int min (BST* T) {
	return minHelper(T->root);
}

void inorderHelper(Node* node) {
	if (node == NULL) {
		return;
	}

	inorderHelper(node->left);

	printf("%d ", node->value);

	inorderHelper(node->right);
}

void inorder(BST* T) {
	if (T->root == NULL) {
		return;
	}

	inorderHelper(T->root);
	printf("\n");
}

void preorderHelper(Node* node) {
	if (node == NULL) {
		return;
	}

	printf("%d ", node->value);

	preorderHelper(node->left);

	preorderHelper(node->right);
}

void preorder(BST* T) {
	if (T->root == NULL) {
		return;
	}

	preorderHelper(T->root);
	printf("\n");
}

void postorderHelper(Node* node) {
	if (node == NULL) {
		return;
	}

	postorderHelper(node->left);

	postorderHelper(node->right);

	printf("%d ", node->value);
}

void postorder(BST* T) {
	if (T->root == NULL) {
		return;
	}

	postorderHelper(T->root);
	printf("\n");
}
/**
	@file
	@author Mark Boady <mwb33@drexel.edu>
	@date 2022
	@section DESCRIPTION
 
	This is a header file for a Binary Search Tree Class.
	Students will implement a related bst.c file to finish this assignment.
 */

/* You MAY NOT change this file */

#ifndef _BST_H_
#define _BST_H_

#include <stdbool.h>

/* Type Definitions for the file */
typedef struct Node Node;
typedef struct BST BST;

/**
	A structure to represent a single node in a binary search tree.
 */
struct Node{
	int value; /**< The value at this point in the tree.*/
	Node* left; /**< The left child of this node.*/
	Node* right; /**< The right child of this node.*/
};

/**
	A structure to represent a binary search tree.
 */
struct BST{
	Node* root; /**< The root node of the binary tree.*/
};

/* Front End Methods */
/* These method act on the TREE starting at the root */

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

#endif

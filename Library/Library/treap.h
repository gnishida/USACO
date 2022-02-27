#pragma once

#include <iostream>

// A Treap Node
struct TreapNode
{
	int key, priority;
	TreapNode *left, *right;
};

TreapNode *TreapRightRotate(TreapNode *y)
{
	TreapNode *x = y->left, *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TreapNode* TreapLeftRotate(TreapNode *x)
{
	TreapNode *y = x->right, *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Return new root
	return y;
}

/* Add a new key */
TreapNode* TreapNewNode(int key)
{
	TreapNode* temp = new TreapNode;
	temp->key = key;
	temp->priority = rand() % 100;
	temp->left = temp->right = nullptr;
	return temp;
}

// Search a given key in a given BST
TreapNode* TreapSearch(TreapNode* root, int key)
{
	// Base Cases: root is null or key is present at root
	if (root == nullptr || root->key == key)
		return root;

	// Key is greater than root's key
	if (root->key < key)
		return TreapSearch(root->right, key);

	// Key is smaller than root's key
	return TreapSearch(root->left, key);
}

/* Recursive implementation of insertion in Treap */
TreapNode* TreapInsert(TreapNode* root, int key)
{
	// If root is NULL, create a new node and return it
	if (!root)
		return TreapNewNode(key);

	// If key is smaller than root
	if (key <= root->key) {
		// Insert in left subtree
		root->left = TreapInsert(root->left, key);

		// Fix Heap property if it is violated
		if (root->left->priority > root->priority)
			root = TreapRightRotate(root);
	} else {
		// Insert in right subtree
		root->right = TreapInsert(root->right, key);

		// Fix Heap property if it is violated
		if (root->right->priority > root->priority)
			root = TreapLeftRotate(root);
	}
	return root;
}

/* Recursive implementation of Delete() */
TreapNode* TreapDeleteNode(TreapNode* root, int key)
{
	if (root == nullptr)
		return root;

	if (key < root->key) {
		root->left = TreapDeleteNode(root->left, key);
	} else if (key > root->key) {
		root->right = TreapDeleteNode(root->right, key);
	} else if (root->left == nullptr) {
		TreapNode *temp = root->right;
		delete(root);
		root = temp;  // Make right child as root
	} else if (root->right == nullptr) {
		TreapNode *temp = root->left;
		delete(root);
		root = temp;  // Make left child as root
	} else if (root->left->priority < root->right->priority) {
		root = TreapLeftRotate(root);
		root->left = TreapDeleteNode(root->left, key);
	} else {
		root = TreapRightRotate(root);
		root->right = TreapDeleteNode(root->right, key);
	}

	return root;
}

// A utility function to print tree
void TreapPrint(TreapNode* root) {
	if (root) {
		TreapPrint(root->left);

		std::cout << "key: " << root->key << " | priority: " << root->priority;
		if (root->left) {
			std::cout << " | left child: " << root->left->key;
		}
		if (root->right) {
			std::cout << " | right child: " << root->right->key;
		}
		std::cout << std::endl;

		TreapPrint(root->right);
	}
}

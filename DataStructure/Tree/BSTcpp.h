/************************************************************************

	http://www.sourcetricks.com/2011/06/binary-search-trees-in-c.html#.WCsqgOJ96Uk

	What is binary search trees?
	How to implement in C++?

	This article explains the concept of binary search trees (BST) 
	-	and provides a sample implementation in C++.

	Binary Search Tree (BST) is a binary tree (has at most 2 children).
	-	It is also referred as sorted/ ordered binary tree.

	BST has the following properties. (notes from wikipedia)
		The left subtree of a node contains only nodes with keys less than the node's key.
		The right subtree of a node contains only nodes with keys greater than the node's key.
		Both the left and right subtrees must also be binary search trees.

	BST Operations:-
		Searching in a BST
			Examine the root node. If tree is NULL value doesn't exist.
			If value equals the key in root search is successful and return.
			If value is less than root, search the left sub-tree.
			If value is greater than root, search the right sub-tree.
			Continue until the value is found or the sub tree is NULL.
			Time complexity. Average: O(log n), Worst: O(n) if the BST is unbalanced and resembles a linked list.


		Insertion in BST
			Insertion begin as a search.
			Compare the key with root. If not equal search the left or right subtree
			When a leaf node is reached add the new node to left or right based on the value.
			Time complexity. Average: O(log n), Worst O(n)

		Deletion in BST

			There are three possible cases to consider:
				Deleting a leaf (node with no children): Deleting a leaf is easy, as we can simply remove it from the tree.
				Deleting a node with one child: Remove the node and replace it with its child.
				Deleting a node with two children: Call the node to be deleted N. Do not delete N. Instead, choose either its in-order successor node or its in-order predecessor node, R. Replace the value of N with the value of R, then delete R.

/************************************************************************/
///  >> 11/16/0/2016 BY.gaohuancai QQ1293302539 <<
#pragma once

#include <iostream>
using namespace std;

// A generic tree node class
class BSTNode
{
private:
	int key;
	BSTNode * left;
	BSTNode * right;
	BSTNode * parent;

public:
	BSTNode()
	{
		key = -1;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	void	setKey(int aKey)			{ key = aKey; }
	void	setLeft(BSTNode * aLeft)	{ left = aLeft; }
	void	setRight(BSTNode * aRight)	{ right = aRight; }
	void	setParent(BSTNode * aParent){ parent = aParent; }

	int			Key()	{ return key; }

	BSTNode *	Left()	{ return left; }
	BSTNode *	Right()	{ return right; }
	BSTNode *	Parent(){ return parent; }

};

class BSTTree
{
public:
	BSTTree();
	~BSTTree();

	void	addNode(int key);
	void	walk(BSTNode * node);
	void	deleteNode(int key);

	BSTNode *	Root()	{ return root; }

	BSTNode *	findNode(int key, BSTNode * parent);
	BSTNode *	min(BSTNode * node);
	BSTNode *	max(BSTNode * node);
	BSTNode *	successor(int key, BSTNode * parent);
	BSTNode *	predecessor(int key, BSTNode * parent);

	static int main_BSTTree();
private:
	void	addNode(int key, BSTNode * leaf);
	void	freeNode(BSTNode * leaf);

private:
	BSTNode * root;
};
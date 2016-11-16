/************************************************************************

/************************************************************************/
#include "BinaryTree.h"

namespace nsBinaryTree
{

	struct LOTBTNode
	{
		int data;
		struct LOTBTNode  *left;
		struct LOTBTNode  *right;
	};


	//function prototypes;
	void printGivenLevel(struct LOTBTNode* root, int level);
	int height(struct LOTBTNode* node);
	struct LOTBTNode* newLOTBTNode(int data);
	void printLevelOrder(struct LOTBTNode* root);
	bool lookup(struct LOTBTNode* node, int target);

	void printLevelOrder(struct LOTBTNode* root)
	{

		int hlevel = height(root);

		for (int i = 0; i <= hlevel; ++i)
		{
			printGivenLevel(root, i);
		}
	}

	//print nodes at a given level;
	void printGivenLevel(struct LOTBTNode* root, int level)
	{
		if (NULL == root)
			return;
		if (1 == level)
			fprintf(stderr, "%d\n", root->data);
		else
			if (1 < level) {
				printGivenLevel(root->left, level - 1);
				printGivenLevel(root->right, level - 1);
			}
	}

	//compute the "height" of a tree
	//the number of nodes along the longest path 
	//from the root node down to the farthest leaf node;
	int height(struct LOTBTNode* node)
	{
		if (NULL == node) {
			//it is a empty tree;
			return 0;
		}
		else{
			//compute the height of each subtree first;
			int lheight = height(node->left);
			int rheight = height(node->right);

			//return the larger one;
			return (((lheight > rheight) ? lheight : rheight) + 1);
		}
	}

	//allocates a new node with the given data and NULL left and right pointers;
	struct LOTBTNode* newLOTBTNode(int data)
	{
		struct LOTBTNode *node =
			(struct LOTBTNode*)malloc(sizeof(struct LOTBTNode));

		node->data = data;
		node->left = nullptr;
		node->right = nullptr;

		return node;
	}

	/************************************************************************
	  given a binary tree return true
		if a node with the target data is found in the tree.
		Recurs down the tree,
		chooses the left or right branch
		by comparing the target to each node
	************************************************************************/
	bool lookup(struct LOTBTNode* node, int target)
	{
		//[0.]  Base case == empty tree;
		//in that case, the target is not found so return false;
		if (nullptr == node)
			return (false);

		else {
			//[1.]  see if found here
			if (target < node->data)
				return (node->left, target);
			else
				return (lookup(node->right, target));

		}
	}


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/


	int main_BinaryTree()
	{
		struct LOTBTNode *root = newLOTBTNode(1);
		root->left = newLOTBTNode(2);
		root->right = newLOTBTNode(3);
		root->left->left = newLOTBTNode(4);
		root->left->right = newLOTBTNode(5);

		printLevelOrder(root);

		return 0;

	}
}


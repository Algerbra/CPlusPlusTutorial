/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "BinaryTree.h"
#include <iostream>
#include <string>

namespace nsBSTree
{

	struct TreeNode
	{
		std::string item;
		TreeNode * left;
		TreeNode * right;

		TreeNode(std::string str = "")
		{
			//constructor, defined for convenience;make a node containing a string;
			item = str;
			left = nullptr;
			right = nullptr;
		}
	};//end struct TreeNode;


	/************************************************************************
	    add an item to the BST to which the parameter "root" refers.
		note that root is passed by reference since its value can change
		in the case where the tree is empty..
	
	/************************************************************************/
	void treeInsert(struct TreeNode*& root, std::string newItem)
	{

		if (nullptr == root) {
			root = new TreeNode(newItem);
			return;
		}

		else if (newItem < root->item) {
			treeInsert(root->left, newItem);
		}

		else {
			treeInsert(root->right, newItem);
		}

	}// end treeInsert;


	/************************************************************************
		Return true if item is one of the items in the BST to which
		root points.  Return false if not.
	/************************************************************************/
	bool treeContains(struct TreeNode* root, std::string item)
	{
		if (nullptr == root) {
			return false;
		}

		else if (item == root->item) {
			return true;
		}

		else if (item < root->item) {
			return treeContains(root->left, item);
		}

		else if (item > root->item) {
			return treeContains(root->right, item);
		}

	}// end treeConains;

	/************************************************************************
		print the items in the tree in postorder, one item to a line.
		since the tree is a sort tree, the output will be in 
		increasing order..
	/************************************************************************/
	void treeList(struct TreeNode* node)
	{
		if (nullptr != node) {
			treeList(node->left);
			fprintf(stderr, " %s\n", node->item.c_str());
			treeList(node->right);
		}

	}// end treeList;


	/************************************************************************
		count the nodes in the binary tree to which node points.
		return the answer...
	/************************************************************************/
	int countNodes(struct TreeNode* node)
	{
		if (nullptr == node) {
			return 0;
		}

		else {
			int leftCount = countNodes(node->left);
			int rightCount = countNodes(node->right);

			return (leftCount + rightCount + 1);
		}

	}// end countNodes;


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/


	int main_BSTree()
	{
		struct TreeNode * root = nullptr;
		std::string title = "This programs stores strings that you enter in a binary sort\n";
		title += "tree.  After each items is inserted, the contents of the tree\n";
		title += "are displayed.  The number of nodes in the tree is also output.\n";
		title += "    Any string you enter will be converted to lower case.\n";
		title += "Duplicate entries are ignored.\n";
		fprintf(stderr, "%s\n", title.c_str());


		/************************************************************************
		get one string from the user, insert it into the tree,
		and print some information about the tree. Exit if the
		user enters an empty string. Note that all strings are
		converted to lower case.
		/************************************************************************/
		while (true)
		{
			fprintf(stderr, "\n\nEnter a string to be inserted, or press return to end.\n");
			fprintf(stderr, "?  \n");
			std::string item;// storing input from the users;

			if (std::cin.peek() == '\n')
				break;

			std::cin >> item;
			std::cin.ignore(10000, '\n');
			if (treeContains(root, item)) {
				// don't insert a second copy of an item that is already in the tree.
				fprintf(stderr, "\n That item is already in the tree.\n");
			}

			else {
				treeInsert(root, item);	// add user's string to the tree...
				std::cout << "\nThe tree contains " << countNodes(root) << " items.\n";
				std::cout << "\nContents of tree:\n\n";
				treeList(root);
			}
		}// end while (true)

		std::cout << "\n\nExisting program..\n\n";

		return 0;

	}//end main_BSTree();
}

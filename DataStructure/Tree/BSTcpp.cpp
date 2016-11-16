/************************************************************************
 *
 *
 *
 * http://algorithms.tutorialhorizon.com/inorder-predecessor-and-successor-in-binary-search-tree/
 *
 *
 ** Predecessor and Successor                            
 **                                                      
 **   When you do the inorder traversal of a binary tree,
 **   the neighbors of given node are called Predecessor
 **       (the node lies behind of given node)
 **   and Successor (the node lies ahead of given node).
 **                                                
 **                 25                             
 **               /    \                           
 **              /      \                          
 **             /        \                         
 **           15          40                       
 **         /   \        /   \                     
 **       10     18    35     45                   
 **      /      /  \         /  \                  
 **     5      19    20     44    49               
 **                                                
 **      Node-25                                   
 **      Predecessor of Node-25 will be the right  
 **      most element in the left-Subtree, which   
 **      is Node-20                                
 **                                                
 **      Successor of Node-25 will be the left most
 **      element in the right-Subtree, which is    
 **      Node-35                                   
 **                                                
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<

#include "BSTcpp.h"

BSTTree::BSTTree()
	{root = nullptr;}

BSTTree::~BSTTree()
	{freeNode(root);}

// free the node;
void BSTTree::freeNode(BSTNode * leaf)
{
	if (nullptr != leaf)
	{
		freeNode(leaf->Left());
		freeNode(leaf->Right());
		delete leaf;
		leaf = nullptr;
	}
}

// add a node [0(height of tree) on average]
void BSTTree::addNode(int key)
{
	//no elements. add the root..
	if (nullptr == root) {
		cout << "add root node ... "<<key <<"\n";
		BSTNode * n = new BSTNode();
		n->setKey(key);

		root = n;
	}

	else {
		cout << "add other node ... " << key <<"\n";
		addNode(key, root);
	}
}


// add a node (private)
void BSTTree::addNode(int key, BSTNode * leaf)
{
	if (key <= leaf->Key()) {

		if (nullptr != leaf->Left())
			addNode(key, leaf->Left());

		else {

			BSTNode * n = new BSTNode();
			n->setKey(key);
			n->setParent(leaf);
			leaf->setLeft(n);
		}
	}

	else {

		if (nullptr != leaf->Right())
			addNode(key, leaf->Right());

		else {
			BSTNode * n = new BSTNode();
			n->setKey(key);
			n->setParent(leaf);
			leaf->setRight(n);
		}
	}

}// end addNode(int , BSTTree*);

// find a node [0(height of tree) on average]
BSTNode * BSTTree::findNode(int key, BSTNode * node)
{
	if (nullptr == node)
		return node;

	else if (key == node->Key())
		return node;

	else if (key < node->Key())
		return findNode(key, node->Left());

	else if (key > node->Key())
		return findNode(key, node->Right());

	else
		return nullptr;
}

// print the tree  // preOrder
void BSTTree::walk(BSTNode * node)
{
	if (nullptr != node) {

		cout << node->Key() << " ";	//--preOrder

		walk(node->Left());			//--inOrder
		walk(node->Right());		//--postOrder
	}
}

// find the node with minimum key
//[0] traverse the left-Subtree recursively
//[1] till left-Subtree is empty to get min
BSTNode * BSTTree::min(BSTNode * node)
{
	if (nullptr == node)
		return node;

	if (node->Left())
		return min(node->Left());

	else
		return node;
}

// find the node with maximum key
//[0] traverse the right-Subtree recursively
//[1] till right-Subtree is empty to get max
BSTNode * BSTTree::max(BSTNode * node)
{
	if (nullptr == node)
		return node;

	if (node->Right())
		return max(node->Right());

	else
		return node;
}


/// 
/************************************************************************
	Successor:
		A node's successor is the one with the next largest value/key
		-	in the tree. 
		
		In other words, if all keys are distinct, the successor of a
		-	nodeX is the node with the smallest key greater than nodeX

		The structure of BST allows to determine the successor of a node
		-	without-ever-comparing-the-keys

		IF the node has a Right-Child
		-	then it is the minimum of the minor tree.

		IF the node has a Left-Child
		-	then we need to search back up the tree
		-	until we find the first Right-Hand turn.


	Predecessor:
		IF a node has a Left-Child
		-	then we take subtree's maximum
		-	the right-most-child of its left subtree.

		IF a node has no Left-Child
		-	we walk up the tree until we find a Left-Hand turn
		-	follow the parent pointer until we get the key 
		-	which is smaller than its own value.
/************************************************************************/
// find successor to a node
//[0] find the node, get the node with max-value
//[1] for the right-Subtree to get the successor
BSTNode * BSTTree::successor(int key, BSTNode * node)
{
	BSTNode* thisKey = findNode(key, node);
	if (thisKey)
		return max(thisKey->Right());
}

// find predecessor to a node
//[0] find the node, get the node with max value
//[1] for the left-Subtree to get predecessor
BSTNode * BSTTree::predecessor(int key, BSTNode * node)
{
	BSTNode * thisKey = findNode(key, node);

	if (thisKey)
		return max(thisKey->Left());
}


// delete a node
//[0] if a leaf, then just delete
//[1] if only one child , then delete this node and replace it with the child
//[2] if 2-children, then find the predecessor (or successor) 
//[2] - Delete the predecessor (or successor). Replace the node to be with
//[2] - the predecessor (or successor)
void BSTTree::deleteNode(int key)
{
	//
	BSTNode * thisKey = findNode(key, root);

	//(1)
	if (nullptr == thisKey->Left() && nullptr == thisKey->Right())
	{
		if (thisKey->Key() > thisKey->Parent()->Key())
			thisKey->Parent()->setRight(nullptr);

		else
			thisKey->Parent()->setLeft(nullptr);

		delete thisKey;
		thisKey = nullptr;
	}

	//(1)
	if (nullptr != thisKey->Left() && nullptr == thisKey->Right())
	{
		//thisKey->Left()->setParent(thisKey->Parent());// ?
		//How to the thisKey->Left is a left-Subtree or a right-Subtree ?
		//if thisKey->Parent()->key() < thisKey->key(), then right-Subtree..
		if (thisKey->Parent()->Key() < thisKey->Key())
			thisKey->Parent()->setRight(thisKey->Left());

		else
			thisKey->Parent()->setLeft(thisKey->Left());

		delete thisKey;
		thisKey = nullptr;
	}

	if (nullptr == thisKey->Left() && nullptr != thisKey->Right())
	{
		if (thisKey->Parent()->Key() < thisKey->Key())
			thisKey->Parent()->setRight(thisKey->Right());

		else
			thisKey->Parent()->setLeft(thisKey->Right());

		delete thisKey;
		thisKey = nullptr;
	}


	//(2)
	if (thisKey->Left() && thisKey->Right())
	{
		//(0th) index the Predecessor of thisKey
		BSTNode * sub = predecessor(thisKey->Key(), thisKey);

		//(1st) is the Predecessor pointing to nullptr ?
		if (nullptr == sub)
			sub = successor(thisKey->Key(), thisKey);

		//(2nd) 
		if (sub->Parent()->Key() <= sub->Key())
			sub->Parent()->setRight(sub->Right());

		else
			sub->Parent()->setLeft(sub->Left());

		//(3th) 
		thisKey->setKey(sub->Key());
		delete sub;
		sub = nullptr;
	}

}

//
int BSTTree::main_BSTTree()
{
	BSTTree * tree = new BSTTree;
	//
	tree->addNode(300);
	tree->addNode(100);
	tree->addNode(200);
	tree->addNode(400);
	tree->addNode(500);

	//Traverse the tree
	cout << "Traverse:\n\t";
	tree->walk(tree->Root());
	cout << "\n\n";

	//Find nodes
	cout << "FindNode: \n";
	for (int i = 5; i < 7;++i)
	{
		if (tree->findNode(i * 100, tree->Root()))
			cout << "\tBSTNode.Key() " << i * 100<<" found...\n";
		else
			cout << "\tBSTNode.Key() " << i * 100 << " not found...\n";
	}
	cout << "\n\n";

	//Minimum && Maximum
	cout << "Min= \n\t" << tree->min(tree->Root())->Key() << "\n";
	cout << "Max= \n\t" << tree->max(tree->Root())->Key() << "\n";
	cout << "\n";

	//Successor && Predecessor
	cout << "Successor to 300 = "
	     << tree->successor(300, tree->Root())->Key() << "\n";
	cout << "Predecessor to 300 = "
		 << tree->predecessor(300, tree->Root())->Key() << "\n";
	cout << "\n";

	//Delete a node
	tree->deleteNode(300);
	//cout << "\n\n";

	// Traverse the tree
	tree->walk(tree->Root());
	cout << "\n";

	delete tree;


	


	return 0;
}
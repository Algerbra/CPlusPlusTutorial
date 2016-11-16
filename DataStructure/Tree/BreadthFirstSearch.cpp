/************************************************************************

  http://www.sanfoundry.com/c-program-to-display-tree-nodes-using-bfs-traversal/
  http://www.blogjava.net/fancydeepin/archive/2013/02/03/395073.html

/************************************************************************/
#include "BreadthFirstSearch.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stack>
#include <queue>

namespace nsBreadthFirstSearch
{
	struct TreeNode
	{
		int value;
		struct TreeNode * left;
		struct TreeNode * right;

		TreeNode()
		{
			value = INT_MIN;
			left = nullptr;
			right = nullptr;
		}
	};

	//show stack element data;
	void stack_show(std::stack<TreeNode*> s)
	{
		while (!s.empty())
		{
			fprintf(stderr, "\t\t <[stack] %d -> >\n", s.top()->value);
			s.pop();
		}
	}

	//show queue element data;
	void queue_show(std::queue<TreeNode*> q)
	{
		while (!q.empty())
		{
			fprintf(stderr, "\t\t <[queue] %d >\n", q.front()->value);
			q.pop();
		}
	}


	//Inserting nodes into a tree
	//Used to construct the Binary-Sorted-Tree
	void insert(TreeNode * newNode, TreeNode * root)
	{
		// Right-Subtree
		if (newNode->value > root->value)
		{
			if (nullptr == root->right)
				root->right = newNode;

			else
				insert(newNode, root->right);
		}

		// Left-Subtree
		if (newNode->value < root->value)
		{
			if (nullptr == root->left)
				root->left = newNode;

			else
				insert(newNode, root->left);
		}
	}


	//Deep First Traverse
	//preOrder: ROOT->Left-Subtree->Right-Subtree
	void depth_first_search(TreeNode * root)
	{
		std::stack<TreeNode * > nodeStack;
		nodeStack.push(root);

		static int counter = 0;
		fprintf(stderr, " :[beg] depth -First -Traverse...\n");
		TreeNode * pnode = nullptr;
		while (!nodeStack.empty())
		{
			if (false)
			{
				stack_show(nodeStack);
			}
			pnode = nodeStack.top();
			if (pnode)
				fprintf(stderr, "%d -> ", pnode->value);//ROOT
			nodeStack.pop();

			if (pnode->right)
				nodeStack.push(pnode->right);

			if (pnode->left)
				nodeStack.push(pnode->left);
		}
		fprintf(stderr, "\n :[end] depth -First -Traverse...\n");

	}// end depthFirstSearch();


	/************************************************************************
		std::queue
			THIS class is a container adapter that gives the programmer the
			functionality of a queue - specifically, a FIFO data structure..

			... The queue pushes the elements on the back of the underlying
			container and pops them from the front..


		std::queue::front
			Returns reference to the first element in the queue.
			This element will be the first element to be removed on a call to pop().
			Effectively calls c.front()
			//but never destroy THIS-exact-element-??
			//yes,only return a reference of c.front()..

		std::queue::pop
			Removes an element from the front of the queue.
			Effectively calls c.pop_front()
			//destroy the element popped..

		[References]
			Wyh doesn't std::queue::pop return value. ?
			http://stackoverflow.com/questions/25035691/why-doesnt-stdqueuepop-return-value

			"It could indeed have done the same thing. The reason it didn't, 
			-	is because a pop that returned the popped element is unsafe 
			-	in the presence of exceptions (having to return by value and
			-	thus creating a copy)."
	/************************************************************************/
	//Breadth First Traverse
	void breadth_first_search(TreeNode * root)
	{
		static int counter = 0;
		std::queue<TreeNode * > nodeQueue;
		nodeQueue.push(root);

		fprintf(stderr, " :[beg] Bread -First -Traverse...\n");
		TreeNode * pnode = nullptr;
		while (!nodeQueue.empty())
		{
			if (false) {
				//TODO:Test Code;
				queue_show(nodeQueue);
				fprintf(stderr, "\t\t\t\t\t[loop]  %d\n", ++counter);
			}

			pnode = nodeQueue.front();
			//for now, pnode and nodeQueue[0] both point to the same memory location ROOT 'root';

			nodeQueue.pop();
			//for now, only pnode have a reference to the ROOT 'root';

			fprintf(stderr, "%d -> ", pnode->value);

			if (pnode->left)
				nodeQueue.push(pnode->left);

			if (pnode->right)
				nodeQueue.push(pnode->right);
		}
		fprintf(stderr, "\n :[end] Bread -First -Traverse...\n");

	}// end breadthFirstSearch();


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	int main_BreadthFirstSearch()
	{
		TreeNode * root = nullptr;
		TreeNode * newNode = nullptr;
		int num = 1;
		fprintf(stderr, "Enter the elements of the tree (enter 0 to exit) \n");

		while (true)
		{
			scanf("%d", &num);
			if (0 == num)break;

			newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
			newNode->left = newNode->right = nullptr;
			newNode->value = num;

			if (nullptr == root)
				root = newNode;

			else
				insert(newNode, root);
		}

		fprintf(stderr, ": Elements in a tree in-Order are \n");

		///breadth_first_search(root);
		depth_first_search(root);

		return 0;
	}

}



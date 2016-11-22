/******************************************************************************************
 *
  References
		https://en.wikibooks.org/wiki/Data_Structures/Stacks_and_Queues
		https://www.cs.cmu.edu/~adamchik/15-121/lectures/Stacks%20and%20Queues/Stacks%20and%20Queues.html

  # # # # # # # # # # # # # # # # # # # # ### # # # # # # # # # # # # # # # # # # # #
  Stacks
	Reference
		https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
  Conception
	A stack is a basic data structure that can be logically thought as
	-	linear structure represented by a real physical stack or pile,
	-	a structure where insertion and deletion of items takes place at
	-	one end called top of the stack.

  Operation
	The basic implementation of a stack is also called a LIFO 
	-	(Last In First Out) to demonstrate the way it accesses data, since
	-	as we will see there are various variations of stack implementations.

	There are basically three operations that can be performed on stacks .
	-	They are 
	-	1) inserting an item into a stack (push). 
	-	2) deleting an item from the stack (pop). 
	-	3) displaying the contents of the stack(pip).


	push(new-item:item-type)
		Adds an item onto the stack.
	top():item-type
		Returns the last item pushed onto the stack.
	pop()
		Removes the most-recently-pushed item from the stack.
	is-empty():Boolean
		True if no more items can be popped and there is no top item.
	is-full():Boolean
		True if no more items can be pushed.
	get-size():Integer
		Returns the number of elements on the stack.

  [reference]
	http://www.cprogramming.com/tutorial/computersciencetheory/stack.html
  Terminology associated with Stack
	
	Push	//To add an element to the stack
	Pop		//To remove an element from the stock
	Peek	//To look at elements in the stack without removing them
	LIFO	//Refers to the last in, first out behavior of the stack
	FILO	//Equivalent to LIFO


  # # # # # # # # # # # # # # # # # # # # ### # # # # # # # # # # # # # # # # # # # #

  Queues
	Reference
		https://en.wikipedia.org/wiki/Queue_(abstract_data_type)

  Conception
	A queue is also called a FIFO (First In First Out) to demonstrate the way
	-	it accesses data.


  Operation
	enqueue(new-item:item-type)
		Adds an item onto the end of the queue.
	front():item-type
		Returns the item at the front of the queue.
	dequeue()
		Removes the item from the front of the queue.
	is-empty():Boolean
		True if no more items can be dequeued and there is no front item.
	is-full():Boolean
		True if no more items can be enqueued.
	get-size():Integer
		Returns the number of elements in the queue.


	# # # # # # # # # # # # # # # # # # # # ### # # # # # # # # # # # # # # # # # # # #
	Reference
	http://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/
	
	Reference
	http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/

/******************************************************************************************/
///  >> 11/21/0/2016 BY.gaohuancai QQ1293302539 <<
#include "DGraphSearch.h"
#include <list>


namespace nsDGraphSearch
{
	using namespace std;

	//This is a directed graph represented with adjacency list.
	//
	// Note that the above code traverses only the vertices reachable 
	// from a given source vertex. All the vertices may not be reachable
	// from a given vertex (example Disconnected graph). 
	class DGraphAdjList
	{
	public:
		DGraphAdjList(int v)
			: _gVertCount(v)
			, _gAdjacencyList(new std::list<int>[_gVertCount])
		{}

		//function to add an edge to graph.
		//@brief add 'w' to v's list..
		void	addEdge(int v, int w)
		{
			_gAdjacencyList[v].push_back(w);
		}

		//DFS traversal of the vertices reachable from V..
		//It uses recursive DFSUtil()
		void	depth_first_search(int vertStart)
		{
			// mark all the vertices as visited
			bool * visited = new bool[_gVertCount];
			for (int i = 0; i < _gVertCount; ++i)
				visited[i] = false;

			// call the recursive helper function to print DFS traversal..
			DFSUtil(vertStart, visited);
		}

		///
		void	breadth_first_search(int vStart)
		{
			/// mark all the vertices as not visited..
			bool * visited = new bool[_gVertCount];
			for (int i = 0; i < _gVertCount; ++i)
				visited[i] = false;

			///create a queue for BFS
			std::list<int>  tQueue;

			/// mark the current node as visited and enqueue it..
			visited[vStart] = true;		///Mark first Enqueue second..
			tQueue.push_back(vStart);	///Mark first Enqueue second..

			/// iterates all Vertices of the Adjacency List of THE Vertex 'vStart'.
			std::list<int>::iterator  it;
			while (!tQueue.empty())
			{
				vStart = tQueue.front();		//Dequeue a Vertex from front..
				fprintf(stderr, "%d ", vStart);	//Print THE Vertex Info..
				tQueue.pop_front();				//Pop THE Vertex from temQueue..

				// every time after we popped out a vertex 'vStart', then 
				// we must following enqueue all adjacent vertices of the dequeued vertex 'vStart'.
				// : if a adjacent has not been visited, then mark it visited and enqueue it.
				for (it = _gAdjacencyList[vStart].begin(); it != _gAdjacencyList[vStart].end(); ++it)
				{
					if (!visited[*it])
					{
						visited[*it] = true;	///Mark first Enqueue second..
						tQueue.push_back(*it);	///Mark first Enqueue second..
					}
				}
			}
		}

	private:
		// function used by DFS..
		void	DFSUtil(int vStart, bool visited[])
		{
			//mark the current node as visited and print it..
			visited[vStart] = true;
			fprintf(stderr, "%d ", vStart);

			// Traverse Each Vertex-Stored-in-AdjacencyList..
			// recur for all vertex adjacent to this Starting-Vertex..
			std::list<int>::iterator it;
			for (it = _gAdjacencyList[vStart].begin(); it != _gAdjacencyList[vStart].end(); ++it)
			{
				if (!visited[*it])
					DFSUtil(*it, visited);
			}
		}

	private:

		int				  _gVertCount;		/// Vertex Counts;
		std::list<int>  * _gAdjacencyList;	///Pointer to an array containing adjacency lists.

	};




	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	int main_DGraphTraversal()
	{
		// Create a graph given in the above diagram
		DGraphAdjList udg(4);
		udg.addEdge(0, 1);
		udg.addEdge(0, 2);
		udg.addEdge(1, 2);
		udg.addEdge(2, 0);
		udg.addEdge(2, 3);
		udg.addEdge(3, 3);

		std::string info = "\n\tFollowing is Directed-Graph-Traversal (starting from vertex 2) \n";
		info += "\tEnter 0 for DFS; 1 for BFS; 2 for exiting Program\n\t";
		int ioption = INT_MIN;
		while (true)
		{
			fprintf(stderr, info.c_str());
			scanf("%d", &ioption);
			if (0 == ioption)
			{
				udg.depth_first_search(2);
			}
			else if (1 == ioption)
			{
				udg.breadth_first_search(2);
			}
			else if (2 == ioption)
			{
				break;
			}
			else
				fprintf(stderr, "\n\n\tReenter your option: ");

		}


		return 0;

	}
}

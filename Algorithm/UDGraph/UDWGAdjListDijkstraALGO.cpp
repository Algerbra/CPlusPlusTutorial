/************************************************************************
  Reference
	//Dijkstra algorithm implementation with Adjacent List Graph
	http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/

	//Dijkstra algorithm implementation with Adjacent Matrix Graph
	http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/

/************************************************************************/
///  >> 11/24/2/2016 BY.gaohuancai QQ1293302539 <<

#include "UDWGAdjListDijkstraALGO.h"

#include <stdio.h>
#include <stdlib.h>


namespace nsUDWGAdjListDijkstraALGO
{
	// Represent a Node in Adjacency List;
	struct AdjListNode
	{
		int  _nDest;
		int  _nWeight;
		struct AdjListNode* _nPnext;
	};

	// Represent an Adjacency List;
	struct AdjList
	{
		// Pointer to Head Node of AdjList;
		struct  AdjListNode  * _listHead;
	};


	// Represent a Graph.
	// A Graph is an_Array of AdjacencyLists.
	// sizeof(an_Array) will be V (number of vertices in graph)..
	struct UDGraphDijkstra
	{
		int   _gVnum;
		struct AdjList * _gAdjListArray;
	};

	// Utility function to create a new adjacency list node.
	struct AdjListNode * newAdjListNode(int dest, int weight)
	{
		struct AdjListNode * newNode =
			(struct AdjListNode*)malloc(sizeof(struct AdjListNode));

		newNode->_nDest = dest;
		newNode->_nWeight = weight;
		newNode->_nPnext = nullptr;

		return newNode;
	}

	// Utility function to create a Graph of Vnum vertices;
	struct UDGraphDijkstra * createGraph(int V)
	{
		struct UDGraphDijkstra * graph = (struct UDGraphDijkstra *)malloc(sizeof(struct UDGraphDijkstra));
		graph->_gVnum = V;
		graph->_gAdjListArray = (struct AdjList *)malloc(V * sizeof(struct AdjList));

		for (int i = 0; i < graph->_gVnum; ++i)
			graph->_gAdjListArray[i]._listHead = nullptr;

		return graph;
	}


	// Adds an Edge to an Undirected Graph
	void  addEdge(struct UDGraphDijkstra * graph, int src, int dest, int weight)
	{
		// Edge: [src]->[dest]
		// A new NODE is added to the AdjacencyList-of-[src]
		// The new NODE is added at the beginning as the HEAD-of-AdjacencyList ??
		struct AdjListNode * newNode = newAdjListNode(dest, weight);
		newNode->_nPnext = graph->_gAdjListArray[src]._listHead;
		graph->_gAdjListArray[src]._listHead = newNode;

		// Undirected Graph
		newNode = newAdjListNode(src, weight);
		newNode->_nPnext = graph->_gAdjListArray[dest]._listHead;
		graph->_gAdjListArray[dest]._listHead = newNode;
	}

	// Represent a MIN heap node
	struct MinHeapNode
	{
		int   _MHNVnum;
		int   _MHNDist;
	};


	// Represent a MIN heap
	struct MinHeap
	{
		int   _MHsize;		// number of heap nodes present currently
		int   _MHcapacity;	// capacity of min heap
		int   *_MHPpos;		// decreaseKey() ?
		struct MinHeapNode  ** _MHPParrayNode;	//
	};

	// Utility function to create a new Min Heap Node
	struct MinHeapNode * newMinHeapNode(int v, int dist)
	{
		struct MinHeapNode * minHeapNode =
			(struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
		
		minHeapNode->_MHNVnum = v;
		minHeapNode->_MHNDist = dist;

		return minHeapNode;
	}
	// Utility function to create a new Min Heap
	struct MinHeap * createMinHeap(int capacity)
	{
		struct MinHeap * minHeap =
			(struct MinHeap *) malloc(sizeof(struct MinHeap));

		minHeap->_MHPpos = (int *)malloc(capacity * sizeof(int));
		minHeap->_MHsize = 0;
		minHeap->_MHcapacity = capacity;
		minHeap->_MHPParrayNode =
			(struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode));

		return minHeap;
	}

	// Utility function to swap two nodes of min heap. needed for min heapify;
	void swapMinHeapNode(struct MinHeapNode ** a, struct MinHeapNode ** b)
	{
		struct MinHeapNode * t = *a;
		*a = *b;
		*b = t;
	}


	// Utility function to heapify at given idx
	// This function also updates position of nodes when they are swapped ???
	// Position is needed for decreaseKey()

	void  minHeapify(struct MinHeap * minHeap, int idx)
	{
		int smallest, left, right;
		smallest = idx;
		left = 2 * idx + 1;
		right = 2 * idx + 2;

		if (left < minHeap->_MHsize &&
			minHeap->_MHPParrayNode[left]->_MHNDist < minHeap->_MHPParrayNode[smallest]->_MHNDist)
			smallest = left;

		if (right < minHeap->_MHsize &&
			minHeap->_MHPParrayNode[right]->_MHNDist < minHeap->_MHPParrayNode[smallest]->_MHNDist)
			smallest = right;

		if (smallest != idx)
		{
			// The nodes to be swapped in min heap
			MinHeapNode *smallestNode = minHeap->_MHPParrayNode[smallest];
			MinHeapNode *idxNode = minHeap->_MHPParrayNode[idx];

			// Swap positions
			minHeap->_MHPpos[smallestNode->_MHNVnum] = idx;
			minHeap->_MHPpos[idxNode->_MHNVnum] = smallest;

			// Swap nodes
			swapMinHeapNode(&minHeap->_MHPParrayNode[smallest], &minHeap->_MHPParrayNode[idx]);

			minHeapify(minHeap, smallest);
		}
	}

	// A utility function to check if the given minHeap is empty or not
	int isEmpty(struct MinHeap* minHeap)
	{
		return minHeap->_MHsize == 0;
	}

	// Standard function to extract minimum node from heap
	struct MinHeapNode* extractMin(struct MinHeap* minHeap)
	{
		if (isEmpty(minHeap))
			return NULL;

		// Store the root node
		struct MinHeapNode* root = minHeap->_MHPParrayNode[0];

		// Replace root node with last node
		struct MinHeapNode* lastNode = minHeap->_MHPParrayNode[minHeap->_MHsize - 1];
		minHeap->_MHPParrayNode[0] = lastNode;

		// Update position of last node
		minHeap->_MHPpos[root->_MHNVnum] = minHeap->_MHsize - 1;
		minHeap->_MHPpos[lastNode->_MHNVnum] = 0;

		// Reduce heap size and heapify root
		--minHeap->_MHsize;
		minHeapify(minHeap, 0);

		return root;
	}

	// Function to decreasy dist value of a given vertex v. This function
	// uses pos[] of min heap to get the current index of node in min heap
	void decreaseKey(struct MinHeap* minHeap, int v, int dist)
	{
		// Get the index of v in  heap array
		int i = minHeap->_MHPpos[v];

		// Get the node and update its dist value
		minHeap->_MHPParrayNode[i]->_MHNDist = dist;

		// Travel up while the complete tree is not hepified.
		// This is a O(Logn) loop
		while (i && minHeap->_MHPParrayNode[i]->_MHNDist < minHeap->_MHPParrayNode[(i - 1) / 2]->_MHNDist)
		{
			// Swap this node with its parent
			minHeap->_MHPpos[minHeap->_MHPParrayNode[i]->_MHNVnum] = (i - 1) / 2;
			minHeap->_MHPpos[minHeap->_MHPParrayNode[(i - 1) / 2]->_MHNVnum] = i;
			swapMinHeapNode(&minHeap->_MHPParrayNode[i], &minHeap->_MHPParrayNode[(i - 1) / 2]);

			// move to parent index
			i = (i - 1) / 2;
		}
	}

	// A utility function to check if a given vertex
	// 'v' is in min heap or not
	bool isInMinHeap(struct MinHeap *minHeap, int v)
	{
		if (minHeap->_MHPpos[v] < minHeap->_MHsize)
			return true;
		return false;
	}

	// A utility function used to print the solution
	void printArr(int dist[], int n)
	{
		printf("Vertex   Distance from Source\n");
		for (int i = 0; i < n; ++i)
			printf("%d \t\t %d\n", i, dist[i]);
	}


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	// The main function that calculates distances of shortest paths from src to all
	// vertices. It is a O(ELogV) function
	void dijkstra(struct UDGraphDijkstra* graph, int src)
	{
		int V = graph->_gVnum;// Get the number of vertices in graph
		///int dist[V];      // dist values used to pick minimum weight edge in cut
		int * dist = (int*)malloc(sizeof(int) * V);

		// minHeap represents set E
		struct MinHeap* minHeap = createMinHeap(V);

		// Initialize min heap with all vertices. dist value of all vertices 
		for (int v = 0; v < V; ++v)
		{
			dist[v] = INT_MAX;
			minHeap->_MHPParrayNode[v] = newMinHeapNode(v, dist[v]);
			minHeap->_MHPpos[v] = v;
		}

		// Make dist value of src vertex as 0 so that it is extracted first
		minHeap->_MHPParrayNode[src] = newMinHeapNode(src, dist[src]);
		minHeap->_MHPpos[src] = src;
		dist[src] = 0;
		decreaseKey(minHeap, src, dist[src]);

		// Initially size of min heap is equal to V
		minHeap->_MHsize = V;

		// In the following loop, min heap contains all nodes
		// whose shortest distance is not yet finalized.
		while (!isEmpty(minHeap))
		{
			// Extract the vertex with minimum distance value
			struct MinHeapNode* minHeapNode = extractMin(minHeap);
			int u = minHeapNode->_MHNVnum; // Store the extracted vertex number

			// Traverse through all adjacent vertices of u (the extracted
			// vertex) and update their distance values
			struct AdjListNode* pCrawl = graph->_gAdjListArray[u]._listHead;
			while (pCrawl != NULL)
			{
				int v = pCrawl->_nDest;

				// If shortest distance to v is not finalized yet, and distance to v
				// through u is less than its previously calculated distance
				if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
					pCrawl->_nWeight + dist[u] < dist[v])
				{
					dist[v] = dist[u] + pCrawl->_nWeight;

					// update distance value in min heap also
					decreaseKey(minHeap, v, dist[v]);
				}
				pCrawl = pCrawl->_nPnext;
			}
		}

		// print the calculated shortest distances
		printArr(dist, V);
	}


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	int main_UDWGAdjListDijkstraALGO()
	{
		// create the graph given in above figure
		int V = 9;
		struct UDGraphDijkstra* graph = createGraph(V);
		addEdge(graph, 0, 1, 4);
		addEdge(graph, 0, 7, 8);
		addEdge(graph, 1, 2, 8);
		addEdge(graph, 1, 7, 11);
		addEdge(graph, 2, 3, 7);
		addEdge(graph, 2, 8, 2);
		addEdge(graph, 2, 5, 4);
		addEdge(graph, 3, 4, 9);
		addEdge(graph, 3, 5, 14);
		addEdge(graph, 4, 5, 10);
		addEdge(graph, 5, 6, 2);
		addEdge(graph, 6, 7, 1);
		addEdge(graph, 6, 8, 6);
		addEdge(graph, 7, 8, 7);

		dijkstra(graph, 0);

		return 0;
	}
}
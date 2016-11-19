/************************************************************************

  Reference:
	http://www.cnblogs.com/skywang12345/p/3711483.html
	https://github.com/wangkuiwu/datastructs_and_algorithm/blob/master/source/graph/iterator/udg/c/matrix_udg.c

  

/************************************************************************/
///  >> 11/19/22/2016 BY.gaohuancai QQ1293302539 <<
#include "UDGraphTraverseA.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAX  (100)
#define isLetter(a) ((((a)>='a') && ((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))


namespace nsALGDepthFirstUDGraph
{

	//adjacency matrix..
	typedef struct _graph
	{
		char vexs[MAX];			// Vertex Set
		int  vexnum;			// Vertex Counts
		int  edgnum;			// Edge Counts
		int  matrix[MAX][MAX];	// Adjacency Matrix
	} Graph, *PGraph;


	// location of 'CH' in struct _graph::matrix
	static int get_position(Graph g, char ch)
	{
		for (int i = 0; i < g.vexnum; ++i)
		{
			if (ch == g.vexs[i])
				return i;
		}

		return -1;
	}

	// Read a char from STDIN..
	static char read_char()
	{
		char ch;
		do {

			ch = getchar();
		} while (!isLetter(ch));

		return ch;
	}


	// Graph Creation /self input
	Graph * create_graph()
	{
		int v;
		int e;
		Graph * pG;

		//
		fprintf(stderr, "Input Vertex Counts:");
		scanf("%d", &v);
		fprintf(stderr, "Input Edge Counts:");
		scanf("%d", &e);
		if (v < 1 || e < 1 || (e >(v * (v - 1))))
		{
			fprintf(stderr, "** input error: invalid parameters..\n");
			return nullptr;
		}

		if (nullptr == (pG = (Graph *)malloc(sizeof(Graph))))
			return nullptr;

		memset(pG, 0, sizeof(Graph));

		//
		pG->vexnum = v;
		pG->edgnum = e;

		// vertex initialization
		for (int i = 0; i < pG->vexnum; ++i)
		{
			fprintf(stderr, "Vertex(%d) : ", i);
			pG->vexs[i] = read_char();
		}

		// edge initialization
		for (int i = 0; i < pG->edgnum; ++i)
		{
			// 
			fprintf(stderr, " Starting Point of EDGE(%d): \n", i);
			char c0 = read_char();
			fprintf(stderr, " Ending Point of EDGE(%d): \n", i);
			char c1 = read_char();

			int p0 = get_position(*pG, c0);
			int p1 = get_position(*pG, c1);
			if (-1 == p0 || -1 == p1)
			{
				fprintf(stderr, "** input error : invalid edge..\n");
				free(pG);
				pG = nullptr;
				return nullptr;
			}

			pG->matrix[p0][p1] = 1;
			pG->matrix[p1][p0] = 1;
		}

		return pG;
	}


	// Graph Creation with application-default-matrix..
	Graph * create_example_graph()
	{
		char vexs[] = 
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G' 
		};

		char edges[][2] = 
		{
			  { 'A', 'C' }
			, { 'A', 'D' }
			, { 'A', 'F' }
			, { 'B', 'C' }
			, { 'C', 'D' }
			, { 'E', 'G' }
			, { 'F', 'G' }
		};

		int vlen = LENGTH(vexs);
		int elen = LENGTH(edges);

		int i, p1, p2;

		Graph * pG;
		if (nullptr == (pG = (Graph *)malloc(sizeof(Graph))))
			return nullptr;
		memset(pG, 0, sizeof(Graph));

		// Vertex and Edge Counts initialization..
		pG->vexnum = vlen;
		pG->edgnum = elen;

		// Vertex Init
		for (int i = 0; i < pG->edgnum; ++i)
			pG->vexs[i] = vexs[i];

		// Edge Init
		for (int i = 0; i < pG->edgnum; ++i)
		{
			int p0 = get_position(*pG, edges[i][0]);
			int p1 = get_position(*pG, edges[i][1]);

			pG->matrix[p0][p1] = 1;
			pG->matrix[p1][p0] = 1;
		}


		return pG;
	}

	// first index of the adjacency vertex RETURNED
	static int first_vertex(Graph G, int v)
	{
		if (v < 0 || v >(G.vexnum - 1))
			return -1;

		for (int i = 0; i < G.vexnum; ++i)
		{
			if (1 == G.matrix[v][i])
				return i;
		}

		return -1;
	}

	// first index of the adjacency vertex RELATIVE-TO index-W Returned.
	static int next_vertix(Graph G, int v, int w)
	{
		if (v < 0 || v >(G.vexnum - 1) || w < 0 || w >(G.vexnum - 1))
			return -1;

		for (int i = w + 1; i < G.vexnum; ++i)
		{
			if (1 == G.matrix[v][i])
				return i;
		}

		return -1;
	}


	// Recursive Implementation of Depth-First-Search of Graph....
	static void DFS(Graph G, int i, int * visited)
	{

		visited[i] = 1;
		fprintf(stderr, "%c ", G.vexs[i]);

		// traverse all the adjacency vertex
		for (int w = first_vertex(G, i); w >= 0; w = next_vertix(G, i, w))
		{
			if (!visited[w])
				DFS(G, w, visited);
		}
	}

	//
	static void DFSTraverse(Graph G)
	{
		int visited[MAX];// mark vertex visited.

		// initialization of memory block of marks..
		// memset(visited,0,sizeof(int)*MAX);
		for (int i = 0; i < G.vexnum; ++i)
			visited[i] = 0;

		fprintf(stderr, "DFS: ");
		for (int i = 0; i < G.vexnum; ++i)
		{
			if (!visited[i])
				DFS(G, i, visited);
		}

		fprintf(stderr, "\n");
	}


	// Breadth -First -Search
	static void BFS(Graph G)
	{
		int head = 0; 
		int rear = 0;
		int queue[MAX];	//
		int visited[MAX];//

		for (int i = 0; i < G.vexnum; ++i)
			visited[i] = 0;


		fprintf(stderr, "BFS: ");
		for (int i = 0; i < G.vexnum; ++i)
		{
			if (!visited[i])
			{
				visited[i] = 1;
				fprintf(stderr, "%c ", G.vexs[i]);
				queue[rear++] = i;	// into queue

			}

			while (head != rear)
			{
				int j = queue[head++];	// out queue..
				for (int k = first_vertex(G, j); k >= 0; k = next_vertix(G, j, k))
				{
					if (!visited[k])
					{
						visited[k] = 1;
						fprintf(stderr, "%c ", G.vexs[k]);
						queue[rear++] = k;
					}
				}
			}
		}

		fprintf(stderr, "\n");
	}


	// matrix print
	void print_graph(Graph G)
	{
		int i, j;

		printf("matrix Graph:\n");
		for (i = 0; i < G.vexnum; i++)
		{
			for (j = 0; j < G.vexnum; j++)
				printf("%d ", G.matrix[i][j]);
			printf("\n");
		}
	}

	int main_UDGrah_Depth_First_Search()
	{

		Graph * pG;
		// 自定义"图"(输入矩阵队列)
		//pG = create_graph();
		// 采用已有的"图"
		pG = create_example_graph();

		print_graph(*pG);
		DFSTraverse(*pG);
		BFS(*pG);        


		return 0;
	}
}



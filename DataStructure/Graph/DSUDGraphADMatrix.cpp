/****************************************************************************************************************
/****************************************************************************************************************

  BASIC CONCEPTION:


  https://en.wikipedia.org/wiki/Graph_(abstract_data_type)
  /// Graph (abstract data type)
	  In computer science, a graph is an abstract data type that is meant to
	  -	implement the undirected graph and directed graph concepts from mathematics.

  /// Operations
	  The basic operations provided by a graph data structure G usually include:
  /// Different data structures for the representation of graphs are used in practice:
	  // Adjacency list[2]
	  // Adjacency matrix[3]
      // Incidence matrix[4]

  /// Adjacency lists are generally preferred because they efficiently represent sparse graphs.
  /// An adjacency matrix is preferred if the graph is dense, that is the number of edges |E |
  /// is close to the number of vertices squared, |V |2, or if one must be able to quickly look up
  /// if there is an edge connecting two vertices.


  Adjacency Matrix Representation of Graph..

  /// http://www.cnblogs.com/skywang12345/p/3691463.html
  /// http://www.cnblogs.com/skywang12345/
  /// https://github.com/wangkuiwu/datastructs_and_algorithm/blob/master/source/graph/basic/udg/c/matrix_udg.c

/****************************************************************************************************************/
///  >> 11/18/10/2016 BY.gaohuancai QQ1293302539 <<

#include "DSUDGraphADMatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

namespace nsDSUDGraphCADMatrix
{
#define MAX 100
#define isLetter(a)    ((((a) >='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)      (sizeof(a)/sizeof(a[0]))


	/// 
	/// Adjacency Matrix.. 
	///
	typedef struct _graph
	{
		char	_gVertex[MAX];		// vertex/points storage.
		int		_gVertexCount;		// vertex counts.

		int		_gEdgeCount;		// edge counts.
		int		_gMatrix[MAX][MAX];	// 2-dimension array for matrix information.

	} AMGraph, *PAMGraph;


	// 返回 ch 在 adjacency matrix中的位置;
	static int get_position(AMGraph g, char ch)
	{
		int i;
		for (int i = 0; i < g._gVertexCount; ++i)
		{
			if (ch == g._gVertex[i])
				return i;
		}

		return -1;
	}
	

	//Read a char From STDIN
	static char read_char()
	{
		char ch;

		do {
			ch = getchar();
		} while (!isLetter(ch));

		return ch;
	}

	//Graph Creation From STDIN
	AMGraph* create_AM_graph()
	{
		char c1, c2;
		int v, e;
		int i, p1, p2;
		AMGraph* pG;

		//Vertex Counts Input
		printf("input vertex number: ");
		scanf("%d", &v);
		//Edge Counts Input
		printf("input edge number: ");
		scanf("%d", &e);
		if (v < 1 || e < 1 || (e >(v * (v - 1))))
		{
			printf("input error: invalid parameters!\n");
			return NULL;
		}

		//Graph Storage Allocation..
		//TODO:need to memory block optimization..
		if ((pG = (AMGraph*)malloc(sizeof(AMGraph))) == NULL)
			return NULL;
		memset(pG, 0, sizeof(AMGraph));


		/// 
		/// initialization
		/// 

		// Vertex
		pG->_gVertexCount = v;
		for (i = 0; i < pG->_gVertexCount; i++)
		{
			printf("vertex(%d): ", i);
			pG->_gVertex[i] = read_char();
		}

		// Edge
		pG->_gEdgeCount = e;
		for (i = 0; i < pG->_gEdgeCount; i++)
		{
			fprintf(stderr, "input CHAR AS starting point of <edge-%d>:\n", i);
			c1 = read_char();	/// Starting Point of Edge
			fprintf(stderr, "input CHAR AS ending point of <edge-%d>:\n", i);
			c2 = read_char();	/// Ending Point of Edge

			p1 = get_position(*pG, c1);
			p2 = get_position(*pG, c2);
			if (p1 == -1 || p2 == -1)
			{
				printf("input error: invalid edge!\n");
				free(pG);
				return NULL;
			}

			pG->_gMatrix[p1][p2] = 1;
			pG->_gMatrix[p2][p1] = 1;
		}

		return pG;
	}


	//Graph Creation With Application-Default-Adjacency-Matrix..
	AMGraph* create_example_AM_graph()
	{
		char vexs[] =
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G'
		};
		char edges[][2] = 
		{
			{ 'A', 'C' },
			{ 'A', 'D' },
			{ 'A', 'F' },
			{ 'B', 'C' },
			{ 'C', 'D' },
			{ 'E', 'G' },
			{ 'F', 'G' }
		};
		int vlen = LENGTH(vexs);
		int elen = LENGTH(edges);
		int i, p1, p2;
		AMGraph* pG;

		//Memory block allocation.
		if ((pG = (AMGraph*)malloc(sizeof(AMGraph))) == NULL)
			return NULL;
		memset(pG, 0, sizeof(AMGraph));

		// Vertex Initialization
		pG->_gVertexCount = vlen;
		for (i = 0; i < pG->_gVertexCount; i++)
		{
			pG->_gVertex[i] = vexs[i];
		}

		// Edge Initialization
		pG->_gEdgeCount = elen;
		for (i = 0; i < pG->_gEdgeCount; i++)
		{
			p1 = get_position(*pG, edges[i][0]);
			p2 = get_position(*pG, edges[i][1]);

			pG->_gMatrix[p1][p2] = 1;
			pG->_gMatrix[p2][p1] = 1;
		}

		return pG;
	}


	// Graph Print.
	char titile[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' ,'J', 'K','L','M','N','O','P','Q'};
	void print_AM_graph(AMGraph G)
	{
		int i, j, k;

		printf("matrix Graph:\n");
		printf("\n   A B C D E F G\n\n");
		for (i = 0; i < G._gVertexCount; i++)
		{
			printf("%c  ", titile[i]);
			for (j = 0; j < G._gVertexCount; j++)
				printf("%d ", G._gMatrix[i][j]);
			printf("\n");
		}
	}



	int main_DSGraphADMatrix()
	{

		AMGraph* pAMG;
		fprintf(stderr, "\t input 0, to select self defined graph:\n");
		fprintf(stderr, "\t input 1, to use application default graph:\n");
		fprintf(stderr, "\t input 101, to exit program..\n");
		int option = -1;
		while (true)
		{
			scanf("%d", &option);

			if (0 == option)
			{
				// self defined graph
				pAMG = create_AM_graph();
				break;
			}
			else if (1 == option)
			{
				// default vertex and edge set of graph
				pAMG = create_example_AM_graph();
				break;
			}
			else if (101 == option)
			{
				pAMG = nullptr;
				break;
			}
			else
			{
				fprintf(stderr, "\t Sorry, option is non-existence...\n");
				fprintf(stderr, "\t please input 0 for user defined, 1 for default,101 for exit program.\n");
			}
		}

		// matrix print
		if (nullptr != pAMG)
		{
			print_AM_graph(*pAMG);
			free(pAMG);
			pAMG = nullptr;
		}

		return 0;
	}
};




namespace nsDSUDGraphCPPADMatrix
{
	//Graph Creation with data from STDIN
	MatrixUDG::MatrixUDG()
	{
		fprintf(stderr, "input Vertex Counts: \n");
		scanf("%d", &_UDGVertCounts);
		fprintf(stderr, "input edge counts:  \n");
		scanf("%d", &_UDGEdgeCount);

		if (_UDGVertCounts < 1 || _UDGEdgeCount < 1 || (_UDGEdgeCount >(_UDGVertCounts * (_UDGVertCounts - 1))))
		{
			fprintf(stderr, "input error: invalid parameters...\n");
			return;
		}

		//vertex initialization...
		for (int i = 0; i < _UDGVertCounts; ++i)
		{
			fprintf(stderr, "Vertex(%d):\n", i);
			_UDGVert[i] = readChar();
		}

		//edge initialization.....
		for (int i = 0; i < _UDGEdgeCount; ++i)
		{
			fprintf(stderr, "input Starting POINT of edge(%d): \n", i);
			char c0 = readChar();
			fprintf(stderr, "input Ending POINT of edge(%d): \n", i);
			char c1 = readChar();

			int p0 = getPosition(c0);
			int p1 = getPosition(c1);
			if (-1 == p0 || -1 == p1)
			{
				fprintf(stderr, "input error: invalid edge..\n");
				return;
			}

			_UDGMatrix[p0][p1] = 1;
			_UDGMatrix[p1][p0] = 1;
		}

	}

	//
	MatrixUDG::~MatrixUDG()
	{
	}

	//
	MatrixUDG::MatrixUDG(char vexs[], int vlen, char edges[][2], int elen)
		: _UDGVertCounts(vlen)
		, _UDGEdgeCount(elen)
	{
		memset(&_UDGMatrix[0][0], 0, (MAX * MAX));
		//vertex initialization
		for (int i = 0; i < _UDGVertCounts; ++i)
			_UDGVert[i] = vexs[i];

		//edge initialization
		for (int i = 0; i < _UDGEdgeCount; ++i)
		{
			int p0 = getPosition(edges[i][0]);//starting point
			int p1 = getPosition(edges[i][1]);//starting point

			_UDGMatrix[p0][p1] = 1;
			_UDGMatrix[p1][p0] = 1;
		}

	}

	void MatrixUDG::print()
	{
		fprintf(stderr, "Adjacency Matrix Graph: \n");
		for (int i = 0; i < _UDGVertCounts; ++i)
		{
			for (int j = 0; j < _UDGVertCounts; ++j)
			{
				fprintf(stderr, "%d ", _UDGMatrix[i][j]);
			}
			fprintf(stderr, "\n");
		}
	}


	char MatrixUDG::readChar()
	{
		char ch;
		do {
			scanf("%c", &ch);

		} while (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')));

		return ch;
	}


	int  MatrixUDG::getPosition(char ch)
	{
		for (int i = 0; i < _UDGVertCounts; ++i)
		{
			if (ch == _UDGVert[i])
				return i;
		}

		return -1;
	}


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	int main_DSUDGraphCADMatrix()
	{
		char vexs[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
		char edges[][2] = {
			{ 'A', 'C' },
			{ 'A', 'D' },
			{ 'A', 'F' },
			{ 'B', 'C' },
			{ 'C', 'D' },
			{ 'E', 'G' },
			{ 'F', 'G' } };
		int vlen = sizeof(vexs) / sizeof(vexs[0]);
		int elen = sizeof(edges) / sizeof(edges[0]);
		MatrixUDG* pG;

		//pG = new MatrixUDG();
		pG = new MatrixUDG(vexs, vlen, edges, elen);

		pG->print();   //show data..

		return 0;
	}

}
/************************************************************************

  http://blog.chinaunix.net/uid-21813514-id-3866951.html

/************************************************************************/

#include "DSGraphA.h"

#include <stdio.h>
#include <stdlib.h>
//#include <curses.h>

namespace nsDSGraphA
{
	typedef char VertexType;                //顶点类型应由用户定义;
	typedef int EdgeType;                   //边上的权值类型应由用户定义;

#define MAXVEX		100             //最大顶点数，应由用户定义;
#define INFINITY    65535               //用65535来代表无穷大;
#define DEBUG

	typedef struct
	{
		VertexType vexs[MAXVEX];            //顶点表;
		EdgeType   arc[MAXVEX][MAXVEX];         //邻接矩阵，可看作边;
		int numVertexes, numEdges;      //图中当前的顶点数和边数;
	}Graph;

	//定位;
	int locates(Graph *g, char ch)
	{
		int i = 0;
		for (i = 0; i < g->numVertexes; i++)
		{
			if (g->vexs[i] == ch)
			{
				break;
			}
		}
		if (i >= g->numVertexes)
		{
			return -1;
		}

		return i;
	}

	//建立一个无向网图的邻接矩阵表示;
	void CreateGraph(Graph *g)
	{
		int i, j, k, w;
		printf("输入顶点数和边数:\n");
		scanf("%d,%d", &(g->numVertexes), &(g->numEdges));

#ifdef DEBUG
		printf("%d %d\n", g->numVertexes, g->numEdges);
#endif

		for (i = 0; i < g->numVertexes; i++)
		{
			g->vexs[i] = getchar();
			while (g->vexs[i] == '\n')
			{
				g->vexs[i] = getchar();
			}
		}

#ifdef DEBUG
		for (i = 0; i < g->numVertexes; i++)
		{
			printf("%c ", g->vexs[i]);
		}
		printf("\n");
#endif


		for (i = 0; i < g->numEdges; i++)
		{
			for (j = 0; j < g->numEdges; j++)
			{
				g->arc[i][j] = INFINITY; //邻接矩阵初始化;
			}
		}
		for (k = 0; k < g->numEdges; k++)
		{
			char p, q;
			printf("输入边(vi,vj)上的下标i，下标j和权值:\n");

			p = getchar();
			while (p == '\n')
			{
				p = getchar();
			}
			q = getchar();
			while (q == '\n')
			{
				q = getchar();
			}
			scanf("%d", &w);

			int m = -1;
			int n = -1;
			m = locates(g, p);
			n = locates(g, q);
			if (n == -1 || m == -1)
			{
				fprintf(stderr, "there is no this vertex.\n");
				return;
			}
			//getchar();
			g->arc[m][n] = w;
			g->arc[n][m] = g->arc[m][n];  //因为是无向图，矩阵对称;
		}
	}

	//打印图;
	void printGraph(Graph g)
	{
		int i, j;
		for (i = 0; i < g.numVertexes; i++)
		{
			for (j = 0; j < g.numVertexes; j++)
			{
				printf("%d  ", g.arc[i][j]);
			}
			printf("\n");
		}
	}

	int main_DSGraphA()
	{
		Graph g;

		//adjacency matrix;
		CreateGraph(&g);
		printGraph(g);

		return 0;
	}

}
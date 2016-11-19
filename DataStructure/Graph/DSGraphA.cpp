/************************************************************************

  http://blog.chinaunix.net/uid-21813514-id-3866951.html

/************************************************************************/

#include "DSGraphA.h"

#include <stdio.h>
#include <stdlib.h>
//#include <curses.h>

namespace nsDSGraphA
{
	typedef char VertexType;                //��������Ӧ���û�����;
	typedef int EdgeType;                   //���ϵ�Ȩֵ����Ӧ���û�����;

#define MAXVEX		100             //��󶥵�����Ӧ���û�����;
#define INFINITY    65535               //��65535�����������;
#define DEBUG

	typedef struct
	{
		VertexType vexs[MAXVEX];            //�����;
		EdgeType   arc[MAXVEX][MAXVEX];         //�ڽӾ��󣬿ɿ�����;
		int numVertexes, numEdges;      //ͼ�е�ǰ�Ķ������ͱ���;
	}Graph;

	//��λ;
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

	//����һ��������ͼ���ڽӾ����ʾ;
	void CreateGraph(Graph *g)
	{
		int i, j, k, w;
		printf("���붥�����ͱ���:\n");
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
				g->arc[i][j] = INFINITY; //�ڽӾ����ʼ��;
			}
		}
		for (k = 0; k < g->numEdges; k++)
		{
			char p, q;
			printf("�����(vi,vj)�ϵ��±�i���±�j��Ȩֵ:\n");

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
			g->arc[n][m] = g->arc[m][n];  //��Ϊ������ͼ������Գ�;
		}
	}

	//��ӡͼ;
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
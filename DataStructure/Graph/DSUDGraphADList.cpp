/************************************************************************
  
  http://www.cnblogs.com/skywang12345/p/3707607.html#anchor3
  https://github.com/wangkuiwu/datastructs_and_algorithm/blob/master/source/graph/basic/udg/c/list_udg.c


  http://www.cnblogs.com/skywang12345/p/3707610.html
  https://github.com/wangkuiwu/datastructs_and_algorithm/blob/master/source/graph/basic/udg/cplus/ListUDG.cpp
/************************************************************************/
///  >> 11/18/23/2016 BY.gaohuancai QQ1293302539 <<

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define  MAX  100
#define isLetter(a)   ((((a)>='a') && ((a)<='z')) || (((a)>='A') && ((a)<='Z')))
#define LENGTH(a)     (sizeof(a)/sizeof(a[0]))

//UDGraphCPPADList
#include <iomanip>
#include <iostream>
#include <vector>

#include "DSUDGraphADList.h"


namespace nsDSUDGraphCADList
{

	// List-Node used Contained in the Vertex of the Adjacency Table
	typedef struct _ENode
	{
		int  _ENode_pos;					// vertex location to which THIS edge point
		struct _ENode *_ENode_next_edge;	// Point to next arc

	} ENode, *PENode;

	// vertex of the Adjacency Table..
	typedef struct _VNode
	{
		char _vert_node_data;			// Vertex information.
		ENode * _vert_node_first_edge;	// First arc of THIS Vertex to which THIS Vertex Point
	} VNode, *PVNode;


	// Adjacency Table..
	typedef struct _LGraph
	{
		int  _LG_vert_count;		// Vertex Counts of the Graph
		int  _LG_edge_count;		// Edge Counts of the Graph

		VNode  _LG_verts[MAX];	// Vertex Block..
	}LGraph, *PLGraph;


	// location of CH in the Matrix;
	static int get_position(LGraph g, char ch)
	{
		for (int i = 0; i < g._LG_vert_count; ++i)
		{
			if (g._LG_verts[i]._vert_node_data == ch)
			{
				return i;
			}
		}

		return -1;
	}

	// get a CHAR from STDIN
	static char read_char()
	{
		char ch;
		do {
			ch = getchar();
		} while (!isLetter(ch));

		return ch;
	}


	// append Node onto the TAIL-of-List.
	static void link_last(ENode * list, ENode * node)
	{
		if (nullptr == list || nullptr == node)return;

		ENode * p = list;

		while (p->_ENode_next_edge)
			p = p->_ENode_next_edge;

		p->_ENode_next_edge = node;

	}

	// Graph Creation of Adjacency-Table <self-defined>
	LGraph * create_lgraph()
	{
		LGraph * pG = nullptr;
		// memory block allocation and initialization
		if (nullptr == (pG = (LGraph *)malloc(sizeof(LGraph))))
			return nullptr;
		memset(pG, 0, sizeof(LGraph));

		//
		fprintf(stderr, "input Vertex Counts: ");
		scanf("%d", &pG->_LG_vert_count);
		fprintf(stderr, "input edge Counts: ");
		scanf("%d", &pG->_LG_edge_count);
		if (pG->_LG_vert_count < 1 || pG->_LG_edge_count < 1 || (pG->_LG_edge_count >(pG->_LG_vert_count *(pG->_LG_vert_count - 1))))
		{
			fprintf(stderr, "** Input Error: invalid parameters..\n");
			free(pG); 
			pG = nullptr;
			return nullptr;
		}

		// Vertex Initialization..
		for (int i = 0; i < pG->_LG_vert_count; ++i)
		{
			fprintf(stderr, "Vertex (%d): ", i);
			pG->_LG_verts[i]._vert_node_data = read_char();
			pG->_LG_verts[i]._vert_node_first_edge = nullptr;
		}

		//
		for (int i = 0; i < pG->_LG_vert_count; ++i)
		{
			fprintf(stderr, " input Starting Point of EDGE(%d): ", i);
			char c0 = read_char();
			fprintf(stderr, " input Ending Point of EDGE(%d): ", i);
			char c1 = read_char();

			int p0 = get_position(*pG, c0);
			int p1 = get_position(*pG, c1);

			// node0 Appended to TAIL of Stating-Point-List..
			ENode * node0 = (ENode *)malloc(sizeof(ENode));
			memset(node0, 0, sizeof(ENode));
			node0->_ENode_pos = p1;
			if (nullptr == pG->_LG_verts[p0]._vert_node_first_edge)
				pG->_LG_verts[p0]._vert_node_first_edge = node0;
			else
				link_last(pG->_LG_verts[p0]._vert_node_first_edge, node0);

			// node1 Appended to TAIL of Ending-Point-List..
			ENode * node1 = (ENode *)malloc(sizeof(ENode));
			memset(node1, 0, sizeof(ENode));
			node1->_ENode_pos = p0;
			if (nullptr == pG->_LG_verts[p1]._vert_node_first_edge)
				pG->_LG_verts[p1]._vert_node_first_edge = node1;
			else
				link_last(pG->_LG_verts[p1]._vert_node_first_edge, node1);

		}

		return pG;
	}

	// Graph Creation of Adjacency-Table <application-default-data>
	LGraph * create_example_lgraph()
	{

		char vexs[] =
		{'A', 'B', 'C', 'D', 'E', 'F', 'G' };

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


		// Graph memory block Allocation and initialization.
		LGraph * pG = nullptr;
		if (nullptr == (pG = (LGraph *)malloc(sizeof(LGraph))))
			return nullptr;
		memset(pG, 0, sizeof(LGraph));


		pG->_LG_vert_count = LENGTH(vexs);
		pG->_LG_edge_count = LENGTH(edges);

		// Vertex Initialization of Adjacency Table.
		for (int i = 0; i < pG->_LG_vert_count; ++i)
		{
			pG->_LG_verts[i]._vert_node_data = vexs[i];
			pG->_LG_verts[i]._vert_node_first_edge = nullptr;
		}

		// Edge Initialization of Adjacency Tale....
		for (int i = 0; i < pG->_LG_vert_count; ++i)
		{
			//Starting and Ending point of EDGE<i>
			char c0 = edges[i][0];
			char c1 = edges[i][1];

			// Position of Starting and Ending Point in Matrix..
			int p0 = get_position(*pG, c0);
			int p1 = get_position(*pG, c1);

			// node0 initialization..
			ENode * node0 = (ENode*)malloc(sizeof(ENode));
			memset(node0, 0, sizeof(ENode));

			node0->_ENode_pos = p1;
			// append node0 to List-Tail-of-p0
			if (nullptr == (pG->_LG_verts[p0]._vert_node_first_edge))
				pG->_LG_verts[p0]._vert_node_first_edge = node0;
			else
				link_last(pG->_LG_verts[p0]._vert_node_first_edge, node0);


			// node1 initialization..
			ENode * node1 = (ENode*)malloc(sizeof(ENode));
			memset(node1, 0, sizeof(ENode));
			node1->_ENode_pos = p0;
			// append node1 to List-Tail-of-p1
			if (nullptr == pG->_LG_verts[p1]._vert_node_first_edge)
				pG->_LG_verts[p1]._vert_node_first_edge = node1;
			else
				link_last(pG->_LG_verts[p1]._vert_node_first_edge, node1);
			
		}

		return pG;
	}


	// print adjacency Table.
	void print_lgraph(LGraph G)
	{
		fprintf(stderr, "List Graph..\n\n");

		for (int i = 0; i < G._LG_vert_count; ++i)
		{
			fprintf(stderr, "\t%d[%c]--", i, G._LG_verts[i]._vert_node_data);
			ENode * node = G._LG_verts[i]._vert_node_first_edge;

			while (nullptr != node)
			{
				fprintf(stderr, "--%d<%c>", node->_ENode_pos, G._LG_verts[node->_ENode_pos]._vert_node_data);
				node = node->_ENode_next_edge;
			}

			fprintf(stderr, "\n");
		}
	}

	// 
	int main_DSUDGraphCADList()
	{
		LGraph * pG = nullptr;
		fprintf(stderr, "\t input 0, to select self defined graph:\n");
		fprintf(stderr, "\t input 1, to use application default graph:\n");
		fprintf(stderr, "\t input 101, to exit program..\n");
		int option = -1;

		while (true)
		{
			scanf("%d", &option);

			if ( 0 == option)
			{
				// self-defined Graph..
				pG = create_lgraph();
				break;
			}

			else if (1 == option)
			{
				// application-default Graph..
				pG = create_example_lgraph();
				break;
			}
			else if (101 == option)
			{
				pG = nullptr;
				break;
			}
			else {
				fprintf(stderr, "\t Sorry, option is non-existence...\n");
				fprintf(stderr, "\t please input 0 for user defined, 1 for default,101 for exit program.\n");
			}
		}

		if (pG)
		{
			print_lgraph(*pG);
			free(pG);
			pG = nullptr;
		}


		return 0;
	}
}

namespace nsDSUDGraphCPPADList
{

	UDGraphADList::UDGraphADList()
	{
		char c1, c2;
		int v, e;
		int i, p1, p2;
		ENode *node1, *node2;

		// 输入"顶点数"和"边数"
		cout << "input vertex number: ";
		cin >> mVexNum;
		cout << "input edge number: ";
		cin >> mEdgNum;
		if (mVexNum < 1 || mEdgNum < 1 || (mEdgNum >(mVexNum * (mVexNum - 1))))
		{
			cout << "input error: invalid parameters!" << endl;
			return;
		}

		// 初始化"邻接表"的顶点
		for (i = 0; i<mVexNum; i++)
		{
			cout << "vertex(" << i << "): ";
			mVexs[i].data = readChar();
			mVexs[i].firstEdge = NULL;
		}

		// 初始化"邻接表"的边
		for (i = 0; i<mEdgNum; i++)
		{
			// 读取边的起始顶点和结束顶点
			cout << "edge(" << i << "): ";
			c1 = readChar();
			c2 = readChar();

			p1 = getPosition(c1);
			p2 = getPosition(c2);
			// 初始化node1
			node1 = new ENode();
			node1->_ENvertPos = p2;
			// 将node1链接到"p1所在链表的末尾"
			if (mVexs[p1].firstEdge == NULL)
				mVexs[p1].firstEdge = node1;
			else
				linkLast(mVexs[p1].firstEdge, node1);
			// 初始化node2
			node2 = new ENode();
			node2->_ENvertPos = p1;
			// 将node2链接到"p2所在链表的末尾"
			if (mVexs[p2].firstEdge == NULL)
				mVexs[p2].firstEdge = node2;
			else
				linkLast(mVexs[p2].firstEdge, node2);
		}
	}

	/*
	* 创建邻接表对应的图(用已提供的数据)
	*/
	UDGraphADList::UDGraphADList(char vexs[], int vlen, char edges[][2], int elen)
	{
		char c1, c2;
		int i, p1, p2;
		ENode *node1, *node2;

		// 初始化"顶点数"和"边数"
		mVexNum = vlen;
		mEdgNum = elen;
		// 初始化"邻接表"的顶点
		for (i = 0; i<mVexNum; i++)
		{
			mVexs[i].data = vexs[i];
			mVexs[i].firstEdge = NULL;
		}

		// 初始化"邻接表"的边
		for (i = 0; i<mEdgNum; i++)
		{
			// 读取边的起始顶点和结束顶点
			c1 = edges[i][0];
			c2 = edges[i][1];

			p1 = getPosition(c1);
			p2 = getPosition(c2);
			// 初始化node1
			node1 = new ENode();
			node1->_ENvertPos = p2;
			// 将node1链接到"p1所在链表的末尾"
			if (mVexs[p1].firstEdge == NULL)
				mVexs[p1].firstEdge = node1;
			else
				linkLast(mVexs[p1].firstEdge, node1);
			// 初始化node2
			node2 = new ENode();
			node2->_ENvertPos = p1;
			// 将node2链接到"p2所在链表的末尾"
			if (mVexs[p2].firstEdge == NULL)
				mVexs[p2].firstEdge = node2;
			else
				linkLast(mVexs[p2].firstEdge, node2);
		}
	}

	/*
	* 析构函数
	*/
	UDGraphADList::~UDGraphADList()
	{
	}

	/*
	* 将node节点链接到list的最后
	*/
	void UDGraphADList::linkLast(ENode *list, ENode *node)
	{
		ENode *p = list;

		while (p->_PENnextEdge)
			p = p->_PENnextEdge;
		p->_PENnextEdge = node;
	}

	/*
	* 返回ch的位置
	*/
	int UDGraphADList::getPosition(char ch)
	{
		int i;
		for (i = 0; i<mVexNum; i++)
			if (mVexs[i].data == ch)
				return i;
		return -1;
	}

	/*
	* 读取一个输入字符
	*/
	char UDGraphADList::readChar()
	{
		char ch;

		do {
			cin >> ch;
		} while (!((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z')));

		return ch;
	}

	/*
	* 打印邻接表图
	*/
	void UDGraphADList::print()
	{
		int i, j;
		ENode *node;

		cout << "List Graph:" << endl;
		for (i = 0; i < mVexNum; i++)
		{
			cout << i << "(" << mVexs[i].data << "): ";
			node = mVexs[i].firstEdge;
			while (node != NULL)
			{
				cout << node->_ENvertPos << "(" << mVexs[node->_ENvertPos].data << ") ";
				node = node->_PENnextEdge;
			}
			cout << endl;
		}
	}

	int main_DSUDGraphCPPADList()
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
		UDGraphADList* pG;


		fprintf(stderr, "\t input 0, to select self defined graph:\n");
		fprintf(stderr, "\t input 1, to use application default graph:\n");
		fprintf(stderr, "\t input 101, to exit program..\n");
		int option = -1;

		while (true)
		{
			scanf("%d", &option);

			if (0 == option)
			{
				// self-defined Graph..
				pG = new UDGraphADList();
				break;
			}

			else if (1 == option)
			{
				// application-default Graph..
				pG = new UDGraphADList(vexs, vlen, edges, elen);
				break;
			}
			else if (101 == option)
			{
				pG = nullptr;
				break;
			}
			else {
				fprintf(stderr, "\t Sorry, option is non-existence...\n");
				fprintf(stderr, "\t please input 0 for user defined, 1 for default,101 for exit program.\n");
			}
		}

		if (pG)
			pG->print();   // 打印图

		delete pG;
		pG = nullptr;


		return 0;
	}
}


/************************************************************************
  Reference http://www.sanfoundry.com/cpp-program-implement-adjacency-list/

  Class Name	
			UDGraphADListEXTA

  Description
			//TODO:


/************************************************************************/
namespace nsDSUDGraphCPPADListEXTA
{

		UDGraphADListEXTA::UDGraphADListEXTA(int V)
		{
			this->V = V;
			this->adList = new struct AdjList[V];
			for (int i = 0; i < this->V; ++i)
				adList[i].head = nullptr;
		}

		// Creating new Adjacency List Node.
		UDGraphADListEXTA::AdjListNode * UDGraphADListEXTA::newAdjListNode(int dest)
		{
			AdjListNode * newNode = new AdjListNode;
			newNode->dest = dest;
			newNode->next = nullptr;

			return newNode;
		}

		// Adding Edge to Graph.
		void UDGraphADListEXTA::addEdge(int src, int dest)
		{
			AdjListNode * newNode = newAdjListNode(dest);
			newNode->next = adList[src].head;
			adList[src].head = newNode;

			newNode = newAdjListNode(src);
			newNode->next = adList[dest].head;

			adList[dest].head = newNode;
		}


		// Print the Graph...
		void UDGraphADListEXTA::printGraph()
		{
			for (int i = 0; i < this->V; ++i)
			{
				AdjListNode * pCrawl = adList[i].head;
				fprintf(stderr, "\n Adjacency List of Vertex (%d) \n head", this->V);

				while (nullptr != pCrawl)
				{
					fprintf(stderr, "-> %d", pCrawl->dest);
					pCrawl = pCrawl->next;
				}

				fprintf(stderr, "\n");
			}
		}


	int main_UDGraphADListEXTA()
	{
		UDGraphADListEXTA gh(5);
		gh.addEdge(0, 1);
		gh.addEdge(0, 4);
		gh.addEdge(1, 2);
		gh.addEdge(1, 3);
		gh.addEdge(1, 4);
		gh.addEdge(2, 3);
		gh.addEdge(3, 4);
		gh.addEdge(0, 4);

		gh.printGraph();

		return 0;
	}
}
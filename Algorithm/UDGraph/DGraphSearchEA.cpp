/************************************************************************

  http://blog.csdn.net/ebowtang/article/details/44263635


/************************************************************************/
///  >> 11/22/17/2016 BY.gaohuancai QQ1293302539 <<
#include "DGraphSearchEA.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
namespace nsDGraphSearchEA
{

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	//���ض���vertexname��m_pVertexTable(���㼯)�е�λ�� ; 
	//������ڶ��㼯�оͷ���-1  ;
	template<class NameType, class DistType>
	int Graph<NameType, DistType>::GetVertexPosTable(const NameType vertexname)
	{
		for (int i = 0; i < m_numVertexs; i++)
		{
			// Searching Vertex-Position in Vertex-Set-of-Graph
			// -	by traversing the Vertex-Set-of-Graph

			if (vertexname == m_pVertexTable[i].m_vertexName)
				return i;

		}

		// while finding no matching-Vertex-Name
		return -1;
	}


	//��ӡͼ�еĸ������㼰�����ӵıߵ�Ȩ�� ; 
	template<class NameType, class DistType>
	void Graph<NameType, DistType>::PrintGraph()
	{
		Edge<DistType> *pmove = nullptr;

		for (int i = 0; i < m_numVertexs; i++)
		{
			// Traversing the Vertex-Set-of-Graph

			cout << m_pVertexTable[i].m_vertexName << "->";	// Vertex-Name
			pmove = m_pVertexTable[i].padjEdge;				// Vertex-Edge retrieved
			while (pmove)
			{
				// if (nullptr != pmove)
				cout << pmove->m_distWeight << "->"
					 << m_pVertexTable[pmove->m_nposTable].m_vertexName
					 << "->";
				pmove = pmove->m_pnext;
			}
			cout << "NULL" << endl;
		}
	}


	//����ڶ��㼯�е�λ��Ϊv�Ķ��������;  
	template<class NameType, class DistType>
	NameType Graph<NameType, DistType>::GetVertexValue(int v)
	{
		// boundary checking.
		if (v < 0 || v >= this->m_numVertexs)
		{cerr << "���ҵĶ���λ�ò�����������;��" << endl; exit(1); }

		// retrieving the Vertex by Vertex-position in Vertex-Table-of-Graph
		return m_pVertexTable[v].m_vertexName;
	}


	//���ض���v1��v2֮��ı�Ȩֵ;��  ;
	//���û��ֱ��������������һ����ֱ���������򷵻������;  
	template<class NameType, class DistType>
	DistType Graph<NameType, DistType>::GetWeight(int v1, int v2)
	{
		// boundary checking.
		if ((v1 >= 0 && v1 < m_numVertexs) && (v2 >= 0 && v2 < m_numVertexs))
		{
			if (v1 == v2)
				return 0;

			// one Vertex may link with several other-Vertex
			// a Vertex-Set Traversal goes here to searching the matching one.
			// [Optimize]
			Edge<DistType> *pmove = m_pVertexTable[v1].padjEdge;
			while (nullptr != pmove)
			{
				if (pmove->m_nposTable == v2)
					return pmove->m_distWeight;

				pmove = pmove->m_pnext;
			}
		}

		return m_Infinity;
	}


	//�������β��뵽����õĶ��㼯��;  
	template<class NameType, class DistType>
	bool Graph<NameType, DistType>::InsertVertex(const NameType vertexname)
	{
		if (IsGraphFull())
		{
			cerr << "ͼ�Ѿ����������ٲ��붥��..;\n";
			return false;
		}
		else
		{
			// Insert Vertex-Name && Increment Vertex-Total-Count
			m_pVertexTable[m_numVertexs].m_vertexName = vertexname;
			m_numVertexs++;
		}

		return true;
	}


	//�ڶ��㼯λ��Ϊv1��v2�Ķ���֮�����ȨֵΪweght�ıߣ���ر��������׼ȷ�ԣ�����.....�� ; 
	template<class NameType, class DistType>
	bool Graph<NameType, DistType>::InsertEdge(int v1, int v2, DistType weight)
	{
		// boundary checking.
		if ((v1 < 0 && v1 > m_numVertexs) && (v2 < 0 && v2 > m_numVertexs))
		{
			cerr << "�ߵ�λ�ò�����������...;\n";
			return false;
		}
		else
		{
			Edge<DistType> *pmove = m_pVertexTable[v1].padjEdge;

			// is it the first Edge ?
			if (nullptr == pmove)
			{
				// First Adjacency-Edge of Vertex-v1 Creation

				// Edge Creation with Ending-Vertex-v2 and Edge-weight
				m_pVertexTable[v1].padjEdge = new Edge<DistType>(v2, weight);

				m_nnumEdges++;

				return true;
			}
			else
			{
				while (nullptr != pmove->m_pnext)
					pmove = pmove->m_pnext;

				// appending new-Created-Edge to the the tail
				// of the Vertex-Table-of-Vertex-v1-in-Graph
				pmove->m_pnext = new Edge<DistType>(v2, weight);

				m_nnumEdges++;

				return true;
			}
		}
	}


	/************************************************************************
	  Dijkstra alo;
		https://en.wikipedia.org/wiki/Dijkstra's_algorithm
		http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
		http://blog.csdn.net/ebowtang/article/details/44262701
		http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/GraphAlgor/dijkstraAlgor.htm

		This implementation of Dijkstra may have some performance problem..
		but the algorithm is yes;
	/************************************************************************/
	template<class NameType, class DistType>
	void Graph<NameType, DistType>::Dijkstra(int VertexStart, DistType *shPath)
	{
		int num = GetNumVertexs();
		int *visited = new int[num];

		// Costs_initialization between Vertex_Pivot to one-of Vertex_Others.
		for (int i = 0; i < num; i++)
		{
			visited[i] = 0;
			shPath[i] = this->GetWeight(VertexStart, i);//����VertexPivot����ǰ�м�㣩���������ڶ���ı�Ȩֵ������������������ ; 
		}

		///[00]
		visited[VertexStart] = 1;// Vertex_Pivot initialized as the starting vertex;�������ʼ��Ϊ�����ʣ�������Ϊ�е�㿪ʼ�����·�� ; 


		for (int i = 1; i < num; i++)
		{
			DistType costMin = this->m_Infinity;
			int VertexPivot = 0;// used for the moving VertexPivot

			///[01] Finding the Cost_Minimum Vertex_min described as THE_closest Vertex_Node adjacent to VertexPivot;
			///[01] the loop for finding the Cost_Minimum among the Vertex_visited_before;
			for (int j = 0; j < num; j++)
			{
				/// does it have visited yet ?
				if (!visited[j])
				{
					/// is its more closer to the VertexPivot ?
					if (shPath[j] < costMin)
					{
						/// update the minimum cost between VertexPivot to its closest adjacent Vertex_node
						/// costMin is the cost between the Vertex_Starting to current VertexPivot.
						costMin = shPath[j];

						/// update the VertexPivot by the node which is the closest adjacent to VertexPivot
						VertexPivot = j;
					}
				}

			}// end for vertex_visited_before


			visited[VertexPivot] = 1;// marking as visited


			///[] Finding the Cost_Minimum between Vertex_u to the Vertex_node that unvisited before
			///[] the loop for Update Predecessor of All Vertex_nodes Adjacent to VertexPivot and the Cost_;
			for (int w = 0; w < num; w++)
			{
				///[] retrieve the Cost between VertexPivot_u to Vertex_node_w,which will be infinity if <w> isn't adjacent to <u>;
				DistType weight = this->GetWeight(VertexPivot, w);

				///[] does Vertex_node_w have visited yet ? and is Vertex_node_w adjacent to Vertex_node_u ?
				if (!visited[w] && weight != this->m_Infinity)
				{
					///[] Update the Cost between VertexSource to Vertex_node_w to the Relaxed Cost_value based on the Cost_Minimum and 'weight'
					if (shPath[VertexPivot] + weight < shPath[w])
						///[] Relax Vertex_node_w adjacent to VertexPivot_u
						shPath[w] = shPath[VertexPivot] + weight;

				}

			}// end for update
		}

		delete[] visited;
	}


	template<class NameType, class DistType>
	int Graph<NameType, DistType>::GetNext(int v1, int v2)
	{
		// boundary checking.
		if (-1 != v1)
		{
			// retrieve the Vertex-Table-of-Vertex-v1
			Edge<DistType> *pmove = this->m_pVertexTable[v1].padjEdge;

			// Searching the matching Vertex-v2 by Traversing the Vertex-Table-of-Vertex-v1
			while (nullptr != pmove->m_pnext)
			{
				// is (*pmove) the Edge between Vertex-v1 and Vertex-v2 ?
				if (pmove->m_nposTable == v2)
					return pmove->m_pnext->m_nposTable;

				pmove = pmove->m_pnext;
			}
		}

		return -1;
	}


	//-----------------------------------depth-first-searching--------------------------------------------//

	template<class NameType, class DistType>
	void Graph<NameType, DistType>::DFS(int v, int *visited)
	{
		// Vertex-name && marking
		visited[v] = 1;
		cout << "->" << this->GetVertexName(v);

		// 
		int firstVertex = this->GetFirst(v); 
		while (-1 != firstVertex)
		{
			// is the Vertex-firstVertex visited before ?
			if (!visited[firstVertex])
			{
				// [Depth Searching Starting]


				// Edge-Weight between Vertex-v and Vertex-firstVertex.
				cout << "->" << this->GetWeight(v, firstVertex);

				// Searching Vertex-firstVertex of Adjacent-Vertex of Vertex-v recursively
				DFS(firstVertex, visited);
			}

			// [Breadth Searching Starting]

			// Searching Adjacency-Vertex of Vertex-firstVertex.
			firstVertex = this->GetNext(v, firstVertex);
		}
	}

	template<class NameType, class DistType>
	void Graph<NameType, DistType>::DFS()
	{
		// storage allocation and initialization
		int *visited = new int[this->m_numVertexs];
		for (int i = 0; i < this->m_numVertexs; i++)
			visited[i] = 0;

		cout << "head";

		// depth-first-searching Starting Here by Vertex-0.
		DFS(0, visited);

		cout << "--->end";
	}


	//-----------------------------------breadth-first-searching--------------------------------------------//


	template<class NameType, class DistType>
	void Graph<NameType, DistType>::BFS()
	{
		// storage allocation and initialization
		int *visited = new int[this->m_numVertexs];
		for (int i = 0; i < this->m_numVertexs; i++)
			visited[i] = 0;

		cout << "head";

		// breadth-first-searching Starting Here by Vertex-0
		BFS(0, visited);

		cout << "--->end";
	}

	template<class NameType, class DistType>
	void Graph<NameType, DistType>::BFS(int v, int *visited)
	{
		// Vertex-name
		cout << "->" << this->GetVertexName(v);
		visited[v] = 1;

		queue<int> que;
		que.push(v);// Enqueue Vertex_V
		while (false != que.empty())
		{
			//@brief [0th] retrieve Vertex_V and Delete it from std::queue
			v = que.front();
			que.pop();

			//@brief [1st] retrieve the First_Grade_Adjacency_Vertex of Vertex_V
			int firstvertex = GetFirst(v);

			//@brief Traverse All the First_Grade_Adjacency_Vertex of Vertex_V
			//@brief && Enqueue the  First_Grade_Adjacency_Vertex of Vertex_V
			while (-1 != firstvertex)
			{
				//@brief [2nd] does the First_Grade_Adjacency_Vertex exist ?
				if (!visited[firstvertex])
				{
					// Vertex-weight
					cout << "->" 
						 << this->GetWeight(v, firstvertex);

					/// Enqueue Vertex-firstVertex and Marking
					que.push(firstvertex);
					visited[firstvertex] = 1;

					// Vertex-name
					cout << "->"
						 << this->GetVertexName(firstvertex);
				}

				// shift to another First_Grade_Adjacency_Vertex of Vertex_V
				firstvertex = GetNext(v, firstvertex);
			}
		}
	}


	//-------------------------------------------------------------------------------------------//

	template<class NameType, class DistType>
	NameType Graph<NameType, DistType>::GetVertexName(int v)
	{
		// boundary checking..
		if (v < 0 || v >= this->m_numVertexs)
		{
			cerr << "���ҵĶ���λ�ò�����������..;\n";
			exit(1);
		}

		return m_pVertexTable[v].m_vertexName;

	}

	template<class NameType, class DistType>
	int Graph<NameType, DistType>::GetFirst(int v)
	{
		if (v < 0 || v >= this->m_numVertexs)
			return -1;

		Edge<DistType> *ptemp = this->m_pVertexTable[v].padjEdge;

		return m_pVertexTable[v].padjEdge ? m_pVertexTable[v].padjEdge->m_nposTable : -1;
	}


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	int main_DGraphSearchEA()
	{
		Graph<char *, int> graph(7);
		char *vertex[7] = { "���ش�;��", "�����;��", "������;��", "������;��", "������;��", "���廪;��", "������;��" };//���㼯;  
		for (int i = 0; i < 7; i++)
			graph.InsertVertex(vertex[i]);


		cout << "<0> Initialization of Graph (Adjacency-List-Storage):"
			 << " ======================================\n";

		graph.PrintGraph();
		cout << "Vertex-Counts in Graph: " << graph.GetNumVertexs() << "\n\n";


		int edge[][3] = 
		{
			  { 0, 1, 43  }/*�ش����ľ���;*/
			, { 0, 2, 12  } /*{1, 2, 38}*/ /*{2, 3 ,1325}*/ /*{3, 6, 55}*/
			, { 4, 5, 34  } /*{4, 6, 248}*/
			, { 0, 3, 400 }
			, { 2, 6, 314 }
			, { 2, 4, 37  }
		};    //������� ;  
		int len = sizeof(edge) / sizeof(edge[0]);
		for (int i = 0; i < len; i++)
		{
			graph.InsertEdge(edge[i][0], edge[i][1], edge[i][2]);
			graph.InsertEdge(edge[i][1], edge[i][0], edge[i][2]);
		}

		cout << "<1> ��ӱߺ��ͼ(����ͼ);��==================================\n";
		graph.PrintGraph();
		cout << "ͼ�бߵ���Ŀ(ʵ��������ʾ��������������Ϊ��˫���);��"
			 << graph.GetNumEdges() 
			 << endl<< endl;

		cout << "<2> Dijkstra�����·��Ϊ;��==========================\n";


		int shortestPath[7];//�洢Dijkstra�㷨���·��ֵ  
		graph.Dijkstra(0, shortestPath);
		for (int i = 0; i < 7; i++)
		{
			cout << graph.GetVertexValue(0) 
				 << "--->" 
				 << graph.GetVertexValue(i)
				 << ":   "
				 << shortestPath[i]
				 << endl;
		}
		cout << endl;

		cout << "<3> Graph (Adjacency-List) Traversal��==========================\n";
		cout << "<3-0> Depth-First-Traversal..\n";
		graph.DFS();
		cout << endl << endl;
		cout << "<3-1> Breadth-First-Traversal..\n";
		graph.BFS();
		cout << endl << endl;

		system("color 0A");


		return 0;
	}
}

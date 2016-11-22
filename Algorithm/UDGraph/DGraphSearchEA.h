/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/22/17/2016 BY.gaohuancai QQ1293302539 <<
#pragma once


namespace nsDGraphSearchEA
{
	using namespace std;


	template<class DistType>	// Edge 权重数据的类型;
	class Edge					// Edge 定义;
	{
	public:
		Edge(int dest, DistType weight)
		{
			m_nposTable = dest;
			m_distWeight = weight;
			m_pnext = nullptr;
		}
		~Edge()
		{
		}

	public:
		//由于Edge是Vertex的一个属性; then
		// m_nposTable 标识与该 Edge 相连的 Vertex-position in Vertex-Set-of-Graph;
		// m_pnext 标识邻接点对应的Edge (即 m_nposTable 对应的 Edge);
		int m_nposTable;		// 该边的目的顶点在顶点集中的位置 ; 
		DistType m_distWeight;	// Edge 权重数值;
		Edge<DistType> *m_pnext;// next Edge（注意不是下一个顶点，因为m_nposTable已经知道了这个顶点的位置）;  
	};

								//声明;  
								//@param Type-Parameter/NameType   /顶点集名字类型;
								//@param Type-Parameter/DistType   /距离/权重数据类型;
	template<class NameType, class DistType>
	class Graph;


											//@param Type-Parameter/NameType   /顶点集名字类型;
											//@param Type-Parameter/DistType   /距离/权重数据类型;
	template<class NameType, class DistType>
	class Vertex							//顶点的定义;  
	{
	public:
		Vertex()
		{
			padjEdge = nullptr;
			m_vertexName = 0;
		}
		~Vertex()
		{
			Edge<DistType> *pmove = padjEdge;
			while (pmove)
			{
				padjEdge = pmove->m_pnext;
				delete pmove;
				pmove = padjEdge;
			}
		}

	private:
		friend class Graph<NameType, DistType>;	//@brief class Graph as a friend class of Vertex
		NameType		m_vertexName;			//@brief Data-Contents in this-Vertex
		Edge<DistType>	*padjEdge;				//@brief THIS-Vertex adjacency Edge ; 

	};


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
								// Value-Type of Vertex-Set	/顶点集名字类型;
								// Value-Type of Weight		/距离的数据类型;
	template<class NameType, class DistType> 
	class Graph
	{
	public:
		Graph(int size = m_nDefaultSize)	//图顶点集的规模;
		{
			m_pVertexTable = new Vertex<NameType, DistType>[size];  //为顶点集分配内存 ; 
			if (m_pVertexTable == nullptr)
			{
				exit(1);
			}
			m_numVertexs = 0;
			m_nmaxSize = size;
			m_nnumEdges = 0;
		}

		~Graph()
		{
			Edge<DistType> *pmove;
			for (int i = 0; i < this->m_numVertexs; i++)
			{
				pmove = this->m_pVertexTable[i].padjEdge;
				if (pmove){
					this->m_pVertexTable[i].padjEdge = pmove->m_pnext;
					delete pmove;
					pmove = this->m_pVertexTable[i].padjEdge;
				}
			}
			delete[] m_pVertexTable;
		}


		int		GetNumEdges(){return m_nnumEdges / 2;}
		int		GetNumVertexs(){return m_numVertexs;}

		bool	IsGraphFull() const{return m_nmaxSize == m_numVertexs;}

		// insert The-Edge between Vertex-v1 and Vertex-v2
		bool InsertEdge(int beg_Vertex_v0, int end_Vertex_v1, DistType Edge_weight = m_Infinity);

		// insert The-Vertex Vertex-vertex
		bool InsertVertex(const NameType vertex);

		// print out graph
		void PrintGraph();

		// the nearest distance between Vertex-v (including v) to Vertex-another
		void Dijkstra(int v, DistType *shotestpath);

		//@brief  retrieve the Weight-Value between Vertex-v1 and Vertex-v2
		DistType GetWeight(int v1, int v2);

		// retrieve the Vertex-name by the Vertex-v position
		NameType GetVertexValue(int v);

		// retrieve the Vertex-position by the Vertex-name
		int GetVertexPosTable(const NameType vertex);


		//@param  int v  [#]Vertex-v is starting vertex with which the depth-first-searching begin.
		//@param  int * visited  [#]storage for Vertex-visited-marking
		void DFS(int v, int *visited);
		void DFS();

		//@param  int v  [#]Vertex-v is starting vertex with which the breadth-first-searching begin.
		//@param  int * visited  [#]storage for Vertex-visited-marking
		void BFS(int v, int *visited);
		void BFS();

		//@brief retrieve the Vertex-name of Vertex-v
		NameType GetVertexName(int v);

		//@brief retrieve the First-Adjacency-Vertex of Vertex-v if there exists one
		//@brief otherwise -1 returned.
		int GetFirst(int v);

		//@brief Retrieve the First-Adjacent-Vertex of Vertex-v2 backward relative to Vertex-v1;
		int GetNext(int v1, int v2);

	private:
		Vertex<NameType, DistType> *m_pVertexTable;	//@brief Vertex Set of Graph
		int m_numVertexs;							//图中当前的顶点数量;  
		int m_nmaxSize;								//图允许的最大顶点数;  
		static const int m_nDefaultSize = 10;		//默认的最大顶点集数目 ; 
		static const DistType m_Infinity = 65536;	//边的默认权值（可以看成是无穷大）;  
		int m_nnumEdges;							//图中边的数目 ; 

	};

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	int main_DGraphSearchEA();
}

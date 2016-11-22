/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/22/17/2016 BY.gaohuancai QQ1293302539 <<
#pragma once


namespace nsDGraphSearchEA
{
	using namespace std;


	template<class DistType>	// Edge Ȩ�����ݵ�����;
	class Edge					// Edge ����;
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
		//����Edge��Vertex��һ������; then
		// m_nposTable ��ʶ��� Edge ������ Vertex-position in Vertex-Set-of-Graph;
		// m_pnext ��ʶ�ڽӵ��Ӧ��Edge (�� m_nposTable ��Ӧ�� Edge);
		int m_nposTable;		// �ñߵ�Ŀ�Ķ����ڶ��㼯�е�λ�� ; 
		DistType m_distWeight;	// Edge Ȩ����ֵ;
		Edge<DistType> *m_pnext;// next Edge��ע�ⲻ����һ�����㣬��Ϊm_nposTable�Ѿ�֪������������λ�ã�;  
	};

								//����;  
								//@param Type-Parameter/NameType   /���㼯��������;
								//@param Type-Parameter/DistType   /����/Ȩ����������;
	template<class NameType, class DistType>
	class Graph;


											//@param Type-Parameter/NameType   /���㼯��������;
											//@param Type-Parameter/DistType   /����/Ȩ����������;
	template<class NameType, class DistType>
	class Vertex							//����Ķ���;  
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
								// Value-Type of Vertex-Set	/���㼯��������;
								// Value-Type of Weight		/�������������;
	template<class NameType, class DistType> 
	class Graph
	{
	public:
		Graph(int size = m_nDefaultSize)	//ͼ���㼯�Ĺ�ģ;
		{
			m_pVertexTable = new Vertex<NameType, DistType>[size];  //Ϊ���㼯�����ڴ� ; 
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
		int m_numVertexs;							//ͼ�е�ǰ�Ķ�������;  
		int m_nmaxSize;								//ͼ�������󶥵���;  
		static const int m_nDefaultSize = 10;		//Ĭ�ϵ���󶥵㼯��Ŀ ; 
		static const DistType m_Infinity = 65536;	//�ߵ�Ĭ��Ȩֵ�����Կ����������;  
		int m_nnumEdges;							//ͼ�бߵ���Ŀ ; 

	};

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	int main_DGraphSearchEA();
}

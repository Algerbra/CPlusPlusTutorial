///************************************************************************/
///*                                                                      */
///************************************************************************/
/////  >> 11/21/17/2016 BY.gaohuancai QQ1293302539 <<
//#include "UGraphTemplate.h"
//
//namespace nsUGraphTemplate
//{
//
//
//	template<typename T, typename E>
//	GraphAdjMatrix<T, E>::GraphAdjMatrix(const E & maxweight, int size)
//	{
//		m_maxVerticesNum = size;
//		m_numVertices = 0;
//		m_numEdge = 0;
//		m_maxWeight = maxweight;
//
//		//storage allocation
//		m_verticesList = new T[m_maxVerticesNum];
//		m_edge = new E *[m_maxVerticesNum];
//
//		for (int i = 0; i < m_maxVerticesNum; ++i)
//			m_edge[i] = new E[m_maxVerticesNum];
//
//		//initialization of EDGE.
//		for (int row = 0; row < m_maxVerticesNum; ++row)
//		{
//			for (int col = 0; col < m_maxVerticesNum; ++col)
//			{
//				m_edge[row][col] = ((row == col) ? 0 : m_maxWeight);
//			}
//		}
//
//	}
//
//
//	template<typename T, typename E>
//	GraphAdjMatrix<T, E>::~GraphAdjMatrix()
//	{
//		delete[] m_verticesList;
//
//		for (int i = 0; i < m_maxVerticesNum; ++i)
//			delete[] m_edge[i];
//
//		delete[] m_edge;
//	}
//
//
//	// retrieve the index of the Vertex-Position
//	// -1 returned if failed..
//	template<typename T, typename E>
//	int GraphAdjMatrix<T, E>::GetVerticesPos(
//		  const T & vertex)
//	{
//		for (int i = 0; i < m_numVertices; ++i)
//		{
//			if (vertex == m_verticesList[i])
//				return i;
//		}
//
//		return s_NULLidx;
//	}
//
//	//@brief  retrieve the Vertex-Value by Vertex-Index.
//	//@param   int vertex_idx  / index of the vertex
//	template<typename T, typename E>
//	T GraphAdjMatrix::GetVertex(
//		  int vertex_idx)
//	{
//		if ((0 <= vertex_idx) && (vertex_idx <= (m_numVertices - 1)))
//			//Vertex-Value stored in Corresponding List returned.
//			return m_verticesList[vertex_idx];
//
//		else
//			///Vertex-Index is out of range. ???
//			return;
//	}
//
//
//
//	template<typename T, typename E>
//	E GraphAdjMatrix::GetWeight(
//		  const T & begvtx
//		, const T & endvtx)
//	{
//		int begidx = GetVerticesPos(begvtx);
//		int endidx = GetVerticesPos(endvtx);
//
//		if ((s_NULLidx != begidx) && (s_NULLidx !+ endidx))
//			//These begidx and endidx are valid.
//			return m_edge[begidx][endidx];
//
//		else
//			//otherwise nothing returned.
//			return;
//	}
//
//
//
//	template<typename T, typename E>
//	T GraphAdjMatrix::GetFirstNeighbor(
//		  const T & vertex)
//	{
//		int idx = GetVerticesPos(vertex);
//
//		//is it a valid Vertex-Index ?
//		if (s_NULLidx != idx)
//		{
//			//Vertex of Graph traversal
//			for (int col = 0; col < m_maxVerticesNum; ++col)
//			{
//				//if finding the adjacency Vertex, then returned.
//				if ((0 < m_edge[idx][col]) && (m_edge[idx][col] < m_maxWeight))
//					return m_verticesList[col];
//			}
//		}
//
//		//otherwise, THIS Vertex-non-existence OR without adjacency-vertex.
//		return;
//	}
//
//	
//	template<typename T, typename E>
//	T GraphAdjMatrix::GetNextNeighbor(
//		  const T & vertex
//		, const T & adj_vertex)
//	{
//		int idx = GetVerticesPos(vertex);
//		int adj_idx = GetVerticesPos(adj_vertex);
//
//		if ((s_NULLidx != idx) && (s_NULLidx != adj_idx))
//		{
//			for (int col = adj_idx + 1; col < m_maxVerticesNum; ++col)
//			{
//				if ((0 < m_edge[idx][adj_idx]) && (m_edge[idx][adj_idx] < m_maxWeight))
//					return m_verticesList[col];
//			}
//		}
//
//		return;
//	}
//
//
//	template<typename T, typename E>
//	bool GraphAdjMatrix::InsertVertex(
//		  const T & vertex)
//	{
//		if (m_maxVerticesNum == m_numVertices)
//			return false;
//
//		// append the 'vertex' to the tail of Adjacency-List
//		m_verticesList[m_numVertices++] = vertex;
//
//		return true;
//	}
//
//
//	template<typename T, typename E>
//	bool GraphAdjMatrix::InsertEdge(const T & begvtx, const T & endvtx, const E & cost)
//	{
//		int begidx = GetVerticesPos(begvtx);
//		int endidx = GetVerticesPos(endvtx);
//
//		if ((s_NULLidx != begidx) && (s_NULLidx != endidx) && (m_edge[begidx][endidx] == m_maxWeight))
//		{
//			m_edge[begidx][endidx] = cost;
//			++m_numEdge;
//
//			return true;
//		}
//
//		//unsatisfied.
//		return false;
//	}
//
//
//	template<typename T, typename E>
//	bool GraphAdjMatrix::RemoveVertex(const T & vertex)
//	{
//		int idx = GetVerticesPos(vertex);
//		if (s_NULLidx != idx)
//			return false;
//
//		if (1 == m_numVertices)
//			return false;
//
//		m_verticesList[idx] = m_verticesList[m_numVertices - 1]; 
//	}
//
//
//	template<typename T, typename E>
//	GraphAdjMatrix::RemoveEdge(const T & begvtx, const T & endvtx)
//	{
//
//	}
//
//
//	//overload standard input..
//	template<typename T, typename E>
//	istream & operator >> (istream & input, GraphAdjMatrix<T, E> & G)
//	{
//
//	}
//
//	//overload standard output..
//	template<typename T, typename E>
//	ostream & operator << (ostream & output, GraphAdjMatrix<T, E> & G)
//	{
//
//	}
//
//	//overload standard file input...
//	template<typename T, typename E>
//	ifstream & operator >> (ifstream & finput, GraphAdjMatrix<T, E> & G)
//	{
//
//	}
//
//	//overload standard file output...
//	ofstream & operator << (ofstream & foutput, GraphAdjMatrix<T, E> & G)
//	{
//
//	}
//
//	/************************************************************************/
//	/*                                                                      */
//	/************************************************************************/
//	int main_nsUGraphTemplate()
//	{
//
//	}
//}
//

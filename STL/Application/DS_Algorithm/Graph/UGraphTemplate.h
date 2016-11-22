///************************************************************************/
///*                                                                      */
///************************************************************************/
/////  >> 11/21/17/2016 BY.gaohuancai QQ1293302539 <<
//#pragma once
//
//#include <iostream>
//#include <fstream>
//
//namespace nsUGraphTemplate
//{
//
//	using namespace std;
//	const int DefaultVerticesNum = 30;
//
//
//	template<typename T, typename E>
//	class GraphAdjMatrix
//	{
//		// overload standard stream input  >>
//		template<typename T, typename E> 
//		friend istream & operator >> (istream & input, GraphAdjMatrix<T, E> & G);
//
//		// overload standard stream output <<
//		template<typename T, typename E> 
//		friend ostream & operator << (ostream & output, GraphAdjMatrix<T, E> & G);
//
//		// overload standard file input 
//		template<typename T, typename E> 
//		friend ifstream & operator >> (ifstream & finput, GraphAdjMatrix<T, E> & G);
//
//		// overload standard file output
//		template<typename T, typename E> 
//		friend ostream & operator << (ofstream & foutput, GraphAdjMatrix<T, E> & G);
//
//	public:
//		GraphAdjMatrix(const E &maxweight, int size = DefaultVerticesNum);
//		~GraphAdjMatrix();
//
//		T GetVertex(int vertex_idx);//retrieve Vertex-Value by Vertex-Index
//		E GetWeight(const T & begvtx, const T & endvtx);//retrieve Weight-Value of Edge between begvtx and endvtx;
//		T GetFirstNeighbor(const T & vertex);// retrieve the first Adjacent vertex of THE 'vertex';
//		T GetNextNeighbor(const T & vertex, const T & adj_vertex);// retrieve the first Adj_vertex of adj_vertex Adjacent to Vertex;
//
//
//		bool	InsertVertex(const T & vertex);
//		bool	InsertEdge(const T & begvtx, const T & endvtx, const E & cost);
//		bool	RemoveVertex(const T & vertex);// delete a vertex;
//		bool	RemoveEdge(const T & begvtx, const T & endvtx);// delete a EDGE between begvtx and endvtx;
//
//	protected:
//		int		GetVerticesPos(const T & vertex);// 
//	protected:
//		int		m_maxVerticesNum;	// max Counts of a Graph.
//		int		m_numEdge;			// Present Edge Counts of THIS-Graph
//		int		m_numVertices;		// Present Vertex Counts of THIS-Graph
//		
//		static const int s_NULLidx = -1;// marker for invalid index of location
//
//		T		* m_verticesList;	// vertex storage list
//		E		** m_edge;			// 2-dimension matrix for edge storage.
//		E		m_maxWeight;		// ??
//
//	};
//
//
//	/************************************************************************/
//	/*                                                                      */
//	/************************************************************************/
//	int main_nsUGraphTemplate();
//}
//

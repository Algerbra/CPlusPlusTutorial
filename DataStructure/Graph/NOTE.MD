//----------------------------------------------------------------------//
//																		//
//----------------------------------------------------------------------//
数据结构之图
	//(存储结构,遍历)
	//http://blog.chinaunix.net/uid-21813514-id-3866951.html


	(01) adjacency matrix
		图的邻接矩阵存储方式是用两个数组来表示图:图的顶点信息, 图的边或弧信息.

		设图 G 有 n 个顶点,则邻接矩阵是一个 (n*n) 的方阵..
				
				arc[i][j]
							=	1,若(Vi,Vj)属于E
							=	0,若(Vi,Vj)不属于E

		** 任意两点是否有边无边
		** 任意顶点的度

//-----------------------------------------------------------------------//
  http://www.geeksforgeeks.org/graph-and-its-representations/

  Adjacency Matrix:
  Pros:
	Representation is easier to implement and follow.
	Removing an edge takes O(1) time. 
	Queries like whether there is an edge from vertex ‘u’ to vertex ‘v’
	-	are efficient and can be done O(1).

  Cons: 
	Consumes more space O(V^2). 
	Even if the graph is sparse(contains less number of edges), 
	-	it consumes the same space. Adding a vertex is O(V^2) time.

//-----------------------------------------------------------------------//

Data-Structure "Graph"

	/// Basic Conception
		// vertices		//a nonempty set V
		// edges		//a nonempty set E of two-element subsets of V
		// Graph = (V,E)

	/// Direction Graph
	/// Undirection Graph

	/// Representation:
		// Adjacency Matrix;	c/c++
		// Adjacency List;		c/c++

	/// Operation:

	/// Algorithm:

//-----------------------------------------------------------------------//
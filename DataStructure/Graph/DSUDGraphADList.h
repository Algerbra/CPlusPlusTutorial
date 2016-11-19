/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/18/23/2016 BY.gaohuancai QQ1293302539 <<
#pragma once

/************************************************************************
  Description
			//TODO:


/************************************************************************/
namespace nsDSUDGraphCADList
{
	int main_DSUDGraphCADList();
}


/************************************************************************
  Description
			//TODO:


/************************************************************************/
namespace nsDSUDGraphCPPADList
{
	using namespace  std;
	class UDGraphADList
	{
	public:
		UDGraphADList();
		UDGraphADList(char vexs[], int vlen, char edges[][2], int elen);
		~UDGraphADList();

		void print();

	private:
		struct ENode
		{
			int _ENvertPos;
			ENode * _PENnextEdge;
		};

		struct VNode
		{
			char data;
			ENode * firstEdge;
		};


	private:
		char readChar();
		int  getPosition(char ch);

		void linkLast(ENode * list, ENode* node);

	private:
		int mVexNum;
		int mEdgNum;
		VNode mVexs[MAX];

	};

	int main_DSUDGraphCPPADList();
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
	class UDGraphADListEXTA
	{
	public:
		struct AdjListNode
		{
			int   dest;
			struct AdjListNode * next;
		};

		struct AdjList
		{
			struct AdjListNode * head;
		};

	public:
		UDGraphADListEXTA(int V);

		AdjListNode * newAdjListNode(int dest);

		void addEdge(int src, int dest);

		void printGraph();

	private:
		int V;	// Vertex 
		struct AdjList * adList;	//Adjacency List of THIS Vertex.

	};


	int main_UDGraphADListEXTA();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

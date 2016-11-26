/************************************************************************
  References
  Tutorial
	https://en.wikipedia.org/wiki/A*_search_algorithm


  Coding
	http://www.bogotobogo.com/Algorithms/path_finding_algorithm.php
	http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/

/************************************************************************/
///  >> 11/26/11/2016 BY.gaohuancai QQ1293302539 <<
#include "algoAStar.h"


#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <string>
#include <queue>

namespace nsalgoAStar
{

	using namespace std;

	const int kHXDimMap = 8;// horizontal size of the squares
	const int kVYDimMap = 6;// vertical size size of the squares
	const int kNODir = 4;	// number of possible directions to go at any position

	// if NDIR = 4
	const int kHXDir[kNODir] = { 1, 0, -1, 0 };
	const int kVYDir[kNODir] = { 0, 1, 0, -1 };

	// if NDIR = 8
	//const int iDir[NDIR] = {1, 1, 0, -1, -1, -1, 0, 1};
	//const int jDir[NDIR] = {0, 1, 1, 1, 0, -1, -1, -1};

	int mapSquares[kHXDimMap][kVYDimMap];

	// list of closed (check-out) nodes
	int ClosedSet[kHXDimMap][kVYDimMap];
	// list of opened (not-yet-checked-out) nodes
	int OpenedSet[kHXDimMap][kVYDimMap];

	
	/************************************************************************

				          [+0,+1]
				             |  
				             |
			   --[-1,+0]<----|---> [+1,+0]----------
				             |
							 |
						  [+0,-1]

		iInd =   0,    1,   2,      3
		iDir = Right, Top, Left,  Bottom

		map of directions (0: East, 1: North, 2: West, 3: South) 
		the dirMap[x][y] value represent the a pointer which points to the Parent Node of [x][y]

		if [x][y] = 0, [x][y] <ParentNode>
		
		               <ParentNode>
		if [x][y] = 1, [x][y]

		if [x][y] = 2, <ParentNode> [x][y]

		if [x][y] = 3, [x][y]
		               <ParentNode>
	/************************************************************************/
	int dirMap[kHXDimMap][kVYDimMap];

	struct Location
	{
		int _rowLoc;
		int _colLoc;

		Location()
		{_rowLoc = _colLoc = 0; };

		Location(int xpos, int ypos)
			: _rowLoc(xpos)
			, _colLoc(ypos)
		{ };
	};

	class Node
	{
	private:
		// current position
		int _rCurNodePos;
		int _cCurNodePos;

		// total distance already traveled to reach the node
		// FValue = GValue + remaining distance estimate
		int _GValueCurNode;
		int _FValueCurNode;  // smaller FValue gets priority

	public:
		Node(const Location &a_Location, int a_iGVal, int a_iFVal)
		{
			_rCurNodePos = a_Location._rowLoc;
			_cCurNodePos = a_Location._colLoc;

			_GValueCurNode = a_iGVal;
			_FValueCurNode = a_iFVal;
		}

		Location getLocation() const { return Location(_rCurNodePos, _cCurNodePos); }
		int getGValue() const { return _GValueCurNode; }
		int getFValue() const { return _FValueCurNode; }

		void calculateFValue(const Location& locDest)
		{
			_FValueCurNode = _GValueCurNode + getHValue(locDest) * 10;
		}


		void updateGValue(const int & i) // i: direction
		{
			_GValueCurNode += (kNODir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
		}

		// Estimation function for the remaining distance to the goal.
		const int & getHValue(const Location& locDest) const
		{
			static int rd, cd, d;
			rd = locDest._rowLoc - _rCurNodePos;
			cd = locDest._colLoc - _cCurNodePos;

			// Euclidean Distance
			// d = static_cast<int>(sqrt((double)(rd*rd+cd*cd)));

			// Manhattan distance
			d = abs(rd) + abs(cd);

			// Chebyshev distance
			//d = max(abs(rd), abs(cd));

			return(d);
		}

		// Determine FValue (in the priority queue)
		friend bool operator<(const Node & a, const Node & b)
		{
			return a.getFValue() > b.getFValue();
		}
	};

	// A-star algorithm.
	// The path returned is a string of direction digits.
	string pathFind(const Location &StartNode,
		const Location &EndNode)

	{
		// list of open (not-yet-checked-out) nodes
		static priority_queue<Node> pqOpen[2];

		// q index
		static int pqi;

		static Node* pNode_CurBest;
		static Node* pNode2;
		static int iInd, jInd;
		static int rowNeighbor, colNeighbor;
		static int row, col;
		static char c;
		pqi = 0;

		// reset the Node lists (0 = ".")
		for (jInd = 0; jInd < kVYDimMap; jInd++) {
			for (iInd = 0; iInd < kHXDimMap; iInd++) {
				ClosedSet[iInd][jInd] = 0;
				OpenedSet[iInd][jInd] = 0;
			}
		}

		// create the start node and push into list of open nodes
		pNode_CurBest = new Node(StartNode, 0, 0);
		pNode_CurBest->calculateFValue(EndNode);
		pqOpen[pqi].push(*pNode_CurBest);

		// A* search
		while (!pqOpen[pqi].empty())
		{
			/// ///////////////////////////////////////////////////////////////////////
			/// Pull Out the Best Node with the-Lowest-FValue from the Open-List
			/// q[pqi] is the "OpenList" priority-queue
			pNode_CurBest = new Node(
				  pqOpen[pqi].top().getLocation()
				, pqOpen[pqi].top().getGValue()
				, pqOpen[pqi].top().getFValue() );


			row = (pNode_CurBest->getLocation())._rowLoc;
			col = (pNode_CurBest->getLocation())._colLoc;
			cout << "row, col=" << row << "," << col << endl;


			/// ///////////////////////////////////////////////////////////////////////
			/// move the node with the-lowest-FValue from "Open List" to "Closed List"

			
			pqOpen[pqi].pop();			// remove the node from the "Open List" priority-queue; 
			OpenedSet[row][col] = 0;	// remove the node from the "Opened List Set";
			ClosedSet[row][col] = 1;	// adding the node into the "Closed List Set";


			/// ///////////////////////////////////////////////////////////////////////
			/// If the Pulled-Best-Node Is the Goal, then Done;

			// is this pNode_CurBest Node Our Goal ? Stop searching if reached;
			if (row == EndNode._rowLoc && col == EndNode._colLoc)
			{
				// drawing direction map
				cout << endl;
				for (jInd = kVYDimMap - 1; jInd >= 0; jInd--) {
					for (iInd = 0; iInd < kHXDimMap; iInd++) {
						cout << dirMap[iInd][jInd] << " -> ";
					}
					cout << endl;
				}
				cout << endl;

				// generate the path from finish to start from dirMap
				string path = "";
				while (!(row == StartNode._rowLoc && col == StartNode._colLoc))
				{
					jInd = dirMap[row][col];
					c = '0' + (jInd + kNODir / 2) % kNODir;
					path = c + path;
					row += kHXDir[jInd];
					col += kVYDir[jInd];
				}

				// garbage collection
				delete pNode_CurBest;

				// empty the leftover nodes
				while (!pqOpen[pqi].empty())
					pqOpen[pqi].pop();
				return path;
			}


			/// ///////////////////////////////////////////////////////////////////////
			/// direction move
			/// iInd =   0,    1,   2,      3
			/// iDir = Right, Top, Left,  Bottom

			// generate moves in all possible directions
			for (iInd = 0; iInd < kNODir; iInd++)
			{
				rowNeighbor = row + kHXDir[iInd];
				colNeighbor = col + kVYDir[iInd];

				/// is it a legal NeighborVertex and out of CLOSED-LIST Set?
				if (!(rowNeighbor < 0 || rowNeighbor > kHXDimMap - 1 || colNeighbor < 0 || colNeighbor > kVYDimMap - 1 ||
					mapSquares[rowNeighbor][colNeighbor] == 1 || ClosedSet[rowNeighbor][colNeighbor] == 1))
				{

					// generate a child node as the New Neighbor;
					pNode2 = new Node(Location(rowNeighbor, colNeighbor), pNode_CurBest->getGValue(), pNode_CurBest->getFValue());
					pNode2->updateGValue(iInd);			// GValue update
					pNode2->calculateFValue(EndNode);	// FValue update

					/// if NOT IN "Open List Set";
					if (OpenedSet[rowNeighbor][colNeighbor] == 0)
					{
						OpenedSet[rowNeighbor][colNeighbor] = pNode2->getFValue();	// the "Open List Set";
						pqOpen[pqi].push(*pNode2);									// the priority-queue;
						dirMap[rowNeighbor][colNeighbor] = (iInd + kNODir / 2) % kNODir;	// the pointer to its Parent-Node;
					}

					/// if ALREADY IN "Open List Set", update the FValue and Parent-Pointer;
					else if (OpenedSet[rowNeighbor][colNeighbor] > pNode2->getFValue())
					{
						OpenedSet[rowNeighbor][colNeighbor] = pNode2->getFValue();	// update the FValue
						dirMap[rowNeighbor][colNeighbor] = (iInd + kNODir / 2) % kNODir;	// update the Parent-Pointe;


						// replace the node by emptying 1-q to the 0-q
						// except the node to be replaced will be ignored
						// and the new node will be pushed in instead

						// 将优先队列pqOpen[pqi]中的所有顶点转移到优先队列pqOpen[1-pqi];

						// All the Node in "Open List Set" except the New-Created-One;
						while (!(pqOpen[pqi].top().getLocation()._rowLoc == rowNeighbor &&
							     pqOpen[pqi].top().getLocation()._colLoc == colNeighbor))
						{
							pqOpen[1 - pqi].push(pqOpen[pqi].top());
							pqOpen[pqi].pop();
						}

						// remove the wanted node
						pqOpen[pqi].pop();

						// empty the larger size q to the smaller one
						if (pqOpen[pqi].size() > pqOpen[1 - pqi].size())
							pqi = 1 - pqi;


						while (!pqOpen[pqi].empty())
						{
							pqOpen[1 - pqi].push(pqOpen[pqi].top());
							pqOpen[pqi].pop();
						}
						pqi = 1 - pqi;

						// add the better node instead
						pqOpen[pqi].push(*pNode2);
					}
					else
					{
						delete pNode2;
					}
				}

				
			}/// end Loop_for( moves )

			delete pNode_CurBest;

		}/// end Loop_while (A * search)


		// no path found
		return "";
	}

	int main_algoAStar()
	{
		// create empty squares
		for (int j = 0; j < kVYDimMap; j++)
		{
			for (int i = 0; i < kHXDimMap; i++)
				mapSquares[i][j] = 0;
		}

		// make wall
		mapSquares[1][2] = 1;
		mapSquares[2][3] = 1;
		mapSquares[3][4] = 1;
		mapSquares[5][3] = 1;
		mapSquares[5][1] = 1;

		mapSquares[6][3] = 1;
		mapSquares[6][2] = 1;
		mapSquares[6][1] = 1;

		mapSquares[4][3] = 1;
		mapSquares[4][4] = 1;

		// starting and ending positions
		int iStart = 4, jStart = 2;
		int iEnd = 5, jEnd = 4;

		cout << "Grid Size (IDIM,JDIM): " << kHXDimMap << "," << kVYDimMap << endl;
		cout << "Start: " << iStart << "," << jStart << endl;
		cout << "Finish: " << iEnd << "," << jEnd << endl;

		clock_t start = clock();

		// get the path
		string path = pathFind(Location(iStart, jStart), Location(iEnd, jEnd));

		clock_t end = clock();
		double time = double(end - start);
		cout << "Time (ms): " << time << endl;
		// iInd = 0, 1, 2, 3
		// iDir = Right, Top, Left, Bottom
		cout << "path: " << path << endl;

		// follow the path on the squares and display it 
		if (path.length() > 0) {
			char c;
			int m, n;
			int i = iStart;
			int j = jStart;
			mapSquares[i][j] = 2;
			for (m = 0; m < path.length(); m++) {
				c = path.at(m);
				n = atoi(&c);
				i = i + kHXDir[n];
				j = j + kVYDir[n];
				mapSquares[i][j] = 3;
			}
			mapSquares[i][j] = 4;

			// display the squares with the path
			for (j = kVYDimMap - 1; j >= 0; j--) {
				for (i = 0; i < kHXDimMap; i++) {
					if (mapSquares[i][j] == 0)
						cout << "+";
					else if (mapSquares[i][j] == 1)
						cout << "O"; //obstacle Point
					else if (mapSquares[i][j] == 2)
						cout << "I"; //Initial	Point
					else if (mapSquares[i][j] == 3)
						cout << "P"; //path		Point
					else if (mapSquares[i][j] == 4)
						cout << "F"; //final	Point
				}
				cout << endl;
			}
		}

		return(0);
	}



}
/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/18/10/2016 BY.gaohuancai QQ1293302539 <<

#pragma once

namespace nsDSUDGraphCADMatrix
{
	int main_DSGraphADMatrix();
}

namespace nsDSUDGraphCPPADMatrix
{
#define MAX 100

	class MatrixUDG
	{
		public:
			//
			MatrixUDG();
			~MatrixUDG();

			//
			MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);

			//
			void print();

		protected:
			//
			char readChar();
			//
			int  getPosition(char ch);

		private:
			char _UDGVert[MAX];
			int  _UDGVertCounts;
			int  _UDGEdgeCount;

			int  _UDGMatrix[MAX][MAX];

	};


	int main_DSUDGraphCADMatrix();
}
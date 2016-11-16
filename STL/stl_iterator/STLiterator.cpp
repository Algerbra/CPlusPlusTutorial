/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#include "STLiterator.h"
#include <iostream>			//std::cout
#include <iterator>			//std::make_move_iterator
#include <vector>			//std::vector
#include <string>			//std::string
#include <algorithm>		//std::copy


namespace nsSTLiterator
{
	static void showVec(std::vector<int> & col)
	{
		fprintf(stderr, "\n");
		std::vector<int>::iterator it = col.begin();
		while (col.end() != it)
			fprintf(stderr, " %d ", *it++);
		fprintf(stderr, "\n\n");
	}


	std::vector<int> colInt({ 23, 4, 21, 15, 6, 2, 34, 5 });
	std::vector<std::string> colstr({ "hello", "world", "stl", "namespace" });

	int main_STLiterator()
	{

		std::vector<int>::iterator hit = mmfind(colInt.begin(), colInt.end(), 5);
		mmreverse<std::vector<int>::iterator, int>(colInt.begin(), colInt.end());


		std::vector<int>  cp;
		cp.resize(colInt.size());

		mmcopy(colInt.begin(), colInt.end(), cp.begin());
		showVec(cp);


		Ostream_iterator<int> oi(std::cout, "\n");
		int a[10];
		for (int i = 0; i != 10; ++i)
			a[i] = i + 1;
		mmCopy(a, a + 10, oi);

		return 0;
	}
}
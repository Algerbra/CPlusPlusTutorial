/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/9/2016 BY.gaohuancai QQ1293302539 <<
#include <stdio.h>
#include <stdlib.h>
#include "AlgSort.h"
#include "SortTemplate.h"
int main()
{
	int dataA[] = { 1, 12, 5, 26, 28, 14, 3, 7, 2 };
	const int dataaSz = sizeof(dataA) / sizeof(dataA[0]);

	int dataB[] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44 };
	const int databSz = sizeof(dataB) / sizeof(dataB[0]);


	//AlgSort::quickSort(dataA, 0, dataaSz - 1);
	//AlgSort::bubbleSort(dataA, dataaSz);
	//AlgSort::bubbleSortA(dataA, dataaSz);
	//AlgSort::insertSort(dataA, dataaSz);
	//AlgSort::selectSort(dataA, dataaSz);


	//AlgSort::mergeSort(dataA, 0, dataaSz-1);
	//logArray(dataA, 0, dataaSz, 0);

	std::vector<int> d({ 1, 12, 5, 26, 28, 14, 3, 7, 2 });

	mergeSort(d.begin(), d.end());
	
	for (int i = 0; i < d.size(); ++i)
		fprintf(stderr, " %d ", d[i]);

	system("pause");
	return 0;
}


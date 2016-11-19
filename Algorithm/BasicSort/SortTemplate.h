/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/9/2016 BY.gaohuancai QQ1293302539 <<
/// 
/// std::iterator_traits
/// 参考 泛型编程;
///		http://elloop.github.io/c++/2015-12-29/learning-using-stl-19-iterator-traits
///		
///	C++ STL 应用与实现目录;
///		http://blog.csdn.net/elloop/article/details/50357205
/// 
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>


namespace nsSortTemplate
{

	template<typename I>
	void mergeSort_move(I begin, I midPoint, I end)
	{
		//nested dependent type;
		//item of the above vector is the object pointed by the I-type;
		typedef std::vector<typename std::iterator_traits<I>::value_type> TmpVec;
		TmpVec  tmp(std::make_move_iterator(begin), std::make_move_iterator(end));
		TmpVec::iterator   begMov = std::begin(tmp);
		TmpVec::iterator   endMov = std::end(tmp);
		TmpVec::iterator   midPivot = std::next(begMov, std::distance(begin, midPoint));


		TmpVec::iterator   Lit = begMov;
		TmpVec::iterator   Rit = midPivot;
		I                  ndtObject = begin;

		//std::move the smaller to the front, until ...
		while (Lit < midPivot && Rit < endMov)
			*ndtObject++ = std::move((*Lit < *Rit) ? *Lit++ : *Rit++);

		//if middle pivot is not reached yet, std::move ...
		while (Lit < midPivot)
			*ndtObject++ = std::move(*Lit++);

		//if middle pivot is not reached yet, std::move ...
		while (Rit < endMov)
			*ndtObject++ = std::move(*Rit++);
	}

	template<typename I>
	void mergeSort(I begin, I end)
	{
		std::size_t length = std::distance(begin, end);
		if (length <= 1)
		{
			return;
		}

		std::size_t mid = length / 2;
		I           midPoint = std::next(begin, mid);

		mergeSort(begin, midPoint);
		mergeSort(midPoint, end);

		mergeSort_move(begin, midPoint, end);
	}


	int main_SortTemplate()
	{
		int dataA[] = { 1, 12, 5, 26, 28, 14, 3, 7, 2 };
		const int dataaSz = sizeof(dataA) / sizeof(dataA[0]);

		int dataB[] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44 };
		const int databSz = sizeof(dataB) / sizeof(dataB[0]);

		std::vector<int> d({ 1, 12, 5, 26, 28, 14, 3, 7, 2 });

		mergeSort(d.begin(), d.end());

		for (int i = 0; i < d.size(); ++i)
			fprintf(stderr, " %d ", d[i]);

		return 0;
	}
}

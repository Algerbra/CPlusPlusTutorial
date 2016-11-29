/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<


#include <algorithm>
#include <string>
#include <vector>
#include "STLiterator_traits.h"

#include <climits>
namespace nsSTLTraits
{
	static std::vector<int> colInt({ 23, 4, 21, 15, 6, 2, 34, 5 });
	static std::vector<std::string> colstr({ "hello", "world", "stl", "namespace" });


	int main_STL_iterator_traits()
	{
		std::vector<int>::iterator it = iteratorTraits_find(colInt.begin(), colInt.end(), 55);
		std::vector<std::string>::iterator itstr = iteratorTraits_find(colstr.begin(), colstr.end(), "hello");
		++itstr;


		MyIter<int> ite(new int(8));
		std::cout << "func(*) value \t" << func(ite) << std::endl;
		std::cout << typeid(iterator_traits<MyIter<int> >::value_type).name() << "\n";
		std::cout << typeid(iterator_traits<int * >::value_type).name() << "\n";
		std::cout << typeid(iterator_traits<const int * >::value_type).name() << "\n";


		std::vector< std::string >foo(3);
		std::vector<std::string > bar({ "one", "two", "three" });
		std::copy((bar.begin()), (bar.end()), foo.begin());
		bar.clear();
		std::cout << "foo \n";
		for (std::string & x : foo)
			std::cout << x << ' ';


		/// ///////////////////////////////////////////////////////////////////////
		float fmax = std::numeric_limits<float>::max();
		float fmin = std::numeric_limits<float>::min();

		return 0;
	}
}

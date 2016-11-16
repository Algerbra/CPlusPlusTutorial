/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#include "SingletonA.h"


SingletonAa* SingletonAa::pInstance = 0;

namespace nsSingletonA
{

	int main_SingletonA()
	{

		SingletonA  & pInst = SingletonA::getInstance();
		SingletonAa * pInstance = SingletonAa::instance();

		for (int i = 0; i < 53; ++i)
		{
			fprintf(stderr, " %d \t ", i % 2);
		}

		return 0;
	}
}
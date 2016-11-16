/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#pragma once
/// 
/// 左值与右值的定义;
/// 左值和右值的语法符号;
/// 
/// http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
/// 
/// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include <vector>
#include "STLiterator_auxiliary_function.h"

void process_value(int & i)
{
	fprintf(stderr, "\t process(int &) Lvalue processed: %d\n", i);
}

void process_value(int && i)
{
	fprintf(stderr, "\t process(int &&) Rvalue processed: %d\n", i);
}


/// Process_value 函数被重载，分别接受左值和右值。由输出结果可以看出，临时对象是作为右值处理的;
/// 但是如果临时对象通过一个接受右值的函数传递给另一个函数时，就会变成左值，因为这个临时对象在传递过程中，变成了命名对象;
/// 
void forward_value(int && i)
{
	fprintf(stderr, "\t forward(int &&) Rvalue processed: %d\n", i);

	/// 虽然 2 这个立即数在函数 forward_value 接收时是右值，但到了 process_value 接收时，变成了左值;
	process_value(i);
}



/// 
/// std::move()  --Iterator auxiliary function;
/// 
void ProcessValue(int & i)
{
	fprintf(stderr, "ProcessValue(int &) -Lvalue: %d\n", i);
}
void ProcessValue(int && i)
{
	fprintf(stderr, "ProcessValue(int &&) -Rvalue: %d\n", i);
}

namespace nsSTLmove
{
	int main_STL_Rvalue_Reference()
	{
		if (false){
			int a = 0;
			process_value(a);
			process_value(1);
			forward_value(2);

			MyString ab;
			ab = MyString("Hello");
			std::vector<MyString> colstr;
			colstr.push_back(MyString("world"));

		}

		int abc = 0;
		ProcessValue(abc);
		ProcessValue(std::move(abc));

		fprintf(stderr, "\n\n");

		return 0;
	}
}
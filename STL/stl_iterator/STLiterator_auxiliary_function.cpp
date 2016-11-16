/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#pragma once
/// 
/// ��ֵ����ֵ�Ķ���;
/// ��ֵ����ֵ���﷨����;
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


/// Process_value ���������أ��ֱ������ֵ����ֵ�������������Կ�������ʱ��������Ϊ��ֵ�����;
/// ���������ʱ����ͨ��һ��������ֵ�ĺ������ݸ���һ������ʱ���ͻ�����ֵ����Ϊ�����ʱ�����ڴ��ݹ����У��������������;
/// 
void forward_value(int && i)
{
	fprintf(stderr, "\t forward(int &&) Rvalue processed: %d\n", i);

	/// ��Ȼ 2 ����������ں��� forward_value ����ʱ����ֵ�������� process_value ����ʱ���������ֵ;
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
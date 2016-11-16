/************************************************************************
/************************************************************************

	http://lib.csdn.net/article/cplusplus/25890

	��ȻC++������C��ָ����ôǿ��Ķ�����,Ϊʲô��Ҫiterator��ôһȺ����������?;

	�����Ǳ�дģ���ʱ��,����ʹ����iterator��Ϊ�����ĺ���;
	�����ú�������iterator��Щ�ض��Ĳ���;
	
	��������2������;
			///Test code:
			std::vector<int> colInt({ 23, 4, 21, 15, 6, 2, 34, 5 });
			std::vector<int>::iterator hit = mmfind(colInt.begin(), colInt.end(), 5);
			mmreverse<std::vector<int>::iterator, int>(colInt.begin(), colInt.end());


	��������������ģ�����P����һ��Ҫ��;
	
		��find��,����Ҫ��P�������� != ,++��*(P)������������Ĳ���;
		������reverse������˵,��Ҫ�����,�����++,--,*(),!=������֧��;
		�������ô������,������ô�������˶�������һҪ����;?
	����˵;
		�����������ģ���ʹ������ô���ڲ�֪��ʵ��ϸ�ڵ�������˽Ⲣ������ЩҪ����;?
		��Ȼ,������Ҫһ�����෽����֪����ν綨��ͬ����ĵ�����;


	�����������ĳ�T��ָ��Ҳ����ɵĺܺ�,��Ҫ iterator ��ʲô;?

		ԭ�����ڲ����������ݽṹ�������Ե�!����һ��������˵;
		���Ҫʵ�������Ĺ���;
		��������дһ������һ�������ǰ�++start���start = start->next�ĺ���;

	��Ȼ, �����ظ������������ǲ�ϣ��������,��������������ǳ���������;
	����ʱ��,iterator�����þͳ�����;
	
	��������;
		�����iterator(list_iterator)����ֻҪ��operator++()��д��operator++(){now = now->next;};
		����������ʹ��find������.��ȫ����Ҫ���±�д.��ͼ����������㷨�ı�д��;

	����,��Ȼ����֪����iterator�ĺô���֮��,���������Ǿ���֪��֮ǰ�ᵽ�ķ��෨����ô������;


	test instance:
				std::vector<int> colInt({ 23, 4, 21, 15, 6, 2, 34, 5 });
				std::vector<int>::iterator hit = mmfind(colInt.begin(), colInt.end(), 5);
				mmreverse<std::vector<int>::iterator, int>(colInt.begin(), colInt.end());
				showVec(cp);

/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
template<typename P, typename T>
P mmfind(P start, P beyond, const T& key)
{
	while (start != beyond && *start != key)
		++start;

	return start;

}


template<typename P, typename T>
void mmreverse(P start, P beyond)
{
	while (start != beyond)
	{
		--beyond;

		if (start != beyond)
		{
			T t = *start;
			*start = *beyond;
			*beyond = t;

			++start;
		}
	}
}

///
/// Output Iterator
///
/************************************************************************

	output iterator ������ʽ���������,�����ܶ���ָ������н���д����;
	output iterator �� input iterator ����ͬ�ľ��� *p �����ص�ֵ�����޸�,����һ��Ҫ��ȡ;
	input iterator ֻ�����ȡ,�������޸�;
	
	֧�ֵĲ�����input iterator ��ͬ;
		(*p)  (++p)  (p++)  (p!=q)  ��p==q)


	test instance:
				std::vector<int> colInt({ 23, 4, 21, 15, 6, 2, 34, 5 });
				std::vector<int>  cp;
				cp.resize(colInt.size());
				mmcopy(colInt.begin(), colInt.end(), cp.begin());
				showVec(cp)
/************************************************************************/
template<typename In, typename Out>
void mmcopy(In start, In beyond, Out result)
{
	while (start != beyond)
	{
		(*result) = (*start);
		(++result);
		(++start);
	}
}

template<typename In, typename Out>
void mmcopya(In start, In beyond, Out result)
{
	while (start != beyond)
		(*result++) = (*start++);
}


/************************************************************************
	�򵥹���һ�� ostream_iterator ����ʹ��mmCopy()��������Ϊ���;
	�˴� ostream_iterator �� STL �кܴ���,��������Ϊ����;


	test instance;

				Ostream_iterator<int> oi(std::cout, "\n");
				int a[10];
				for (int i = 0; i != 10; ++i)
				a[i] = i + 1;
				mmCopy(a, a + 10, oi);

/************************************************************************/
#include <iostream>
template<typename T>
class Ostream_iterator
{
public:

	Ostream_iterator(std::ostream & os, const char * s) :strm(&os), str(s) {}

	Ostream_iterator& operator ++ (){ return *this; }
	Ostream_iterator& operator ++(int){ return *this; }

	Ostream_iterator& operator * (){ return *this; };
	Ostream_iterator& operator =(const T& rth)
	{
		*strm << rth << str;

		return *this;
	}
	
private:
	std::ostream * strm;
	const char * str;
};


template<typename In, typename Out>
Out mmCopy(In start, In beyond, Out dest)
{
	while (start != beyond)
		(*dest++) = (*start++);

	return dest;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace nsSTLiterator
{
	int main_STLiterator();
}


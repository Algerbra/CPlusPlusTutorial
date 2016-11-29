/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
/// 
/// C++ STL Iterator_traits
///
/// http://blog.zhengdong.me/2010/09/22/from-concept-to-iterator_traits/
///
template<typename Iterator, typename T>
Iterator iteratorTraits_find(Iterator first, Iterator last, const T & value)
{
	while (first != last && (*first) != value)
		++first;

	return first;
}



/************************************************************************/
/*                                                                      */
/************************************************************************/

///
/// ��ȡ(traits)��̼����Ľ��ܺ�Ӧ��;
/// http://www.searchtb.com/2014/03/%E8%90%83%E5%8F%96traits%E7%BC%96%E7%A8%8B%E6%8A%80%E6%9C%AF%E7%9A%84%E4%BB%8B%E7%BB%8D%E5%92%8C%E5%BA%94%E7%94%A8.html
///
/************************************************************************
	
/************************************************************************/
template<typename Iterator, typename T>
Iterator demo_find(Iterator begin, Iterator end, const T& value)
{
	while (begin != end && (*begin) != value)
		++begin;

	return begin;
}


template<typename Iterator>
typename Iterator::value_type getValue(Iterator iter)
{
	return *iter;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
/// 
/// 
/// C++ Traits ��̼���--�ӵ���������ƿ������Ƶ��������Ƶ�;
/// http://blog.csdn.net/gatieme/article/details/50950726
/// 
/// Nested-Dependent-Type-Name

/************************************************************************

		Test Instance:
					MyIter<int> ite(new int(8));
					std::cout << func(ite) << std::endl;

	//////
	//
	// ����;
	//
	func()�ķ���ֵ������Ϊ typename Iter::value_type	;
	��Ƕ���ͱ�����Ϊ typedef T value_type				;

	���� T ��һ�� template ����,���������������廯/ʵ����֮ǰ�������� T ��һ����֪	;
	��������ʱ����֪�� MyIter<T>::value_type ����������ͻ��ǳ�Ա�����������ݳ�Ա	;

	����� typename �ؼ��ֵ���������ڸ��߱����� Iter::value_type �Ǹ�����	;

	//
	// ����;
	//
	���������еĵ�����������class type	;
	������ԭ����ָ��Ͳ��ǡ��������class type�����޷�Ϊ��������Ƕ����	;
	
/************************************************************************/
#include <iostream>
template<typename T>
struct MyIter
{
	MyIter(T * p = NULL)
		:m_ptr(p)
	{
		// NOP...
	}

	T & operator * ()const
	{
		return *m_ptr;
	}


	typedef T	value_type;		// declaration of nested-type;
			T	*m_ptr;
};

template<typename Iter>
typename Iter::value_type		// type of returned value;
func(Iter iter)
{
	// TODO:
	return *iter;
}


/************************************************************************
	template partial specialization 

	ģ���ػ�����;

	��� class templateӵ��һ�����ϵ�template����	;
	��ô�����������ĳ�������߶�������ǲ���ȫ�����Ĳ��������ػ�����	;

	���仰˵�����ǿ����ڷ���������ṩһ���ػ��İ汾;
	��ͨ���������汾�е�ĳЩtemplate����������ȷ��ָ��;


	ͨ������κ�template������ģ�棬�����ػ����õ�һ�������˲���������ػ��汾	;

	����������������ǾͿ��Խ��ǰ���ġ���Ƕ���͡�δ�ܽ��������;
	��ǰ�������ǣ�ԭ����ָ�벢��class������޷�Ϊ���Ƕ�����Ƕ�ͱ�;

	�������ǿ���ͨ���Ե�����ָ��Ϊ�������ػ���������ƿ��Խ���ԭ��ָ������������;

/************************************************************************/
template<typename T>	//[�����汾]	;
class Demo_C			//[�����汾] ������� T Ϊ��������	;
{
	/// NOP....
};
template<typename T>	//[�ػ��汾]�ػ��� Demo_C �����ԭ��ָ����Ϊ����	;
class Demo_C<T*>		//[�ػ��汾]������ T Ϊԭ��ָ������	;
{
	/// T Ϊԭ��ָ����� T Ϊ�������͵�һ������һ������������;
	/// ͬ�������±�����������ѡ���ػ��汾��ʵ��;
	/// NOP...
};


/************************************************************************
	���ܵ��м��	;

	�����Ƴ�һ���м��,�����һ�� value type ��Ƕ����;


	Test instance:
				MyIter<int> ite(new int(8));
				std::cout <<"func(*) value \t"<< func(ite) << std::endl;
				std::cout << typeid(iterator_traits<MyIter<int> >::value_type).name() << "\n";
				std::cout << typeid(iterator_traits<int * >::value_type).name() << "\n";
				std::cout << typeid(iterator_traits<const int * >::value_type).name() << "\n";
/************************************************************************/

template<typename Iter>		//[�����汾] iterator_traits ����;
struct iterator_traits
{
	//��� Iter �������Լ��� value_type	;
	//��ô��ͨ����� iterator_traits ������	;
	//��ȡ�� value_type��Ա ���� Iter::value_type	;
	typedef typename Iter::value_type	value_type;
};


template<typename T>		//[�ػ��汾]Ϊ�м�� iterator_traits ����ػ��汾	;
struct iterator_traits<T*>	//[�ػ��汾]�ػ����ģ�� iterator_traits ���Ƚ��� <T*> ����	;
{
	//�ɴ�,ԭ��ָ���� (int*) ��Ȼ��������� (class type) ���ͨ�� traits ��ȡ�� value type	;
	//���ǵ�����֧��ԭ��ָ��������	;
	typedef T	value_type;	//
};

template<typename T>
struct iterator_traits<const T*>//[�ػ��汾]���� <const T*> ����,��ȡ��һ�� T ����;
{
	typedef T	value_type;
};



template<typename Iter>		//[���°汾]	;
typename iterator_traits<Iter>::value_type
func_new(Iter iter)
{
	/// NOP...
	return *iter;
}





/************************************************************************
	STL �е����������	;

	STL Դ��,�� <stl_iterator_base.h>	;
/************************************************************************/


namespace nsSTLTraits
{
	int main_STL_iterator_traits();
}
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
/// 萃取(traits)编程技术的介绍和应用;
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
/// C++ Traits 编程技法--从迭代器的设计看参数推导与类型推导;
/// http://blog.csdn.net/gatieme/article/details/50950726
/// 
/// Nested-Dependent-Type-Name

/************************************************************************

		Test Instance:
					MyIter<int> ite(new int(8));
					std::cout << func(ite) << std::endl;

	//////
	//
	// 解析;
	//
	func()的返回值被定义为 typename Iter::value_type	;
	内嵌类型被定义为 typedef T value_type				;

	由于 T 是一个 template 参数,在它被编译器具体化/实例化之前编译器对 T 是一无所知	;
	编译器此时并不知道 MyIter<T>::value_type 代表的是类型还是成员函数或是数据成员	;

	而这个 typename 关键字的用意就在于告诉编译器 Iter::value_type 是个类型	;

	//
	// 问题;
	//
	并不是所有的迭代器都是类class type	;
	比如有原生的指针就不是。如果不是class type，就无法为它定义内嵌类型	;
	
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

	模板特化问题;

	如果 class template拥有一个以上的template参数	;
	那么可以针对其中某个（或者多个，但是不能全部）的参数进行特化工作	;

	换句话说，我们可以在泛化设计中提供一个特化的版本;
	即通过将泛化版本中的某些template参数赋予明确的指定;


	通过针对任何template参数的模版，进行特化，得到一个限制了参数对象的特化版本	;

	有了这个利器，我们就可以解决前述的”内嵌类型”未能解决的问题;
	先前的问题是，原生的指针并非class，因此无法为他们定义内嵌型别;

	现在我们可以通过对迭代器指针为参数的特化对象，来设计可以接收原生指针的特殊迭代器;

/************************************************************************/
template<typename T>	//[泛化版本]	;
class Demo_C			//[泛化版本] 允许接收 T 为任意类型	;
{
	/// NOP....
};
template<typename T>	//[特化版本]特化的 Demo_C 类接受原生指针作为对象	;
class Demo_C<T*>		//[特化版本]适用于 T 为原生指针的情况	;
{
	/// T 为原生指针便是 T 为任意类型的一个更进一步的条件限制;
	/// 同等条件下编译器会优先选择特化版本的实现;
	/// NOP...
};


/************************************************************************
	万能的中间层	;

	因此设计出一个中间层,并添加一个 value type 内嵌对象;


	Test instance:
				MyIter<int> ite(new int(8));
				std::cout <<"func(*) value \t"<< func(ite) << std::endl;
				std::cout << typeid(iterator_traits<MyIter<int> >::value_type).name() << "\n";
				std::cout << typeid(iterator_traits<int * >::value_type).name() << "\n";
				std::cout << typeid(iterator_traits<const int * >::value_type).name() << "\n";
/************************************************************************/

template<typename Iter>		//[泛化版本] iterator_traits 对象;
struct iterator_traits
{
	//如果 Iter 定义有自己的 value_type	;
	//那么就通过这个 iterator_traits 的作用	;
	//萃取出 value_type成员 就是 Iter::value_type	;
	typedef typename Iter::value_type	value_type;
};


template<typename T>		//[特化版本]为中间层 iterator_traits 添加特化版本	;
struct iterator_traits<T*>	//[特化版本]特化后的模板 iterator_traits 优先接收 <T*> 参数	;
{
	//由此,原生指针如 (int*) 虽然不是类对象 (class type) 亦可通过 traits 萃取其 value type	;
	//于是迭代器支持原生指针类型了	;
	typedef T	value_type;	//
};

template<typename T>
struct iterator_traits<const T*>//[特化版本]接收 <const T*> 参数,萃取出一个 T 类型;
{
	typedef T	value_type;
};



template<typename Iter>		//[更新版本]	;
typename iterator_traits<Iter>::value_type
func_new(Iter iter)
{
	/// NOP...
	return *iter;
}





/************************************************************************
	STL 中迭代器的设计	;

	STL 源码,见 <stl_iterator_base.h>	;
/************************************************************************/


namespace nsSTLTraits
{
	int main_STL_iterator_traits();
}
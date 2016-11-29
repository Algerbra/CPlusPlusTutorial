/************************************************************************
  Reference
	0) What is Traits?
	http://www.bogotobogo.com/cplusplus/template_specialization_traits.php

  Reference
	http://www.bogotobogo.com/cplusplus/templates.php#restrictionstemplateparameter

	We use templates when we need functions/classes that apply the same
	- algorithm to a several types. So we can use the same function/class
	- regardless of the types of the argument or result.

	... The compiler then generates a specific class of function when we
	- later provide specific types as arguments. In a sense, templates
	- provide STATIC (compile-time) polymorphism, as opposed to
	- DYNAMIC (run-time) polymorphism. 

	... We can think of a class template as a TYPE GENERATOR. The process
	- of generating types from a class template is called specialization or
	- template instantiation, which happens at COMPILE-TIME or LINK-TIME not
	- at RUN-TIME.

/************************************************************************/
///  >> 11/29/22/2016 BY.gaohuancai QQ1293302539 <<
#include "STL_iterator_traits.h"


namespace nsSTLIteratorTraits
{

	/************************************************************************
	  Reference
	    http://www.bogotobogo.com/cplusplus/templates.php#restrictionstemplateparameter

		More on Template Parameter
		-	Type parameter  /  non-Type parameter



	/************************************************************************/
	namespace ns_scope_of_template_parameter
	{
		// // // // // // // 
		//
		//Scope of Template Parameter
		//
		// the global typedef that defines T as float is hidden by the type 
		// parameter named T. So tmp is not a float, it still has the type of
		// the template parameter T, not that of the global typedef.
		// In other words, the type of tmp is whatever type gets bound to
		// the template parameter T.
		typedef float T;
		template <typename T>
		T & userMin(const T & a, const T & b)
		{
			T tmp = ((a < b) ? (a : b));
			return tmp;
		};



	};
	//end namespace ns_scope_of_template_parameter;

	namespace ns_template_parameter_name
	{

		// // // // // // // 
		//
		//Template Parameter Name
		// The name of a template parameter T or something like.
		// The keywords typename and class ..
		// "We must be explicit because the compiler cannot tell when a name
		//   defined by a type parameter is a TYPE or a VALUE."

		//  If T::const_iterator is a type, then the line is a declaration.
		//  But if T::const_iterator is an object, then it's a multiplication.
		//  We know that const_iterator must be a member of the type bound to T,
		//  but we do not know whether const_iterator is the name of a type or
		//  a data member.
		template <typename T >
		void foo_wrong(const T & vector)
		{
			T::const_iterator * it;//a wrong way
		};


		// So, if we want the compiler to treat const_iterator as a type,
		// then we must explicitly tell the compiler to do so:
		template<typename T>
		void foo_correct(const T & vector)
		{
			// By writing typename T::const_iterator
			// we indicate that member const_iterator of the type
			// bound to T is the name of a type..
			typename T::const_iterator * it;// a correct way;
		}


		// similar example:
		template <typename T>
		class A
		{
			// the typename is used to clarify that MyType is a type of class T.
			// So, ptr is pointer to the type T::MyType.
			// Without typename, MyType would be considered a static member.
			typename T::MyType * ptr_variable;

			//T::Mytype * ptr_value;// this would be a multiplication of value MyType of type T with ptr_value;
		};

	};
	// end namespace ns_template_parameter_name


	/// Scott Meyers called a variable like T::const_iterator a "nested dependent type name"
	/// :
	/// anytime we refer to a Nested-Dependent-Type-Name in a template,
	/// we must immediately precede it by the word typename because in C++
	/// any identifier of a template is considered to be a value
	/// if it is qualified by typename..

	namespace ns_another_eg_of_typename
	{
		template <typename T>
		void foo_local_var(T it)
		{
			// here declares a local variable, tmp,
			// which is the same type as what T objects point to,
			// and it initializes tmp with the object that T points to.
			// So, if T is list<string>::iterator, then tmp is of type string..
			typename iterator_traits<T>::value_type tmp(*it);

		}

	};
	// end namespace ns_another_eg_of_typename_iterator_traits



	/************************************************************************
	  ...So, C++ STL provides a special template structure to define the 
	  iterator_traits. This structure has information regarding an iterator.
	  It is used as a common interface for all the type definitions an iterator
	  should have, such as the category, the type of the elements, and so on.

	/************************************************************************/
	namespace ns_iterator_traits
	{

		template < typename T>
		struct std_iterator_traits
		{
			typedef typename T::value_type			value_type;
			typedef typename T::difference_type		difference_type;
			typedef typename T::iterator_category	iterator_category;
			typedef typename T::pointer				pointer;
			typedef typename T::reference			reference;
		};

		// Here, T stands for the type of the iterator.
		// So the following expression yields the value type of iterator type T:
		/// typename std::iterator_traits<T>::value_type;
		/// ns_iterator_traits::std_iterator_traits<T>::value_type ;

	};
	//end namespace ns_iterator_traits

	/// iterator_traits is so named COZ it describes argument's property/traits.
	/// The most important feature of traits templates is that they provide us
	/// a way to associate information with a type non-intrusively...



	/************************************************************************
	  http://blog.csdn.net/wenqian1991/article/details/19815721
		
		...因此每一种容器型别都必须提供自己的迭代器;
		事实上每种容器都将其迭代器以嵌套方式定义于其自身内部;

		value_type  
		/  是指迭代器所指对象的型别;任何一个打算与STL算法有完美搭配的 class;
		/  都应该定义自己的 value_type 内嵌型别;

		difference_type
		/  用来表示两个迭代器直接的距离,因此可以用来表示一个容器的最大容量;
		/  对于连续空间的容器而言,头尾之间的距离就是其最大容量;

		reference
		/  从迭代器所指之物的内容是否允许改变的角度而言;
		/  可分为 -所指对象内容不可更改 -所指对象内容可更改;
		/  其中 -所指对象内容可更改 可以为左值,在C++中;
		/  如果函数要传回左值,都是以 by reference 的方式进行;

		iterator_category
		/  迭代器类型,可以分为五类;
			input iterator
				/  read-only  迭代器所指对象内容不允许外界更改;
				/  只能一次一个向前读取元素(不支持operator--);并按此顺序一个个传回元素值;

			output iterator
				/  write-only  向前将元素值一个个写入(不支持operator--);
				/  只能一个一个元素的赋新值;

			forward iterator
				/  
			bidirectional iterator
				/
			random access iterator
				/




		... 于是 SGI STL 采用了 traits 编程技巧,;
		... 其实质就是 traits 依靠显示模板特殊化;
		... 把代码中因类型不同而发生变化的片段拖出来用统一的接口来封装;
		... traits 有能力通过模板特殊化来萃取出迭代器的种类;
	/************************************************************************/

	  

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	int main_STL_iterator_traits()
	{
		return 0;
	}
}

/************************************************************************
  Reference
	https://www.cs.helsinki.fi/u/tpkarkka/alglib/k06/lectures/iterators.html



/************************************************************************/
///  >> 11/27/18/2016 BY.gaohuancai QQ1293302539 <<
#include "STL_1127_Iterator.h"

#include <vector>

namespace nsSTL1127Iterator
{
	/************************************************************************
	
	  Iterators
		[00] Iterator is generalized poiner identifying a position in a container;
		[01] Allowing moving in the container and accessing elements;
	
		[02] Iterator can have three kinds of values;
		     A dereferenceable iterator points to an element;
			 A past the end iterator points to the one-step-beyond-last position of a container;
			 A singular iterator does not point anywhere. It corresponds to NULL pointer;

	/************************************************************************/

	/// ///////////////////////////////////////////////////////////////////////
	/// Algorithm find.

	template<typename Iterator, typename T>
	Iterator ITfind(Iterator begin, Iterator end, const T & value)
	{
		while (end != begin && value != (*begin))
			++begin;

		return begin;
	}


	/// Example: simple List;

	struct struNode
	{
	public:
		int val;
		struNode * next;

		struNode(int i, struNode * n) :val(i), next(n){}

	public:
		// iterator
		struct iterator
		{
			struNode * ptr;

			iterator(struNode * p = nullptr) :ptr(p){}

			int & operator * () { return ptr->val; }
			iterator & operator ++ () { ptr = ptr->next; return *this; }
			iterator & operator ++ (int) {iterator tmp = (*this);++*this;return tmp;}
			bool operator == (const iterator & rhs)const {return (ptr == rhs.ptr); }
			bool operator != (const iterator & rhs)const { return (ptr != rhs.ptr); }


		};
		iterator begin(){ return iterator(this); }
		iterator end(){ return iterator(); }
	};

	
	/// Test Code..

	static int main_test_struNode()
	{
		int iKey = 0;
		fprintf(stderr, "input the number to find: \n");
		scanf("%d", &iKey);
		std::vector<int > col = { 12, 4, 9, 21, 70, 25, 44 };
		std::vector<int>::iterator it;
		it = ITfind(col.begin(), col.end(), iKey);


		struNode * list = new struNode(3, 0);
		list = new struNode(2, list);
		list = new struNode(1, list);

		struNode::iterator iter = ITfind(list->begin(), list->end(), 1);
		if (iter != list->end())
			fprintf(stderr, "find the value: %d\n", (*iter));
		else
			fprintf(stderr, "** failed to find the value...\n");

		return 0;
	}


	/************************************************************************

	  https://www.cs.helsinki.fi/u/tpkarkka/alglib/k06/lectures/iterators.html
	  [Iterator Categories]

	    The ITfind(...) function defined above uses the following operators
		-  of the iterator:
			PRE-increment  /  (++operator)
			DE-reference   /  (operator*)
			comparison     /  (operator !=)
			copy constructor/  (...)

		The algorithm works for any iterator type that defines the operators
		-	of above features properly. Such a list of requirement is sometimes
		-	called a CONCEPT.


	  

	/************************************************************************/

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	int main_STL1127Iterator()
	{
		main_test_struNode();

		return 0;
	}
}




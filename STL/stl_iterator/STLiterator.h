/************************************************************************
/************************************************************************

	http://lib.csdn.net/article/cplusplus/25890

	既然C++沿用了C的指针这么强大的东西了,为什么还要iterator这么一群类来工作呢?;

	在我们编写模板的时候,对于使用了iterator做为参数的函数;
	往往该函数对于iterator有些特定的操作;
	
	比如下列2个函数;
			///Test code:
			std::vector<int> colInt({ 23, 4, 21, 15, 6, 2, 34, 5 });
			std::vector<int>::iterator hit = mmfind(colInt.begin(), colInt.end(), 5);
			mmreverse<std::vector<int>::iterator, int>(colInt.begin(), colInt.end());


	这两个函数都对模板参数P做了一定要求;
	
		在find中,我们要求P必须允许 != ,++和*(P)这三个运算符的操作;
		而对于reverse函数来说,其要求更多,运算符++,--,*(),!=都必须支持;
		问题就这么出来了,我们怎么让所有人都遵守这一要求呢;?
	或者说;
		后续采用这个模板的使用者怎么能在不知道实现细节的情况下了解并遵守这些要求呢;?
		显然,我们需要一个分类方法来知道如何界定不同种类的迭代器;


	这两个函数改成T的指针也能完成的很好,还要 iterator 做什么;?

		原因在于不是所有数据结构都是线性的!对于一个链表来说;
		如果要实现上述的功能;
		必须重新写一个几乎一样仅仅是把++start变成start = start->next的函数;

	显然, 这样重复的事情我们是不希望碰到的,尤其如果函数还非常大的情况下;
	而这时候,iterator的作用就出来了;
	
	对于链表;
		链表的iterator(list_iterator)仅仅只要把operator++()重写成operator++(){now = now->next;};
		就能正常的使用find函数了.完全不需要重新编写.这就减少了我们算法的编写量;

	现在,既然我们知道了iterator的好处了之后,接下来我们就想知道之前提到的分类法是怎么回事了;


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

	output iterator 工作方式类似输出流,我们能对其指向的序列进行写操作;
	output iterator 与 input iterator 不相同的就是 *p 所返回的值运行修改,而不一定要读取;
	input iterator 只允许读取,不允许修改;
	
	支持的操作和input iterator 相同;
		(*p)  (++p)  (p++)  (p!=q)  （p==q)


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
	简单构造一个 ostream_iterator 并且使用mmCopy()函数来作为输出;
	此处 ostream_iterator 和 STL 有很大差别,但功能行为完整;


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


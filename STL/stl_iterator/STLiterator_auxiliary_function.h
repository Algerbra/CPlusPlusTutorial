/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#pragma once

//void process_value(int & i);
//void process_value(int && i);
//void forward_value(int && i);



/// 
/// 转移语义的定义;
/// 实现转移构造函数和转移赋值函数;
///		http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
/// 
///		右值引用是用来支持转移语义的。转移语义可以将资源 ( 堆，系统对象等 ) 从一个对象转移到另一个对象;
///		这样能够减少不必要的临时对象的创建、拷贝以及销毁，能够大幅度提高 C++ 应用程序的性能;
///		临时对象的维护 ( 创建和销毁 ) 对性能有严重影响;
///
///		转移语义和拷贝语义相对，可类比文件的剪切与拷贝，当将文件从一个目录拷贝到另一个目录时，速度比剪切慢很多;
///		通过转移语义，临时对象中的资源能够转移其它的对象里;
///		在现有的 C++ 机制中，我们可以定义拷贝构造函数和赋值函数;
///		要实现转移语义，需要定义转移构造函数，还可以定义转移赋值操作符;
///		对于右值的拷贝和赋值会调用转移构造函数和转移赋值操作符;
///		如果转移构造函数和转移拷贝操作符没有定义，那么就遵循现有的机制，拷贝构造函数和赋值操作符会被调用;
///		
///		普通的函数和操作符也可以利用右值引用操作符实现转移语义;
/// 
/************************************************************************
	Test Instance:
				MyString a;
				a = MyString("Hello");
				std::vector<MyString> colstr;
				colstr.push_back(MyString("world"));

	Result:
	// before definition of Move Copy Constructor and Move Assignment Operator Method;

				Copy Assignment is called : source : Hello
				Copy constructor is called: source : world


	测试用例中;
	实现了调用拷贝构造函数,拷贝赋值操作符的操作;
	MyString("Hello"),MyString("world")都是临时对象,也是右值;

	虽然是临时的,程序仍然调用了拷贝构造和拷贝赋值,造成没有意义的资源申请和释放的操作;
	如果能够直接使用临时对象已经申请的资源,则既节省资源又节省资源再次申请和释放的时间;

	而这正是定义转移语义的本源意义;

	Test Instance:
				same with codes above wholly;
	Result:
	// after definition of Move Copy and Move Assignment...
				Move Assignment is called : source : Hello
				Move Constructor is called : source : world
	编译器区分了左值和右值，对右值调用了转移构造和转移赋值操,节省资源，提高运行的效率;
	有了右值引用和转移语义，在设计和实现类时;
	对于需要动态申请大量资源的类，应该设计转移构造函数和转移赋值函数，以提高应用程序的效率;

/************************************************************************/
class MyString
{
private:
	char * _data;
	size_t _len;

	void _init_data(const char * s)
	{
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

public:
	MyString(){
		_data = NULL;
		_len = 0;
	}

	MyString(const char * p){
		_len = strlen(p);
		_init_data(p);
	}

	MyString(const MyString & str) {
		_len = str._len;
		_init_data(str._data);
		fprintf(stderr, "Copy Constructor is called~ source: %s\n", str._data);
	}

	MyString & operator = (const MyString & str) {
		if (&str != this) {
			_len = str._len;
			_init_data(str._data);
		}

		fprintf(stderr, "Copy Assignment is called~ source: %s\n", str._data);

		return *this;
	}


	virtual ~MyString(){
		if (_data)free(_data);
	}

public:
	/// 
	/// 首先定义转移构造函数;
	/// 参数(右值类型)的符号必须是右值引用符号, 即 /&&/;
	/// 参数(右值类型)不可以是常量, 因为此处需要修改右值, 即不可以是 (const MyString && str);
	/// 参数(右值类型)的资源链接和标记必须修改,否则右值的析构函数就会释放资源,转移到新对象的资源就无效了;
	/// 
	MyString(MyString && str)
	{
		fprintf(stderr, "Move Constructor is called : source : %s \n", str._data);
		_len = str._len;
		_data = str._data;
		str._len = 0;
		str._data = NULL;
	}


	/// 
	/// 其次定义转移赋值操作符;
	MyString & operator = (MyString && str)
	{
		fprintf(stderr, "Move Assignment is called : source : %s \n", str._data);
		if (&str != this)
		{
			_len = str._len;
			_data = str._data;
			str._len = 0;
			str._data = NULL;
		}
		return *this;
	}


};

/// 
/// std::move()  --Iterator auxiliary function;
/// 
/************************************************************************
	标准库函数 std::move
		既然编译器只对右值引用才能调用转移构造函数和转移赋值函数，而所有命名对象都只能是左值引用;
		如果已知一个命名对象不再被使用而想对它调用转移构造函数和转移赋值函数;

		也就是把一个左值引用当做右值引用来使用，怎么做呢;？
		标准库提供了函数 std::move ;
		这个函数以非常简单的方式将左值引用转换为右值引用;


	Test Instance:
				int a = 0;
				ProcessValue(a);
				ProcessValue(std::move(a));
	Result:
				ProcessValue(int &) -Lvalue: 0
				ProcessValue(int &&) -Rvalue: 0


	swap函数的通用定义;
		template<typename T>
		swap(T & a, T & b)
		{
			T tmp (a);	// copy a to tmp
			a = b;		// copy b to a
			b = tmp;	// copy tmp to b
		}

	swap() function with std::move()
		template<typename T>
		swap(T & a, T & b)
		{
			T tmp(std::move(a));	//move a to tmp;
			a = std::move(b);		//move b to a;
			b = std::move(tmp);		//move tmp to b;

		}

/************************************************************************/

namespace nsSTLmove
{
	//void ProcessValue(int & i);
	//void ProcessValue(int && i);
	int main_STL_Rvalue_Reference();
}
/// 
/// 精确传递 perfect Forwarding;
///		精确传递;完美转发;精准转发;
/// 


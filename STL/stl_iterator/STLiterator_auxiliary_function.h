/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#pragma once

//void process_value(int & i);
//void process_value(int && i);
//void forward_value(int && i);



/// 
/// ת������Ķ���;
/// ʵ��ת�ƹ��캯����ת�Ƹ�ֵ����;
///		http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/
/// 
///		��ֵ����������֧��ת������ġ�ת��������Խ���Դ ( �ѣ�ϵͳ����� ) ��һ������ת�Ƶ���һ������;
///		�����ܹ����ٲ���Ҫ����ʱ����Ĵ����������Լ����٣��ܹ��������� C++ Ӧ�ó��������;
///		��ʱ�����ά�� ( ���������� ) ������������Ӱ��;
///
///		ת������Ϳ���������ԣ�������ļ��ļ����뿽���������ļ���һ��Ŀ¼��������һ��Ŀ¼ʱ���ٶȱȼ������ܶ�;
///		ͨ��ת�����壬��ʱ�����е���Դ�ܹ�ת�������Ķ�����;
///		�����е� C++ �����У����ǿ��Զ��忽�����캯���͸�ֵ����;
///		Ҫʵ��ת�����壬��Ҫ����ת�ƹ��캯���������Զ���ת�Ƹ�ֵ������;
///		������ֵ�Ŀ����͸�ֵ�����ת�ƹ��캯����ת�Ƹ�ֵ������;
///		���ת�ƹ��캯����ת�ƿ���������û�ж��壬��ô����ѭ���еĻ��ƣ��������캯���͸�ֵ�������ᱻ����;
///		
///		��ͨ�ĺ����Ͳ�����Ҳ����������ֵ���ò�����ʵ��ת������;
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


	����������;
	ʵ���˵��ÿ������캯��,������ֵ�������Ĳ���;
	MyString("Hello"),MyString("world")������ʱ����,Ҳ����ֵ;

	��Ȼ����ʱ��,������Ȼ�����˿�������Ϳ�����ֵ,���û���������Դ������ͷŵĲ���;
	����ܹ�ֱ��ʹ����ʱ�����Ѿ��������Դ,��Ƚ�ʡ��Դ�ֽ�ʡ��Դ�ٴ�������ͷŵ�ʱ��;

	�������Ƕ���ת������ı�Դ����;

	Test Instance:
				same with codes above wholly;
	Result:
	// after definition of Move Copy and Move Assignment...
				Move Assignment is called : source : Hello
				Move Constructor is called : source : world
	��������������ֵ����ֵ������ֵ������ת�ƹ����ת�Ƹ�ֵ��,��ʡ��Դ��������е�Ч��;
	������ֵ���ú�ת�����壬����ƺ�ʵ����ʱ;
	������Ҫ��̬���������Դ���࣬Ӧ�����ת�ƹ��캯����ת�Ƹ�ֵ�����������Ӧ�ó����Ч��;

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
	/// ���ȶ���ת�ƹ��캯��;
	/// ����(��ֵ����)�ķ��ű�������ֵ���÷���, �� /&&/;
	/// ����(��ֵ����)�������ǳ���, ��Ϊ�˴���Ҫ�޸���ֵ, ���������� (const MyString && str);
	/// ����(��ֵ����)����Դ���Ӻͱ�Ǳ����޸�,������ֵ�����������ͻ��ͷ���Դ,ת�Ƶ��¶������Դ����Ч��;
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
	/// ��ζ���ת�Ƹ�ֵ������;
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
	��׼�⺯�� std::move
		��Ȼ������ֻ����ֵ���ò��ܵ���ת�ƹ��캯����ת�Ƹ�ֵ��������������������ֻ������ֵ����;
		�����֪һ�����������ٱ�ʹ�ö����������ת�ƹ��캯����ת�Ƹ�ֵ����;

		Ҳ���ǰ�һ����ֵ���õ�����ֵ������ʹ�ã���ô����;��
		��׼���ṩ�˺��� std::move ;
		��������Էǳ��򵥵ķ�ʽ����ֵ����ת��Ϊ��ֵ����;


	Test Instance:
				int a = 0;
				ProcessValue(a);
				ProcessValue(std::move(a));
	Result:
				ProcessValue(int &) -Lvalue: 0
				ProcessValue(int &&) -Rvalue: 0


	swap������ͨ�ö���;
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
/// ��ȷ���� perfect Forwarding;
///		��ȷ����;����ת��;��׼ת��;
/// 


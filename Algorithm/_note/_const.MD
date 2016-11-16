/*****************************************************************
	
*****************************************************************/
/// 
/// http://lib.csdn.net/article/cplusplus/30981
///

	const迭代器，顾名思义，就是不能改变的迭代器，是常量，其性质是由const决定的。
	比如说我们这样定义一个const迭代器。
	[cpp] view plaincopy
					vector<int> vv(10,9);  
					const vector<int> :: iterator iter = vv.begin();  
	则，当程序中出现这样的语句时是错误的

	[cpp] view plaincopy
					++iter;  

	其原因是iter是一个常量，因此是不能改变的。
	换句话说，iter只能指向vv的地一个元素，不能指向其他的元素。
	但是这样的语句是正确的：

	[cpp] view plaincopy
					×iter = 10;  

	因为虽然iter不能指向其他的元素，但是其指向的第一个元素的值是可以改变的。
	而对于const_iterator来说的话，正好相反。比如我们这样定义

	[cpp] view plaincopy
					vector<int> vv(10,9);  
					vector<int> :: const_iterator iter;  

	即定义了一个const_iterator迭代器。
	这个迭代器是可以自己增加的，但是其所指向的元素是不可以被改变的。
	比如说

	[cpp] view plaincopy
					for(iter = vv.begin(); iter != vv.end(); ++iter){  
						cout << *iter << endl;  
					}  

	这样是正确的，即iter本身的值是可以改变的。但是

	[cpp] view plaincopy
					for(iter = vv.begin(); iter != vv.end(); ++ iter){  
					   *iter = 0;  
					}  

	这样是不对的，因为const_iterator迭代器是不能改变其所指向的元素的值的。

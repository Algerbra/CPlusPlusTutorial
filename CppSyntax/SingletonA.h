/************************************************************************/
/*                                                                      */
/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#pragma once

#include <iostream>
/************************************************************************
  C++ /Singleton/
  Limitation: Single Threaded Design
  See: http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
       For problems associated with locking in multi threaded applications
 
  Limitation:
  If you use this Singleton (A) within a destructor of another Singleton (B)
  This Singleton (A) must be fully constructed before the constructor of (B)
  is called
/************************************************************************/
class SingletonA
{
public:

	static SingletonA & getInstance()
	{
		//The only instance;
		//guaranteed to be lazy initialized;
		//guaranteed that it will be destroyed correctly;
		static SingletonA aInstance;
		return aInstance;
	}

private:
	SingletonA(){ fprintf(stderr, "** SingletonA::SingletonA() \n"); }
	SingletonA(SingletonA const & rth);//without implemented
	SingletonA & operator = (SingletonA const & rth);//without implemented

};


/// /Singleton/
/************************************************************************

  C++ /Singleton/
  @brief [Limitation]

	In a single-threaded environment,
	-	this generally works fine, though interrupts can be problematic;

	Unfortunately,
	-	this implementation is not reliable in a multi-threaded environment;

	http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf


	Suppose that Thread A enters the instance function, executes through Line 14, and is then suspended.
	
	At the point where it is suspended, it has just determined that pInstance is null,
	- i.e., that no Singleton object has yet been created.

	Thread B now enters instance and executes Line 14.
	It sees that pInstance is null, so it proceeds to Line 15 and creates a Singleton for pInstance
	- to point to. It then returns pInstance to instance¡¯s caller.

	At some point later, Thread A is allowed to continue running, and the first thing it does is move to Line 15,
	- where it conjures up another Singleton object and makes pInstance point to it. 
	
	It should be clear that this violates the meaning of a singleton, as there are now two Singleton objects.
/************************************************************************/
class SingletonAa
{
public:
	static SingletonAa * instance()
	{
		if (0 == pInstance)
			pInstance = new SingletonAa;

		return pInstance;
	}

	~SingletonAa(){ delete pInstance; }
private:
	static SingletonAa * pInstance;

private:
	SingletonAa(){ fprintf(stderr, "** SingletonAa::SingletonAa()  \n"); }
	SingletonAa(const SingletonAa & rth);
	SingletonAa & operator = (const SingletonAa & rth);
};


/// [*] volatile  //http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
/// [*] memory-mapped I/O (MMIO)  //http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf


/// [*] explicit
/************************************************************************
	
	http://en.cppreference.com/w/cpp/language/explicit

	explicit specifier
	
	C++  C++ language  Classes
	The explicit specifier specifies that a constructor or conversion function
	(since C++11) doesn't allow implicit conversions or copy-initialization. 
	It may only appear within the decl-specifier-seq of the declaration of
	such a function within its class definition.


/************************************************************************/


/// /Singleton/
/************************************************************************

	http://stackoverflow.com/questions/270947/can-any-one-provide-me-a-sample-of-singleton-in-c/271104#271104
	Why does everybody want to return a singleton as a pointer?
	
	Return it as a reference seems much more logical!

	You should never be able to free a singleton manually.
	How do you know who is keeping a reference to the singleton? 
	If you don't know (or can't guarantee) nobody has a reference
	(in your case via a pointer) then you have no business freeing the object.

	Use the static in a function method.
	This guarantees that it is created and destroyed only once. 
	It also gives you lazy initialization for free.

/************************************************************************/
class SingletonAb
{
public:
	static SingletonAb & getInstance()
	{
		static SingletonAb instanceAb;
		return instanceAb;
	}

private:
	SingletonAb(){ fprintf(stderr, "** SingletonAb::SingletonAb()  \n"); };
	SingletonAb(const SingletonAb & rth);//don't implementated;
	SingletonAb & operator = (const SingletonAb & rth);//don't implemented;

	~SingletonAb(){ fprintf(stderr, "** SingletonAb::~SingletonAb()  \n"); }
};


namespace nsSingletonA
{
	int main_SingletonA();
}
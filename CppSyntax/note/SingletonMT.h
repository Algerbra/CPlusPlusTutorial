/************************************************************************
C++ Class Design Example

http://code.runnable.com/Utbjy6sVG-00AAEv/c%2B%2B-class-design-example-singleton


/************************************************************************/
///  >> 11/16/8/2016 BY.gaohuancai QQ1293302539 <<
#include <stdio.h>
#include <iostream>

class Mutex
{
	//placeholder for code to create, and free a mutex;
};

class Lock
{
public:
	Lock(Mutex & rm) :mutex(rm)//placeholder code to acquire the mutex;
	{}

	~Lock(){}//placeholder code to release the mutex;

private:
	Mutex & mutex;
};

class SingletonMT
{
public:
	static SingletonMT * getInstance();

	int a;
	~SingletonMT(){ fprintf(stderr, "SingletonMT::~SingletonMT()"); }

private:
	SingletonMT(int a_int) :a(a_int)
	{ fprintf(stderr, "SingletonMT::SingletonMT(int a_int)"); }

	static Mutex mutex;


	SingletonMT(const SingletonMT & rth);//unimplemented to preventing copying;
	SingletonMT & operator = (const SingletonMT & rth);//unimplemented to preventing copying;
};



///////

Mutex SingletonMT::mutex;

SingletonMT * SingletonMT::getInstance()
{
	Lock lock(mutex);
	fprintf(stderr, " SingletonMT::getInstance()\n");

	//initialized during first access;
	static SingletonMT instancemt(1);
	return &instancemt;
}


/************************************************************************
  
  Reference
  [cpp/container/priority_queue]
	http://en.cppreference.com/w/cpp/container/priority_queue



/************************************************************************/
///  >> 11/26/12/2016 BY.gaohuancai QQ1293302539 <<
#include "us_PriorityQueue.h"

#include <queue>
#include <vector>
#include <string>

namespace nsus_PriorityQueue
{
	/************************************************************************

	  Reference \ Conception
	  http://en.cppreference.com/w/cpp/container/priority_queue
		A priority queue is a container adaptor that provides constant time
		lookup of the largest (by default) element, at the expense of logarithmic
		insertion and extraction..

		A user-provided Compare can be supplied to change the ordering, 
		e.g. using std::greater<T> would cause the smallest element to appear
		as the top()..

	/************************************************************************/


	/************************************************************************
	  References \ Code
	    http://stackoverflow.com/questions/19535644/how-to-use-the-priority-queue-stl-for-objects

	/************************************************************************/

	class Person
	{
		friend struct LessThanBySalary;

		friend bool operator < (const Person& lhs, const Person& rhs)
		{
			return (lhs._iAge < rhs._iAge);
		}

	public:
		Person(int a_iAge = 18, float a_fSalary = 0.0f, std::string a_sName = "pName")
			: _iAge(a_iAge), _fSalary(a_fSalary), _sName(a_sName)
		{}

		void showInfo(void)
		{
			fprintf(stderr, "\t [name] %s    [age] %d    [salary] %f\n"
							, _sName.c_str() , _iAge , _fSalary);
		}

	private:
		int _iAge;
		float _fSalary;
		std::string _sName;
	};


	struct LessThanBySalary
	{
		bool operator () (const Person & lhs, const Person & rhs)const
		{
			return (lhs._fSalary < rhs._fSalary);
		}
	};

	/// ///////////////////////////////////////////////////////////////////////
	/// Reference:
	/// http://en.cppreference.com/w/cpp/container/priority_queue (Example)

	template<typename T>
	void print_queue(T & q)
	{
		while (!q.empty())
		{
			//fprintf(stderr, ")
			q.top().showInfo();
			q.pop();
		}
		fprintf(stderr, "\n\n");
	}




	/// ///////////////////////////////////////////////////////////////////////
	/// 
	int main_us_PriorityQueue()
	{
		std::vector<Person> colP =
		{
			  Person(21, 10000.0f, "Jack")
			, Person(34, 40000.0f, "Mick")
			, Person(19, 50000.0f, "Alle")
			, Person(29, 110000.0f, "Coco")
			, Person(49, 1000000.0f, "Allo")
			, Person(12, 210000.0f, "Algo")
		};


		// bool LessThanBySalary::operator() (const Person & lhs, const Person & rhs)const;
		std::priority_queue<Person, std::vector<Person>, LessThanBySalary> userDefPQueue;
		// bool operator < (const Person & , const Person & );
		std::priority_queue < Person > stllessPQueue;
		std::vector<Person>::iterator itv = colP.begin();
		while (colP.end() != itv)
		{
			stllessPQueue.push(*itv);
			userDefPQueue.push(*itv);
			++itv;
		}

		print_queue(userDefPQueue);
		
		print_queue(stllessPQueue);

		fprintf(stderr, " %d \n", 45 < 12);
		return 0;
	}
}


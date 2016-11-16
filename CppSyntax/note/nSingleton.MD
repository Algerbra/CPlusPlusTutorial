/****************************************************************************************/
/*																						*/
*****************************************************************************************/
///
/// [/Singleton/] : How should it be used ?
/// http://stackoverflow.com/questions/86582/singleton-how-should-it-be-used

//note0
Singletons give you the ability to combine two bad traits in one class.
That's wrong in pretty much every way.

A singleton gives you:

	[0]	Global access to an object, and
	[1]	A guarantee that no more than one object of this type
		can ever be created Number one is straightforward.

Globals are generally bad.
We should never make objects globally accessible unless we really need it.


//[note1]
The problem with singletons is not their implementation. 
It is that they conflate two different concepts, 
neither of which is obviously desirable.

	1)  Singletons provide a global access mechanism to an object. 
		Although they might be marginally more threadsafe or marginally more reliable in languages without
		a well-defined initialization order, this usage is still the moral equivalent of a global variable.
		It's a global variable dressed up in some awkward syntax (foo::get_instance() instead of g_foo, say),
		but it serves the exact same purpose (a single object accessible across the entire program) and
		has the exact same drawbacks.

	2)	Singletons prevent multiple instantiations of a class.
		It's rare, IME, that this kind of feature should be baked into a class.
		It's normally a much more contextual thing; a lot of the things that are regarded as one-and-only-one
		are really just happens-to-be-only-one. IMO a more appropriate solution is to just create only one
		instance--until you realize that you need more than one instance.


/****************************************************************************************/
/*																						*/
*****************************************************************************************/
///
/// [/explicit/] : what does the explicit keyword in c/c++ mean?
/// http://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-in-c-mean

//note0
In C++, the compiler is allowed to make one implicit conversion to resolve the parameters to a function.
What this means is that the compiler can use constructors callable with a single parameter to
convert from one type to another in order to get the right type for a parameter.

Here's an example class with a constructor that can be used for implicit conversions:

				class Foo
				{
				public:
					Foo(int a_int) : m_int(a_int)
					{}

					int getInt()
					{return m_int;}

				private:
					int m_int;
				}

				void doBar(Foo foo)
				{
					int i = foo.getInt();
				}

				int main()
				{
					doBar(42);
				}

Prefixing the explicit keyword to the constructor prevents the compiler from using that
constructor for implicit conversions. Adding it to the above class will create a compiler error
at the function call DoBar (42).
It is now necessary to call for conversion explicitly with  DoBar (Foo (42))

The reason you might want to do this is to avoid accidental construction that can hide bugs.



/****************************************************************************************/
/*																						*/
*****************************************************************************************/
///
/// [/volatile/] : why do we use volatile keyword in c/c++?
/// http://stackoverflow.com/questions/4437527/why-do-we-use-volatile-keyword-in-c

//note0
Consider this code,

				int some_int = 100;

				while(some_int == 100)
				{
				   //your code
				}
When this program gets compiled, the compiler may optimize this code, if it finds that the program 
never ever makes any attempt to change the value of some_int, so it may be tempted to optimize the while loop
by changing it from while(some_int == 100) to simply while(true) so that the execution could be fast 
(since the condition in while loop appears to be true always). (if the compiler doesn't optimize it, 
then it has to fetch the value of some_int 
(if it's not loaded on a register) and compare it with 100,each time which obviously is a little bit slow.)

However, sometimes, optimization (of some parts of your program) may be undesirable, 
because it may be that someone else is changing the value of some_int from outside the program 
which compiler is not aware of, since it can't see it; but it's how you've designed it. 
In that case, compiler's optimization would not produce the desired result!

So, to ensure the desired result, you need to somehow stop the compiler from optimizing the while loop. 
That is where the volatile keyword plays it's role. 

	All you need to do is this,

				volatile int some_int = 100; //note the 'volatile' qualifier now!

///
In others words I would explain this as follows:

volatile tells the compiler that,

		"Hey compiler, I'm volatile and, you know, 
		I can be changed by some XYZ that you're not even aware of. 
		That XYZ could be anything. Maybe some alien outside this planet called program. 
		Maybe some lighting, some form of interrupt, volcanoes, etc can mutate me. 
		Maybe. You never know who is going to change me! 
		So O you ignorant, stop playing an all-knowing god, 
		and don't dare touch the code where I'm present. Okay?"

Well, that is how volatile prevents compiler from optimizing code. 
Now google it to see some sample examples.

Quoting from the C++ Standard ($7.1.5.1/8)

[..]	volatile is a hint to the implementation to avoid aggressive optimization 
		involving the object because the value of the object might be changed 
		by means undetectable by an implementation.
[...]


///note1
///http://stackoverflow.com/questions/72552/why-does-volatile-exist
///

volatile is needed if you are reading from a spot in memory that, 
say, a completely separate process/device/whatever may write to.

I used to work with dual-port ram in a multiprocessor system in straight C. 
We used a hardware managed 16 bit value as a semaphore to know 
when the other guy was done. Essentially we did this:

				void waitForSemaphore()
				{
				   volatile uint16_t* semPtr = WELL_KNOWN_SEM_ADDR;/*well known address to my semaphore*/
				   while ((*semPtr) != IS_OK_FOR_ME_TO_PROCEED);
				}
Without volatile, the optimizer sees the loop as useless 
(The guy never sets the value! He's nuts, get rid of that code!) and 
my code would proceed without having acquired the semaphore, causing problems later on.

///note2 
/// http://stackoverflow.com/questions/4479597/does-making-a-struct-volatile-make-all-its-members-volatile/4479652
///

Another question can be asked (or simply another way to look at the original question):
Does making a struct const make all its members const?

		If I have:

				struct whatever { int data; };

				const whatever test;

		Will test.data be const too?

My answer is : Yes. 
If you declare an object of type whatever with const then all its members will be const too Similarly, 
if you declare an object of type whatever with volatile then all its members will be volatile too, 
just like if you declare the object with const, all it's member will be const too.

const and volatile are two faces of the same coin; 
they're so that the Standard often refers to them as cv-qualifiers.

		Quoting from the Standard ($7.1.5.1/8)

				[Note: volatile is a hint to the implementation to avoid aggressive optimization 
					involving the object because the value of the object might be changed 
					by means undetectable by an implementation. See 1.9 for detailed semantics. 
					In general, the semantics of volatile are intended to be the same in C + + as they are in C.
				]

That means, if your object is an instance of a struct, 
then the compiler cannot avoid aggressive optimization involving the object, 
unless it avoids aggressive optimization of each of it's members. 
(Otherwise, how else it can avoid optimization involving the object?)

///																													///
///																													///
///_________________________________________________________________________________________________________________///
///																													///
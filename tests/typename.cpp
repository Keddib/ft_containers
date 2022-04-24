#include <iostream>

template<typename T>

class Trap {
	public:
		enum{x};
};

template<typename T>
class Victim {
	public:
		int y;
		// (1) x is not a type here
		void poof() {
			Trap<T>::x * y << '\n'; // (2) declaration or multiplication?
		}
};

template<>
class Trap<void> { // evil specialization! // (3) x is a type here
	public:
		typedef int x;
};

void boom(Victim<void>& bomb)
{
	bomb.poof();
}

/* As the compiler is parsing line (2), it must decide whether it is seeing a declaration or a multiplication.
This decision in turn depends on whether the dependent qualified name Trap<T>::x is a type name.
It may be tempting to look in the template Trap at this point and find that, according to line (1), Trap<T>::x is not a type, which would leave us to believe that line (2) is a multiplication.
However, a little later the source corrupts this idea by overriding the generic X<T>::x for the case where T is void. In this case, Trap<T>::x is in fact type int.
The language definition resolves this problem by specifying that in general a dependent qualified name does not denote a type unless that name is prefixed with the keyword typename.
If it turns out, after substituting template arguments, that the name is not the
name of a type, the program is invalid and your C++ compiler should complain at instantiation time. Note that this use of typename is different from the use to denote template type parameters.
Unlike type parameters, you cannot equivalently replace typename with class. The typename prefix to a name is required when the name :
1. Appears in a template
2. Is qualified
3. Is not used as in a list of base class specifications or in a list of member initializers introducing a constructor definition
4. Is dependent on a template parameter
Furthermore, the typename prefix is not allowed unless at least the first three previous
conditions hold. To illustrate this, consider the following erroneous example [5]:
[5] From [VandevoordeSolutions], proving once and for all that C++ promotes code
reuse. */

/* template<typename T>
struct S: typename X<T>::Base {
	S(): typename X<T>::Base(typename X<T>::Base(0)) {}
	typename X<T> f() {
		typename X<T>::C * p; // declaration of pointer p
		X<T>::D * q;
	}
	typename X<int>::C * s;
};

struct U {
	typename X<int>::C * pc;
}; */


/* Each occurrence of typename—correct or not—is numbered with a subscript for easy reference.
The first, typename1, indicates a template parameter.
The previous rules do not apply to this first use.
The second and third typenames are disallowed by the third item in the previous rules.
Names of base classes in these two contexts cannot be preceded by typename. However, typename4 is required.
Here, the name of the base class is not used to denote what is being initialized or derived from.
Instead, the name is part of an expression to construct a temporary X<T>::Base from its argument 0 (a sort
of conversion, if you will).
The fifth typename is prohibited because the name that follows it, X<T>, is not a qualified name.
The sixth occurrence is required if this statement is to declare a pointer.
The next line omits the typename keyword and is, therefore, interpreted by the compiler as a multiplication.
The seventh typename is optional because it satisfies all the previous rules except the last.
Finally, typename8 is prohibited because it is not used inside a template. */




int main(){
	Victim<void> x;
	boom(x);
	return 0;
}

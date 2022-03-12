#include "stack.hpp"
#include <iostream>
#include <string>
#include <list>
#include <stack>

int main()
{

	ft::stack<int, std::list<int> >					intStack;
	ft::stack<std::string> 			stringStack;

	// manipulate int stack
	intStack.push(7);
	std::cout << intStack.top() << std::endl;

	// manipulate string stack
	stringStack.push("hello");
	std::cout << stringStack.top() << std::endl;
	stringStack.pop();
	// stringStack.pop();
}

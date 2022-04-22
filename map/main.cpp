#include <iostream>

#include "map.hpp"
#include <map>

int main() {

{
	ft::map<int, std::string> map;
	typedef ft::map<int, std::string>::iterator iter;
	map.insert( ft::make_pair(1, std::string("hello")) );

	iter it1 = map.find(1);
	if (it1 != map.end())
		std::cout << it1->first << it1->second << '\n';
}

	return 0;
}

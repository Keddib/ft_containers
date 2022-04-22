#include <iostream>

#include "map.hpp"
#include <map>

int main() {

	ft::map<int, std::string> map;
	typedef ft::map<int, std::string>::iterator iter;
	map.insert( std::make_pair(1, std::string("hello")) );

	iter it1 = map.find(10);
	if (it1 != map.end())
		std::cout << it1->first << it1->second << '\n';




	std::map<char,int> mymap;
  std::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;

  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('f');  // itlow points to b
  std::cout << itlow->first << '\n';

	return 0;
}

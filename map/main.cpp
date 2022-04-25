#include <iostream>
#include "map.hpp"
#include <vector>
#include <map>
#include <utility>



int _ratio = 10000;


int main (void)
{

{
    // std
    std::vector<int> v;
    std::map<int, int> mp;
    mp.insert(std::make_pair(10, 10));
    mp.insert(std::make_pair(20, 20));
    mp.insert(std::make_pair(30, 30));
    mp.insert(std::make_pair(40, 40));
    mp.insert(std::make_pair(50, 50));
    mp.insert(std::make_pair(60, 60));
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair = mp.equal_range(10);
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second->first);
    v.push_back(pair.second->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second->first);
    v.push_back(pair2.second->second);
    v.push_back(pair3.first->first);
    v.push_back(pair3.first->second);
    v.push_back(pair3.second->first);
    v.push_back(pair3.second->second);
}

{

    std::vector<int> v;
    ft::map<int, int> mp;

    mp.insert(ft::make_pair(10, 10));
    mp.insert(ft::make_pair(20, 20));
    mp.insert(ft::make_pair(30, 30));
    mp.insert(ft::make_pair(40, 40));
    mp.insert(ft::make_pair(50, 50));
    mp.insert(ft::make_pair(60, 60));
    const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair = mp.equal_range(10);
    const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
    const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second->first);
    v.push_back(pair.second->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second->first);
    v.push_back(pair2.second->second);
    v.push_back(pair3.first->first);
    v.push_back(pair3.first->second);
    v.push_back(pair3.second->first);
    v.push_back(pair3.second->second);
}

    return 0;
}

#include <iostream>

#include "map.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>


template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

int main() {

        bool cond;
        std::map<char, int> m;
        ft::map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::map<char, int>::iterator ft_it;

        // insert some values:
        ft_m['a'] = 10;
        ft_m['b'] = 20;
        ft_m['c'] = 30;
        ft_m['d'] = 40;
        ft_m['e'] = 50;
        ft_m['f'] = 60;

        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 30;
        m['d'] = 40;
        m['e'] = 50;
        m['f'] = 60;

        cond = m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());
        std::cout << (cond ? "valid" : "invalid") << std::endl;

        it = m.find('b');
        ft_it = ft_m.find('b');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
        std::cout << (cond ? "valid" : "invalid") << std::endl;
        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());
        std::cout << (cond ? "valid" : "invalid") << std::endl;

        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key

        cond = cond && ret == ft_ret && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());
        std::cout << (cond ? "valid" : "invalid") << std::endl;

        it = m.find('e');
        ft_it = ft_m.find('e');

        std::cout << it->first << '\n';
        std::cout << it->second << '\n';
        std::cout << m.size() << '\n';
        std::cout << ft_it->first << '\n';
        std::cout << ft_it->second << '\n';
        std::cout << ft_m.size() << std::endl;

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();
        std::cout << (cond ? "valid" : "invalid") << std::endl;

        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

        cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());
        std::cout << (cond ? "valid" : "invalid") << std::endl;


	return 0;
}

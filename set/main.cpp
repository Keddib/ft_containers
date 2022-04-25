#include <iostream>
#include "set.hpp"
#include "../utils/pair.hpp"
#include <utility>
#include <set>
#include <vector>

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  ft::set<int> st;

    std::vector<int> v;
    ft::pair<ft::set<int>::iterator, bool> pair = st.insert(7);
    ft::set<int>::iterator it = st.begin();
    v.push_back(*it);

    v.push_back(*(pair.first));
    v.push_back(pair.second);
    st.insert(9);
    ft::pair<ft::set<int>::iterator , bool> pair2 = st.insert(9);
    ft::set<int>::iterator it2 = pair.first;
    v.push_back(*it2);
    v.push_back(*(pair2.first));
    v.push_back(pair2.second);
    for (int i = 0; i < 50 * 1000; ++i) {
        st.insert(i);
    }
     ft::set<int>::iterator it3 = st.begin();
    for (; it3 != st.end(); ++it3) {
        v.push_back(*it3);
    }
    v.push_back(st.size());
  return 0;
}

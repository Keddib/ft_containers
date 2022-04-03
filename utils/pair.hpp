#ifndef FT_PAIR_HPP
#define FT_PAIR_HPP

namespace ft {

template<typename T1, typename T2>
struct pair
{
	// types
	typedef T1 first_type;
	typedef T2 second_type;
	// memeber variables
	first_type first;
	second_type second;

	// constructors

	pair(); // defualt

	pair (const first_type& a, const second_type& b) // initialization
	: first(a), second(b) {}

	template<class U, class V>
	pair (const pair<U,V>& pr) // copy
	: first(pr.first), second(pr.second) {}

	pair& operator = (const pair& pr) {
		first = pr.first;
		second = pr.second;
		return *this;
	}
};



template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}


template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(lhs == rhs);
}


template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}


template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(rhs < lhs);
}


template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return (rhs < lhs);
}


template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
	return !(lhs < rhs);
}

// make pair

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}


}

#endif

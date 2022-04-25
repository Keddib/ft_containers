#ifndef FT_VITERATOR_HPP
#define FT_VITERATOR_HPP

#include <iterator>

namespace ft {

template <typename T>
class Iterator: public std::iterator <std::random_access_iterator_tag, T> {

	public:

		typedef T																						value_type;
		typedef typename std::iterator<std::random_access_iterator_tag, value_type>::pointer			pointer;
		typedef typename std::iterator<std::random_access_iterator_tag, value_type>::reference			reference;
		typedef typename std::iterator<std::random_access_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename std::iterator<std::random_access_iterator_tag, value_type>::iterator_category	iterator_category;

		private:
			pointer _p;

		public:
			Iterator(pointer p = 0x00) : _p(p) {}

			Iterator( const Iterator &other) : _p(other._p) {}

			~Iterator() { _p = nullptr; }

			Iterator& operator = (const Iterator &other ) {
				_p = other._p;
				return *this;
			}


			reference operator * () const{
				return *_p;
			}

			reference operator [] (size_t n) {
				return *(_p + n);
			}

			pointer operator -> () const{
				return _p; // (iter.operator->())->member_func();
			}

			// pre-increment and pre-decrement
			pointer	operator ++ ( void ) {
				_p++;
				return _p;
			}
			pointer	operator -- ( void ) {
				_p--;
				return _p;
			}

			// post-increment and post-decrement
			pointer operator ++ ( int ) {
				pointer tmp = _p;
				++_p;
				return tmp;
			}
			pointer operator -- ( int ) {
				pointer tmp = _p;
				--_p;
				return tmp;
			}

			difference_type operator - (const Iterator& iter) const {
				return _p - iter._p;
			}

			Iterator operator - (difference_type n) const {
				return Iterator (_p - n);
			}

			Iterator operator + (difference_type n) const {
				return Iterator (_p + n);
			}

			friend Iterator operator + (difference_type n, const Iterator& iter) {
				return Iterator (iter._p + n);
			}

			Iterator& operator += (difference_type n) {
				_p += n;
				return *this;
			}

			Iterator& operator -= (difference_type n) {
				_p -= n;
				return *this;
			}

			bool operator == (const Iterator& iter) { return _p == iter._p; }
			bool operator != (const Iterator& iter) { return _p != iter._p; }
			bool operator < (const Iterator& iter) { return _p < iter._p; }
			bool operator > (const Iterator& iter) { return _p > iter._p; }
			bool operator <= (const Iterator& iter) { return _p <= iter._p; }
			bool operator >= (const Iterator& iter) { return _p>= iter._p; }

			// operator for conversion from 'Iterator<int>' to Iterator<const int>'
			operator Iterator<const T> () {
				return (const pointer)_p;
			}
	};

} // ft

#endif

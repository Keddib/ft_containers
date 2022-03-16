#ifndef FT_VITERATOR_HPP
#define FT_VITERATOR_HPP

#include <iterator>

namespace ft {

	template <typename T>
	class Iterator {
		public:
			//types
			typedef ptrdiff_t								difference_type;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef std::random_access_iterator_tag			iterator_category;

		private:
			pointer _p;

		public:
			Iterator(pointer p = 0) : _p(p) {}

			Iterator( const Iterator &other) : _p(other._p) {}

			~Iterator() { _p = nullptr; }

			Iterator& operator = (const Iterator &other ) {
				_p = other._p;
				return *this;
			}

			bool operator == (const Iterator &other ) {
				return _p == other._p;
			}
			bool operator != (const Iterator &other ) {
				return ! (_p == other._p);
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

			pointer operator + ( size_t n) {
				return _p + n;
			}
			pointer operator += ( size_t n) {
				return _p += n;
			}
			pointer operator - ( size_t n) {
				return _p - n;
			}
			pointer operator -= ( size_t n) {
				return _p -= n;
			}
			friend pointer operator + (size_t n, const Iterator &iter) {
				return iter._p + n;
			}
			difference_type operator - (const Iterator &other) {
				return _p - other._p;
			}

			bool operator < (const Iterator &other) {
				return _p < other._p;
			}
			bool operator > (const Iterator &other) {
				return other._p < _p;
			}
			bool operator <= (const Iterator &other) {
				return !(other._p > _p);
			}
			bool operator >= (const Iterator &other) {
				return !(_p < other._p);
			}
			// operator for conversion from 'Iterator<int>' to Iterator<const int>'
			operator Iterator<const T> () {
				return (const pointer)_p;
			}
	};

} // ft

#endif

#ifndef FT_VITERATOR_HPP
#define FT_VITERATOR_HPP

namespace ft {

	template <typename T>
	class iterator {
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
			iterator(pointer p = 0) : _p(p) {}

			iterator( const iterator &other) _p(other._p) {}

			~iterator() { _p = nullptr; }

			iterator& operator = (const iterator &other ) {
				_p = other._p;
				return *this;
			}

			bool operator == (const iterator &other ) {
				return _p == other._p;
			}
			bool operator != (const iterator &other ) {
				return ! (_p == other._p);
			}
			reference operator * (const iterator &other ) const{
				return *_p;
			}

			reference operator [] (size_t n) {
				return *(_p + n);
			}

			pointer operator -> (const iterator &other ) const{
				return _p; // (iter.operator->())->member_func();
			}

			// pre-increment and pre-decrement
			pointer	operator ++ ( void ) {
				_p++;
				return _p;
			}
			pointer	operator -- ( void ) {
				_p--
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
			friend pointer operator + (size_t n, const iterator &iter) {
				return iter._p + n;
			}
			pointer operator - (const iterator &other) {
				return iter._p - other._p;
			}

			bool operaotr < (const iterator &other) {
				return _p < other._p;
			}
			bool operaotr > (const iterator &other) {
				return _p > other._p;
			}
			bool operaotr <= (const iterator &other) {
				return _p <= other._p;
			}
			bool operaotr >= (const iterator &other) {
				return _p >= other._p;
			}
			// operator for conversion from 'iterator<int>' to iterator<const int>'
			operator iterator<const T> () {
				return (const pointer)_p;
			}
	};

} // ft

#endif
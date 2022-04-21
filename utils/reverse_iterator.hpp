#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

namespace ft {

template <class Iterator>
class reverse_iterator
{
	protected:
		Iterator _current;

	public:
		// types
		typedef typename std::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename std::iterator_traits<Iterator>::value_type			value_type;
		typedef typename std::iterator_traits<Iterator>::pointer				pointer;
		typedef typename std::iterator_traits<Iterator>::reference			reference;
		typedef typename std::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef Iterator 												iterator_type;

		reverse_iterator() : _current() {}

		explicit reverse_iterator(iterator_type x) : _current(x) {}

		template <class U>
		reverse_iterator(const reverse_iterator<U>& u): _current(u.base()) {}

		iterator_type base() const { return _current; } //explicit

		reference operator * () const {
			iterator_type it(_current);
			--it;
			return *it;
		}

		pointer operator -> ()const {
			iterator_type it(_current);
			--it;
			return it.operator->();
		}

		reverse_iterator& operator ++ () {
			--_current;
			return *this;
		}

		reverse_iterator  operator++(int) {
			iterator_type tmp(_current--);
			return reverse_iterator(tmp);
		}

		reverse_iterator& operator--() {
			++_current;
			return *this;
		}

		reverse_iterator  operator--(int) {
			iterator_type tmp(_current++);
			return reverse_iterator(tmp);
		}

		reverse_iterator  operator+ (difference_type n) const {
			return reverse_iterator(iterator_type(_current - n));
		}

		reverse_iterator& operator+=(difference_type n) {
			_current -= n;
			return *this;
		}

		reverse_iterator  operator - (difference_type n) const {
			return reverse_iterator(iterator_type(_current + n));
		}

		reverse_iterator& operator-=(difference_type n) {
			_current+= n;
			return *this;
		}

		reference operator[](difference_type n) const {
			return * (_current - n - 1);
		}

		friend bool operator== (const reverse_iterator& x, const reverse_iterator& y) {
			return x.base() == y.base();
		}

		friend bool operator < (const reverse_iterator& x, const reverse_iterator& y) {
			return x.base() > y.base();
		}
};


template <class Iterator>
bool operator != (const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
	return !(x == y);
}

template <class Iterator>
bool operator > (const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
	return (y < x);
}

template <class Iterator>
bool operator >=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
	return !(y > x);
}

template <class Iterator>
bool operator<=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
	return !(x > y);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator - (const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y){
	return y.base() - x.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
	return x + n;
}

} // ft


#endif

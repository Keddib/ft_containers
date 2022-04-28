#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "Iterator.hpp"
#include "../utility/iterator_traits.hpp"
#include "../utility/enable_if.hpp"
#include "../utility/lexicographical_compare.hpp"
#include "../utility/reverse_iterator.hpp"
#include <memory>
#include <algorithm>


namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector
{
	public:
		// types
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef Iterator<T>									iterator;
		typedef Iterator<const T>							const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		pointer				_elements;
		allocator_type		_alloc;
		size_type			_capacity;
		size_type			_size;

		// tag dispatching  called based on iterator type
		template <class InputIterator>
		int _range(InputIterator first, InputIterator last, std::random_access_iterator_tag) {
			return last - first;
		}
		template <class InputIterator>
		int _range(InputIterator first, InputIterator last, std::bidirectional_iterator_tag) {
			return std::distance(first, last);
		}
		template <class InputIterator>
		int _range(InputIterator , InputIterator , std::input_iterator_tag) {
			return -1;
		}

		template <class InputIterator> // _insert for range of input Iterators
		void _insert(iterator position, InputIterator first, InputIterator last) {
			vector<value_type> tmp(first, last);
			iterator begin = tmp.begin();
			size_type n = tmp.size();
			size_type pos = position - _elements;
			if (_size + n <= _capacity) {
				for (size_type i = _size - 1; i >= pos; --i) {
					if (i + n < _size)
						_elements[i + n] = _elements[i];
					else
						_alloc.construct(_elements + i + n, _elements[i]);
				}
				for (size_type i = pos; i < pos + n; i++) {
					if (i < _size)
						_elements[i] = *begin++;
					else
						_alloc.construct(_elements + i, *begin++);
				}
				_size += n;
			}
			else if (_size + n > _capacity) {
				size_type newCap = n > _size ? _size + n : _size * 2;
				pointer tmp = _alloc.allocate(newCap);
				for (size_type i = 0; i < pos; i++)
					_alloc.construct(tmp + i, _elements[i]);
				for (size_type i = pos; i < pos + n; i++)
					_alloc.construct(tmp + i, *begin++);
				for (size_type i = pos + n; i < _size + n; i ++)
					_alloc.construct(tmp + i, _elements[i - n]);
				size_type sz = _size;
				clear();
				_alloc.deallocate(_elements, _capacity);
				_capacity = newCap;
				_elements = tmp;
				_size = sz + n;
			}
		}

	public:

		// 23.2.4.1 construct/copy/destroy:
		explicit vector(const allocator_type &alloc = allocator_type())
		: _elements(NULL), _alloc(alloc), _capacity(0), _size(0) {}

		explicit vector(size_type n, const_reference value = value_type(), const allocator_type &alloc = allocator_type())
		: _elements(NULL), _alloc(alloc), _capacity(n), _size(n)
		{
			_elements = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_elements + i, value);
		}

		template <class InputIterator> // enable_if
		vector (InputIterator first, typename enable_if<Type<typename std::iterator_traits<InputIterator>::iterator_category>::val, InputIterator>::type last, const Allocator& alloc = Allocator())
		: _elements(NULL), _alloc(alloc), _capacity(0), _size(0)
		{
			int dis = _range(first, last, typename std::iterator_traits<InputIterator>::iterator_category() );
			if (dis != -1) {
				_capacity = last - first;
				_elements = _alloc.allocate(_capacity);
			}
			while (first != last)
				push_back (*first++);
		}

		vector(const vector& x)
		: _alloc(x._alloc), _capacity(x._capacity), _size(x._size) {
			_elements = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_elements + i, x._elements[i]);
		}

		~vector() {
			clear();
			if (_elements)
				_alloc.deallocate(_elements, _capacity);
		}

		vector<T,Allocator>& operator=(const vector& x)
		{
			if (this != &x) {
				clear();
				if (_elements)
					_alloc.deallocate(_elements, _capacity);
				_alloc = x._alloc;
				_capacity = x._capacity;
				_size = x._size;
				_elements = _alloc.allocate(_capacity);
				for(size_type i = 0; i < _size; i++)
					_alloc.construct(_elements + i, x._elements[i]);
			}
			return *this;
		}

		template <class InputIterator>
		void assign(InputIterator first, typename enable_if<Type<typename std::iterator_traits<InputIterator>::iterator_category>::val, InputIterator>::type last)
		{
			int n = _range(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
			clear();
			if (n > 0){
				if ((size_type)n > _capacity) {
					_alloc.deallocate(_elements, _capacity);
					_capacity = n;
					_elements = _alloc.allocate(_capacity);
				}
			}
			while (first != last)
				push_back (*first++);
		}

		void assign(size_type n, const_reference u) {
			clear();
			if (n > _capacity) {
				_alloc.deallocate(_elements, _capacity);
				_capacity = n;
				_elements = _alloc.allocate(_capacity);
			}
			for (; _size < n; _size++) {
				_alloc.construct(_elements + _size, u);
			}
		}

		allocator_type get_allocator() const { return _alloc; }

		// // iterators:
		iterator begin() { return iterator(_elements); }

		const_iterator begin() const { return const_iterator(_elements); }

		iterator end() {return iterator(_elements + _size); }

		const_iterator end() const { return const_iterator(_elements + _size); }

		reverse_iterator rbegin() { return reverse_iterator(_elements + _size); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(_elements + _size); }

		reverse_iterator rend() { return reverse_iterator(_elements ); }

		const_reverse_iterator rend() const { return const_reverse_iterator(_elements); }

		// 23.2.4.2 capacity:
		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

		void resize( size_type sz, value_type c = value_type() ) {

			if (sz < _size) {
				for (size_type i = sz; i < _size; i++)
					_alloc.destroy(_elements + i);
				_size = sz;
			} else if (sz <= _capacity) {
				for (; _size < sz; _size++)
					_alloc.construct( _elements + _size, c );
			} else {

				size_type cap = _capacity;
				while (_capacity < sz)
					_capacity *= 2;
				// reallocate one time;
				// _capacity = sz;
				pointer tmp = _alloc.allocate(_capacity);
				for (size_type i = 0; i < sz; i++) {
					if (i < _size)
						_alloc.construct(tmp + i, _elements[i]);
					else
						_alloc.construct(tmp + i, c);
				}
				clear();
				if (_elements)
					_alloc.deallocate(_elements, cap);
				_size = sz;
				_elements = tmp;
			}
		}

		size_type capacity() const { return _capacity; }

		bool empty()const { return !_size; }

		void reserve(size_type n) {
			if (n > _capacity) {
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, _elements[i]);
				size_type sz = _size;
				clear();
				_size = sz;
				if (_elements)
					_alloc.deallocate(_elements, _capacity);
				_capacity = n;
				_elements = tmp;
			}
		}

		// element access:
		reference operator[](size_type n) {
			return _elements[n];
		}

		const_reference operator[](size_type n) const {
			return _elements[n];
		}

		reference at(size_type n) {
			if (n >= _size)
				throw std::out_of_range("out of range") ;
			return _elements[n];
		}

		const_reference at(size_type n) const {
			if (n >= _size)
				throw std::out_of_range("out of range") ;
			return _elements[n];
		}

		reference front(){
			return _elements[0];
		}

		const_reference front() const{
			return _elements[0];
		}

		reference back() {
			return _elements[_size - 1];
		}

		const_reference back() const {
			return _elements[_size - 1];
		}

		// 23.2.4.3 modifiers:

		void push_back(const_reference x) {
			if (_capacity == 0) {
				_capacity = 1;
				_elements = _alloc.allocate(1);
			}
			if (_capacity > _size) {
				_alloc.construct(_elements + _size, x);
				_size++;
			} else {
				size_type old_capacity = _capacity;
				// reallocation
				_capacity *= 2;
				pointer tmp = _alloc.allocate( _capacity);
				// copy elements
				for(size_type i= 0; i < _size; i++)
					_alloc.construct(tmp + i, _elements[i]);
				// destroy all elements
				size_type n = _size;
				clear();
				_size = n;
				// deallocate elemnets
				_alloc.deallocate(_elements, old_capacity);
				_elements =  tmp;
				_alloc.construct(_elements + _size, x);
				_size++;
			}
		}

		void pop_back() {
			_alloc.destroy(_elements + (--_size));
		}

		iterator insert(iterator position, const_reference x) {
			size_type pos = position - _elements;
			push_back(x);

			value_type tmp = _elements[_size -1 ];
			for (size_type i = _size - 1; i > pos; i--) {
				_elements[i] = _elements[i - 1];
			}
			_elements[pos] = tmp;
			return iterator(_elements + pos);
		}

		void insert(iterator position, size_type n, const_reference x) {
			size_type pos = position - _elements;
			if (pos > _size)
				return ;
			if (_size + n <= _capacity) {
				for (size_type i = _size - 1; i >= pos; --i) {
					if (i + n < _size)
						_elements[i + n] = _elements[i];
					else
						_alloc.construct(_elements + i + n, _elements[i]);
				}
				for (size_type i = pos; i < pos + n; i++) {
					if (i < _size)
						_elements[i] = x;
					else
						_alloc.construct(_elements + i, x);
				}
				_size += n;
			}
			else if (_size + n > _capacity) {
				size_type newCap = n > _size ? _size + n : _size * 2;
				pointer tmp = _alloc.allocate(newCap);
				for (size_type i = 0; i < pos; i++)
					_alloc.construct(tmp + i, _elements[i]);
				for (size_type i = pos; i < pos + n; i++)
					_alloc.construct(tmp + i, x);
				for (size_type i = pos + n; i < _size + n ; i ++)
					_alloc.construct(tmp + i, _elements[i - n]);
				size_type sz = _size;
				clear();
				_alloc.deallocate(_elements, _capacity);
				_capacity = newCap;
				_elements = tmp;
				_size = sz + n;
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, typename enable_if<Type<typename std::iterator_traits<InputIterator>::iterator_category>::val, InputIterator>::type last)
		{
			size_type pos = position - _elements;
			int dis = _range(first, last, typename std::iterator_traits<InputIterator>::iterator_category());
			if (pos > _size)
				return;
			if (dis < 0) // input iterator
				_insert(position, first, last);
			size_type n = dis;
			if (_size + n < _capacity) {
				for (size_type i = _size - 1; i >= pos; --i) {
					if (i + n < _size)
						_elements[i + n] = _elements[i];
					else
						_alloc.construct(_elements + i + n, _elements[i]);
				}
				for (size_type i = pos; i < pos + n; i++) {
					if (i < _size)
						_elements[i] = *first++;
					else
						_alloc.construct(_elements + i, *first++);
				}
				_size += n;
			}
			else if (_size + n >= _capacity) {
				size_type newCap = n > _size ? _size + n : _size * 2;
				pointer tmp = _alloc.allocate(newCap);
				for (size_type i = 0; i < pos; i++)
					_alloc.construct(tmp + i, _elements[i]);
				for (size_type i = pos; i < pos + n; i++)
					_alloc.construct(tmp + i, *first++);
				for (size_type i = pos + n; i < _size + n; i ++)
					_alloc.construct(tmp + i, _elements[i - n]);
				size_type sz = _size;
				clear();
				_alloc.deallocate(_elements, _capacity);
				_capacity = newCap;
				_elements = tmp;
				_size = sz + n;
			}

		}

		iterator erase(iterator position) {
			size_type pos = position - _elements;
			_alloc.destroy(_elements + pos);
			_alloc.construct( _elements + pos, _elements[pos + 1] );
			for (++pos; pos < _size - 1; pos++) {
				_elements[pos] = _elements[pos + 1];
			}
			_alloc.destroy(_elements + (--_size));
			return position;
		}

		iterator erase(iterator first, iterator last) {

			size_type rang = last - first;
			size_type pos = first - _elements;
			size_type count = _size;
			for (size_type i = 0; (i < rang && i < _size) ; i++)
			{
				_alloc.destroy(_elements + (pos + i) );
				if (rang + (pos + i) < _size)
					_alloc.construct(_elements + (pos + i), _elements[rang + pos + i] );
				--count;
			}

			for (size_type i = pos + rang; i < _size; i++)
			{
				_alloc.destroy(_elements + i);
				if (i + rang < _size)
					_alloc.construct(_elements + i, _elements[i + rang] );
				--count;
			}
			_size = (_size >= rang) ? _size - rang : pos;
			return first;
		}

		void swap(vector& other) {

			std::swap(_elements, other._elements);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
		}

		void clear() {

			for(size_type i= 0; i < _size; i++)
				_alloc.destroy(_elements + i);
			_size = 0;
		}
};

	template <class T, class Allocator>
	bool operator == (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin()));
	}

	template <class T, class Allocator>
	bool operator != (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return !(x == y);
	}

	template <class T, class Allocator>
	bool operator < (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class T, class Allocator>
	bool operator > (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (y < x);
	}

	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return !(x < y);
	}

	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return !(y < x);
	}

	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y){
		x.swap(y);
	}

} // ft

#endif

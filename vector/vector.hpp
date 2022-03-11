#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "v_iterator.hpp"
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
		typedef ft::V_iterator<T>							iterator;
		// typedef implementation-defined					const_iterator;
		// typedef std::reverse_iterator<iterator>			reverse_iterator;
		// typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		pointer				_elements;
		allocator_type		_alloc;
		size_type			_capacity;
		size_type			_size;

	public:

		// 23.2.4.1 construct/copy/destroy:
		explicit vector(const allocator_type &alloc = allocator_type())
		: _elements(NULL), _alloc(alloc), _capacity(1), _size(0)
		{
			_elements = _alloc.allocate(1);
		}

		explicit vector(size_type n, const value_typeT& value = value_type(), const allocator_type &alloc = allocator_type())
		: _elements(NULL), _alloc(alloc), _capacity(n), _size(n)
		{
			_elements = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_elements + i, value);
		}

		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last, const Allocator& = Allocator());

		vector(const vector& x)
		: _alloc(x._alloc), _capacity(x._capacity), _size(x._size) {
			_alloc.allocate(_capacity);
			for (size_type i = 0; i < _size)
				_alloc.construct(_elements + i, x._elements[i]);
		}

		~vector() {
			clear();
			_alloc.deallocate(_elements, _capacity);
		}

		vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
		{
			if (this != &x) {
				clear();
				_alloc.deallocate(_elements, _capacity);
				_alloc = x._alloc;
				_capacity = x._capacity;
				_size = x._size;
				_elements = _alloc.allocate(_capacity);
				for(size_type i = 0; i < _size; i++)
					_elements[i] = x._elements[i];
			}
		}

		// template <class InputIterator>
		// void assign(InputIterator first, InputIterator last);

		void assign(size_type n, const T& u) {
			// rethink
			size_t i = 0;
			for (; i < _size; i++) {
				if (i < n)
					_elements[i] = u;
				else
				{
					_alloc.destroy(_elements + i);
					_size--;
				}
			}
			for (; i < n; i++)
				push_back(u);
		}

		allocator_type get_allocator() const { return _alloc; }

		// // iterators:
		// iterator begin();
		// const_iterator begin()const;
		// iterator end();
		// const_iterator end()const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;

		// 23.2.4.2 capacity:
		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

		void resize( size_type sz, T c = T() ) {

			if (sz < _size) {
				for (; sz < _size; sz++)
					_alloc.destroy(_elements + sz);
			} else if (sz < _capacity) {
				for (size_type i = _size; i < sz; i++)
					_alloc.construct( _elements + i, c );
			} else {
				// reallocate one time;
				for (size_t i = _size; i < sz; i++)
					push_back(u);
			}
		}

		size_type capacity() const { return _capacity; }

		bool empty()const { return _size; }

		void reserve(size_type n) {
			if (n > _capacity) {
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, _elements[i]);
				clear();
				_alloc.deallocate(_elements, _capacity);
				_capacity = n;
				_elements = tmp;
			} else
				; //do nothing
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
				throw std::out_of_range;
			return _elements[n];
		}

		const_reference at(size_type n) const {
			if (n >= _size)
				throw std::out_of_range;
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

		void push_back(const T& x) {

			if (_capacity > _size) {
				_alloc.construct(_elements + _size, x);
				_size++;
			} else {
				// reallocation
				_capacity *= 2;
				pointer tmp = _alloc.allocate( _capacity);
				// copy elements
				for(size_type i= 0; i < _size; i++)
					_alloc.construct(tmp + i, _elements[i]);
				// destroy all elements
				clear();
				// deallocate elemnets
				_alloc.deallocate(_elements, _capacity / 2);
				_elements =  tmp;
				_alloc.construct(_elements + _size, x);
				_size++;
			}
		}

		void pop_back() {
			_alloc.destroy(_elements + (--_size));
		}

		// iterator insert(iterator position, const T& x);
		// void insert(iterator position, size_type n, const T& x);
		// template <class InputIterator>
		// void insert(iterator position, InputIterator first, InputIterator last);
		// iterator erase(iterator position);
		// iterator erase(iterator first, iterator last);

		void swap(vector<T,Allocator> &other) {
			std::swap(*this, other);
		}

		void clear() {

			for(size_type i= 0; i < _size; i++)
				_alloc.destroy(_elements + i);
			_size = 0;
		}
	};

	template <class T, class Allocator>
	bool operator == (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator < (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator != (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator > (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y);

	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y){
		x.swap(y);
	}

} // ft

#endif

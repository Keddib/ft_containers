#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "iterator.hpp"
#include "utils/iterator_traits.hpp"
#include "utils/enable_if.hpp"
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
		typedef ft::iterator<T>								iterator;
		typedef ft::iterator<const T>						const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		pointer				_elements;
		allocator_type		_alloc;
		size_type			_capacity;
		size_type			_size;

		// tag dispatching
		template <class InputIterator>
		void _rang(InputIterator first, InputIterator last, std::random_access_iterator_tag) {
			_capacity = last - first;
			_elements = _alloc.allocate(_capacity);
		}
		template <class InputIterator>
		void _rang(InputIterator first, InputIterator last, std::bidirectional_iterator_tag) {
			_capacity= std::distance(first, last);
			_elements = _alloc.allocate(_capacity);
		}
		template <class InputIterator>
		void _ran(InputIterator , InputIterator , std::input_iterator_tag) {
		}


	public:

		// 23.2.4.1 construct/copy/destroy:
		explicit vector(const allocator_type &alloc = allocator_type())
		: _elements(NULL), _alloc(alloc), _capacity(0), _size(0) {}

		explicit vector(size_type n, const value_typeT& value = value_type(), const allocator_type &alloc = allocator_type())
		: _elements(NULL), _alloc(alloc), _capacity(n), _size(n)
		{
			_elements = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(_elements + i, value);
		}

		template <class InputIterator> // enable_if
		vector(InputIterator first, typename ft::enable_if<Type<typename std::iterator_traits<InputIterator>::iterator_category>::val, InputIterator>::type last, const Allocator& alloc = Allocator())
		: _elements(NULL), _alloc(alloc), _capacity(0), _size(0)
		{
			_range(first, last, ft::iterator_traits<InputIterator>::iterator_category());
			while (first != last)
				push_back (*first++);
		}

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

		vector<T,Allocator>& operator=(const vector& x)
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

		template <class InputIterator>
		void assign(InputIterator first, typename ft::enable_if<Type<typename std::iterator_traits<InputIterator>::iterator_category>::val, InputIterator>::type last)
		{
			clear();
			_alloc.deallocate(_elements, _capacity);
			_capacity = 0;
			_range(first, last, ft::iterator_traits<InputIterator>::iterator_category());
			while (first != last)
				push_back (*first++);
		}

		void assign(size_type n, const_reference u) {
			clear();
			_alloc.deallocate(_elements, _capacity);
			_capacity = n;
			_elements = _alloc.allocate(_capacity);
			for (; _size < n; _size++) {
				_alloc.construct(_elements + _size, u);
		}

		allocator_type get_allocator() const { return _alloc; }

		// // iterators:
		iterator begin() { return iterator(_elements); }

		const_iterator begin() const { return const_iterator(_elements); }

		iterator end() {return iterator(_elements + _size); }

		const_iterator end() const { return const_iterator(_elements + _size); }

		reverse_iterator rbegin() { return reverse_iterator(_elements + size); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(_elements + size); }

		reverse_iterator rend() { return reverse_iterator(_elements ); }

		const_reverse_iterator rend() const { return const_reverse_iterator(_elements); }

		// 23.2.4.2 capacity:
		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

		void resize( size_type sz, value_type c = value_type() ) {

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

		void push_back(const_reference x) {
			if (_capacity == 0) {
				_capacity = 1;
				_elements = _alloc.allocate(1);
			}
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
			iterator iter = insert(position, x);
			for (size_type i = 1; i < n; i++) {
				iterator iter = insert(iter + 1, x);
			}
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, typename ft::enable_if<Type<typename std::iterator_traits<InputIterator>::iterator_category>::val, InputIterator>::type last)
		{
			iterator iter = insert(position, *first);
			while (first != last) {
				iterator iter = insert(iter + 1, *first);
				first++;
			}
		}

		iterator erase(iterator position) {
			size_type pos = position - _elements;
			_alloc.destroy(_elemets + pos);
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

			for (size_type i = 0; (i < rang && i < _size) ; i++)
			{
				_alloc.destroy(_elements + (pos + i) ));
				if (rang + (pos + i) < _size)
					_alloc.construct(_elements + (pos + i), _elements[rang + pos + i] );
			}

			for (size_type i = pos + rang; i < _size; i++)
			{
				_alloc.destroy(_elements + i);
				if (i + rang < _size)
					_alloc.construct(_elements + i, (_elements[i + rang] );
			}
			_size = (_size >= rang) ? _size - rang : pos;
			return first;
		}

		void swap(vector& other) {
			std::swap(*this, other);
		}

		void clear() {

			for(size_type i= 0; i < _size; i++)
				_alloc.destroy(_elements + i);
			_size = 0;
		}
	};

	template <class T, class Allocator>
	bool operator == (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (x.size() == y.size() && std::equal(x.begin(), y.end(), x.begin()));
	}

	template <class T, class Allocator>
	bool operator != (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return !(x == y);
	}

	template <class T, class Allocator>
	bool operator < (const vector<T,Allocator>& x, const vector<T,Allocator>& y);

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

};

} // ft

#endif

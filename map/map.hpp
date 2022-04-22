#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "../utils/pair.hpp"
#include "../utils/reverse_iterator.hpp"
#include "iterator.hpp"
#include "RBT.hpp"
#include <memory>

namespace ft
{

template <typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<std::pair<const Key, T> > >
class map {


	private:
		typedef RBT<std::pair<const Key, T>, Compare, Allocator>			_RBT;
		typedef RBT<const std::pair<const Key, T>, Compare, Allocator>	const_RBT;
		typedef typename _RBT::Node									Node;
		typedef Node*												Node_ptr;

	public: // types:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename Allocator::reference				reference;
		typedef typename Allocator::const_reference			const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef map_iterator<_RBT>							iterator;
		typedef map_iterator<const_RBT>						const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		_RBT			_Tree;
		allocator_type	_Alloc;
		key_compare		_Comp;

	public:

		// 23.3.1.1 construct/copy/destroy:
		explicit map(const Compare& comp = Compare(), const Allocator &alloc = Allocator()) : _Tree(comp, alloc), _Alloc(alloc), _Comp(comp) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator &alloc = Allocator()) : _Tree(comp, alloc), _Alloc(alloc), _Comp(comp) {
			while (first != last)
				_Tree.insert(*first++);
		}

		// map(const map<Key,T,Compare,Allocator>& x);

		~map() {};

		// map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x);

		// iterators:
		iterator begin() { return iterator(&_Tree, _Tree.minimum()); }
		const_iterator begin() const { return const_iterator(&_Tree, _Tree.minimum()); }
		iterator end() { return iterator(&_Tree, _Tree.nil()); }
		const_iterator end() const { return const_iterator(&_Tree, _Tree.nil()); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// capacity:
		bool			empty()			const { return !_Tree.size(); }
		size_type		size()			const { return _Tree.size(); }
		size_type		max_size()		const { return _Tree.max_size(); };
		allocator_type	get_allocator()	const { return _Alloc; }


		// 23.3.1.2 element access:
		T& operator[](const key_type& x) {
			Node_ptr ret = _Tree.insert(x).first;
			return ret->value;
		}


		// modifiers:
		std::pair<iterator, bool> insert(const value_type& x) {
			std::pair<Node_ptr, bool> ret = _Tree.insert(x);

			iterator it(&_Tree, ret.first);
			return std::make_pair(it, ret.second);
		}

		iterator insert(iterator position, const value_type& x) {
			Node_ptr z = _Tree.insert(x).first;
			return iterator(&_Tree, z);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			while (first != last)
			{
				_Tree.insert(*first);
				first++;
			}
		}

		void erase(iterator position) {
			_Tree.deleteNode(position.get_node());
		}

		size_type	erase(const key_type& x) {
			return _Tree.deleteNode(x);
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				_Tree.deleteNode(first++);
		}

		// void		swap(map<Key,T,Compare,Allocator>&);


		void		clear() { _Tree.clear(); }


		// observers:
		key_compare		key_comp()		const { return  _Tree.key_comp(); }
		// value_compare	value_comp()	const;

		// 23.3.1.3 map operations:
		iterator		find(const key_type& x) {
			return iterator(&_Tree, _Tree.search(x));
		}

		const_iterator	find(const key_type& x)	const {
			return const_iterator(&_Tree, _Tree.search(x));
		}


		size_type		count(const key_type& x)		const {
			Node_ptr p = _Tree.search(x);
			if (p != _Tree.nil())
				return 1;
			return 0;
		}

		iterator	lower_bound(const key_type& x) {

			Node_ptr z = _Tree.lower_bound(x);
			return iterator(&_Tree, z);
		}
		const_iterator	lower_bound(const key_type& x)	const {

			Node_ptr z = _Tree.lower_bound(x);
			return const_iterator(&_Tree, z);
		}
		iterator	upper_bound(const key_type& x) {

			Node_ptr z = _Tree.upper_bound(x);
			return iterator(&_Tree, z);
		}
		const_iterator	upper_bound(const key_type& x)	const {

			Node_ptr z = _Tree.upper_bound(x);
			return const_iterator(&_Tree, z);
		}

		std::pair<iterator,iterator> equal_range(const key_type& x) {
			return make_pair(lower_bound(x), upper_bound(x));
		}

		std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const {
			return make_pair(lower_bound(x), upper_bound(x));
		}

};

// template <class Key, class T, class Compare, class Allocator>
// bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

// template <class Key, class T, class Compare, class Allocator>
// bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

// template <class Key, class T, class Compare, class Allocator>
// bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

// template <class Key, class T, class Compare, class Allocator>
// bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);


// template <class Key, class T, class Compare, class Allocator>
// bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);


// template <class Key, class T, class Compare, class Allocator>
// bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

// // specialized algorithms:
// template <class Key, class T, class Compare, class Allocator>
// void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y);

}  // ft

#endif

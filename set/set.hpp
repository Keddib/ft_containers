#ifndef FT_SET_HPP
#define FT_SET_HPP

#include "../utils/pair.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "../RBTree/RBT.hpp"

namespace ft {


template <
			typename Key,
			typename Compare = std::less<Key>,
			typename Allocator = std::allocator<Key>
		>
class set {



	public: // types:
		typedef Key												key_type;
		typedef Key 											value_type;
		typedef Compare 										key_compare;
		typedef Compare 										value_compare;
		typedef Allocator										allocator_type;
		typedef typename Allocator::reference					reference;
		typedef typename Allocator::const_reference				const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer 				const_pointer;
		typedef typename Allocator::size_type					size_type;
		typedef typename Allocator::difference_type				difference_type;
	private: //types
		typedef ft::RBT<const value_type, Compare, Allocator>	_RBT;
		typedef typename _RBT::Node								Node;
		typedef Node*											Node_ptr;
	public: // types:
		typedef ft::node_iterator<const value_type>					iterator;
		typedef ft::node_iterator<const value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	private:
		key_compare		_Comp;
		allocator_type	_Alloc;
		_RBT			_Tree;

	public:
		// 23.3.3.1 construct/copy/destroy:
		explicit set(const Compare& comp = Compare(), const Allocator &alloc = Allocator())
		: _Comp(comp), _Alloc(alloc), _Tree(_Comp, _Alloc) {}

		template <class InputIterator>
		set(InputIterator first, InputIterator last,  const Compare& comp = Compare(), const Allocator &alloc = Allocator())
		: _Comp(comp), _Alloc(alloc), _Tree(_Comp, _Alloc)
		{
			while(first != last)
				_Tree.insert(*first++);
		}

		set(const set& x)
		: _Comp(x._Comp), _Alloc(x._Alloc), _Tree(x._Tree) {}


		set& operator=(const set& x) {
			if (this != &x) {
				_Tree = x._Tree;
			}
			return *this;
		}

		~set() {}

		void printBT() const{ _Tree.printBT();}
		// iterators:
		iterator begin() { return iterator(_Tree.minimum(), _Tree.root()); }
		const_iterator begin() const { return const_iterator( iterator(_Tree.minimum(), _Tree.root()) ); }
		iterator end() { return iterator(_Tree.nil(), _Tree.root()); }
		const_iterator end() const { return const_iterator( iterator(_Tree.nil(), _Tree.root()) ); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// capacity:
		bool empty() const { return !_Tree.size(); }
		size_type size() const { return _Tree.size(); }
		size_type max_size() const { return _Tree.max_size(); }
		allocator_type get_allocator() const { return _Alloc; }

		// modifiers:
		ft::pair<iterator,bool> insert(const value_type& x)
		{
			ft::pair<Node_ptr, bool> ret = _Tree.insert(x);

			iterator it(ret.first, _Tree.root());
			return ft::make_pair(it, ret.second);
		}

		iterator insert(iterator position, const value_type& x)
		{
			(void)position;
			Node_ptr z = _Tree.insert(x).first;
			return iterator(z, _Tree.root());
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_Tree.insert(*first);
				first++;
			}
		}

		void erase(iterator position) {
			_Tree.deleteNode(*position);
		}

		size_type erase(const key_type& x) {
			return _Tree.deleteNode(x);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last) {
				iterator it(_Tree.successor(first.get_node()), _Tree.root());
				_Tree.deleteNode(first.get_node(), true);
				first = it;
			}
		}

		void swap(set<Key,Compare,Allocator> &x) {
			_Tree.swap(x._Tree);
			std::swap(_Alloc, x._Alloc);
			std::swap(_Comp, x._Comp);
		}

		void clear() { _Tree.clear(); }

	// observers:
		key_compare key_comp() const { return _Comp; }
		value_compare value_comp() const { return value_compare(); }

		// set operations:
		iterator find(const key_type& x) const
		{
			return iterator(_Tree.search(x), _Tree.root());
		}

		size_type count(const key_type& x) const
		{
			Node_ptr p = _Tree.search(x);
			if (p != _Tree.nil())
				return 1;
			return 0;
		}

		iterator  lower_bound(const key_type& x) const
		{
			Node_ptr z = _Tree.lower_bound(x);
			return iterator(z, _Tree.root());
		}

		iterator  upper_bound(const key_type& x) const {

			Node_ptr z = _Tree.upper_bound(x);
			return iterator(z, _Tree.root());
		}

		ft::pair<iterator,iterator> equal_range(const key_type& x) const
		{
			return ft::make_pair(lower_bound(x), upper_bound(x));
		}

};


template <class Key, class Compare, class Allocator>
bool operator==(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
	if ( x.size() == y.size() ) {
		return std::equal ( x.begin(), x.end(), y.begin() );
	}
	return false;
}

template <class Key, class Compare, class Allocator>
bool operator< (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
}

template <class Key, class Compare, class Allocator>
bool operator!=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
	return !(x == y);
}

template <class Key, class Compare, class Allocator>
bool operator> (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
	return (y < x);
}

template <class Key, class Compare, class Allocator>
bool operator>=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
	return !(x < y);
}

template <class Key, class Compare, class Allocator>
bool operator<=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y) {
	return !(y < x);
}

// specialized algorithms:
template <class Key, class Compare, class Allocator>
void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y) {
	x.swap(y);
}


} // ft

#endif

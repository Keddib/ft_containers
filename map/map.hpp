#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "../utils/pair.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "../RBTree/RBT.hpp"
#include <memory>

namespace ft {

template <
			typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Allocator = std::allocator<pair<const Key, T> >
		>
class map
{


	public: // types:
		typedef Key 													key_type;
		typedef T 														mapped_type;
		typedef pair<const key_type, mapped_type>						value_type;
		typedef Compare 												key_compare;
		typedef Allocator 												allocator_type;
		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

	private:
		class	value_compare;
		typedef RBT<value_type, value_compare, Allocator>				_RBT;
		typedef typename _RBT::Node										Node;
		typedef Node*													Node_ptr;

	public: // iterators
		typedef node_iterator<value_type>								iterator;
		typedef node_iterator<const value_type>							const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	private:
		key_compare		_Comp;
		allocator_type	_Alloc;
		value_compare	_Value_Comp;
		_RBT			_Tree;

	public:
		// 23.3.1.1 construct/copy/destroy:
		// initializing tree with value compair that will be responsible of compairing keys of value_type
		// so we don't have to compair key of value type inside the tree to make it general
		explicit map(
					const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type() )
			: _Comp(comp), _Alloc(alloc), _Value_Comp(comp), _Tree(_Value_Comp, alloc) {}

		template <class InputIterator>
		map(
			InputIterator first,
			InputIterator last,
			const Compare &comp = Compare(),
			const Allocator &alloc = Allocator() )
			: _Comp(comp), _Alloc(alloc), _Value_Comp(comp), _Tree(_Value_Comp, alloc)
		{
			while (first != last)
				_Tree.insert(*first++);
		}


		map (const map& x)
		: _Comp(x._Comp), _Alloc(x._Alloc), _Value_Comp(x._Value_Comp), _Tree(x._Tree) {}

		map& operator= (const map& x) {
			if (this != &x)
				_Tree = x._Tree;
			return *this;
		}

		~map(){};

		// iterators:
		iterator begin() { return iterator(_Tree.minimum(), _Tree.root()); }
		const_iterator begin() const { return const_iterator( iterator(_Tree.minimum(), _Tree.root()) ); }
		iterator end() { return iterator(_Tree.root(), _Tree.root()); }
		const_iterator end() const { return const_iterator( iterator(_Tree.root(), _Tree.root()) ); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// capacity:
		bool empty() const { return !_Tree.size(); }
		size_type size() const { return _Tree.size(); }
		size_type max_size() const { return _Tree.max_size(); }
		allocator_type get_allocator() const { return _Alloc; }

		// 23.3.1.2 element access:
		T &operator[](const key_type &x)
		{
			value_type v(x, mapped_type());
			Node_ptr ret = _Tree.insert(v).first;
			return ret->value.second;
		}

		// modifiers:
		pair<iterator, bool> insert(const value_type &x)
		{
			pair<Node_ptr, bool> ret = _Tree.insert(x);

			iterator it(ret.first, _Tree.root());
			return ft::make_pair(it, ret.second);
		}

		iterator insert(iterator position, const value_type &x)
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

		size_type erase(const key_type &x) {
			value_type tmp(x, mapped_type());
			return _Tree.deleteNode(tmp);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last) {
				iterator it(_Tree.successor(first.get_node()), _Tree.root());
				_Tree.deleteNode((*first));
				first = it;
			}
		}

		void		swap(map<Key,T,Compare,Allocator> &x) {
			_Tree.swap(x._Tree);
			std::swap(_Alloc, x._Alloc);
			std::swap(_Comp, x._Comp);
		}

		void clear() { _Tree.clear(); }

		// observers:
		key_compare key_comp() const { return _Comp; }

		value_compare	value_comp() const { return _Value_Comp; }

		// 23.3.1.3 map operations:
		iterator find(const key_type &x)
		{
			value_type tmp(x, mapped_type());
			return iterator(_Tree.search(tmp), _Tree.root());
		}

		const_iterator find(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			return const_iterator(_Tree.search(tmp), _Tree.root());
		}

		size_type count(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			Node_ptr p = _Tree.search(tmp);
			if (p != _Tree.root())
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type &x)
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = _Tree.lower_bound(tmp);
			return iterator(z, _Tree.root());
		}
		const_iterator lower_bound(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = _Tree.lower_bound(tmp);
			return const_iterator( iterator(z, _Tree.root()) );
		}
		iterator upper_bound(const key_type &x)
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = _Tree.upper_bound(tmp);
			return iterator(z, _Tree.root());
		}
		const_iterator upper_bound(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = _Tree.upper_bound(tmp);
			return const_iterator( iterator(z, _Tree.root()) );
		}

		pair<iterator, iterator> equal_range(const key_type &x)
		{
			iterator it1(lower_bound(x));
			iterator it2(upper_bound(x));
			return ft::make_pair(it1, it2);
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &x) const
		{
			const_iterator it1(lower_bound(x));
			const_iterator it2(upper_bound(x));
			return ft::make_pair(it1, it2);
		}
};

template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
	if ( x.size() == y.size() ) {
		return std::equal ( x.begin(), x.end(), y.begin() );
	}
	return false;
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return !(x == y);
}

template <class Key, class T, class Compare, class Allocator>
bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
}

template <class Key, class T, class Compare, class Allocator>
bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return (y < x);
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return !(x < y);
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return !(y < x);
}

	// // specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y) {
	x.swap(y);
}

		// function object template inside map
	// uses the internal comparison object to generate the appropriate comparison
	// functional class
	template <typename Key, typename T, typename Compare, typename Alloc>
	class map< Key, T, Compare, Alloc>::value_compare
		: public std::binary_function<typename map::value_type, typename map::value_type, bool>
	{
		friend class map;

		protected:
			Compare comp;
			value_compare (Compare c): comp (c) {}
		public:
			typedef bool			result_type;
			typedef	value_type		first_argument_type;
			typedef value_type		second_argument_type;
			bool operator () (const value_type& x, const value_type& y) const{
				return comp (x.first, y.first);
			}
	};

} // ft

#endif

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include "../utils/pair.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "iterator.hpp"
#include "RBT.hpp"
#include <memory>

namespace ft
{

template <
			typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Allocator = std::allocator<pair<const Key, T> >
		>
class map
{

	private:
		class	value_compare;

		typedef RBT<pair<const Key, T>, Compare, Allocator> _RBT;
		typedef RBT<const pair<const Key, T>, Compare, Allocator> const_RBT;
		typedef typename _RBT::Node Node;
		typedef Node *Node_ptr;

	public: // types:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef map_iterator<_RBT> iterator;
		typedef map_iterator<const_RBT> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		_RBT _Tree;
		allocator_type _Alloc;
		key_compare _Comp;

	public:
		// 23.3.1.1 construct/copy/destroy:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _Tree(comp, alloc), _Alloc(alloc), _Comp(comp) {}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) : _Tree(comp, alloc), _Alloc(alloc), _Comp(comp)
		{
			while (first != last)
				_Tree.insert(*first++);
		}


		map (const map& x): _Tree(x._Tree), _Alloc(x._Alloc), _Comp(x._Comp) {}

		map& operator= (const map& x) {
			if (this != &x)
				_Tree = x._Tree;
			return *this;
		}

		~map(){};

		// iterators:
		iterator begin() { return iterator(&_Tree, _Tree.minimum()); }
		const_iterator begin() const { return const_iterator( iterator(&_Tree, _Tree.minimum()) ); }
		iterator end() { return iterator(&_Tree, _Tree.nil()); }
		const_iterator end() const { return const_iterator( iterator(&_Tree, _Tree.nil()) ); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// capacity:
		bool empty() const { return !_Tree.size(); }
		size_type size() const { return _Tree.size(); }
		size_type max_size() const { return _Tree.max_size(); };
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

			iterator it(&_Tree, ret.first);
			return ft::make_pair(it, ret.second);
		}

		iterator insert(iterator position, const value_type &x)
		{
			(void)position;
			Node_ptr z = _Tree.insert(x).first;
			return iterator(&_Tree, z);
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
			_Tree.deleteNode((*position).first);
		}

		size_type erase(const key_type &x) {
			return _Tree.deleteNode(x);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last) {
				iterator it(&_Tree, _Tree.successor(first.get_node()));
				_Tree.deleteNode((*first).first);
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
		key_compare key_comp() const { return _Tree.key_comp(); }

		value_compare	value_comp() const { return value_compare(_Comp); }

		// 23.3.1.3 map operations:
		iterator find(const key_type &x)
		{
			return iterator(&_Tree, _Tree.search(x));
		}

		const_iterator find(const key_type &x) const
		{
			return const_iterator(&_Tree, _Tree.search(x));
		}

		size_type count(const key_type &x) const
		{
			Node_ptr p = _Tree.search(x);
			if (p != _Tree.nil())
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type &x)
		{

			Node_ptr z = _Tree.lower_bound(x);
			return iterator(&_Tree, z);
		}
		const_iterator lower_bound(const key_type &x) const
		{

			Node_ptr z = _Tree.lower_bound(x);
			return const_iterator( iterator(&_Tree, z) );
		}
		iterator upper_bound(const key_type &x)
		{

			Node_ptr z = _Tree.upper_bound(x);
			return iterator(&_Tree, z);
		}
		const_iterator upper_bound(const key_type &x) const
		{

			Node_ptr z = _Tree.upper_bound(x);
			return const_iterator( iterator(&_Tree, z) );
		}

		pair<iterator, iterator> equal_range(const key_type &x)
		{
			return ft::make_pair(lower_bound(x), upper_bound(x));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &x) const
		{
			return ft::make_pair(lower_bound(x), upper_bound(x));
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
	class map< Key, T, Compare, Alloc>::value_compare : public std::binary_function<typename map::value_type, typename map::value_type, bool> {
		friend class map;

		protected:
			Compare comp;
			value_compare (Compare c): comp (c) {}
		public:
			typedef bool			result_type;
			typedef	value_type		first_argument_type;
			typedef value_type		second_argument_type;
			bool operator () (const value_type& x, const value_type& y) {
				return comp (x.first, y.first);
			}
	};

} // ft

#endif

#ifndef FT_NODE_ITERATOR_HPP
#define FT_NODE_ITERATOR_HPP

#include <iterator>
#include "../utils/enable_if.hpp"

namespace ft {

// node struct
template <typename T>
struct node
{
	T value;
	node *p;	 // parent
	node *left;	 // child
	node *right; // child;
	bool color;
	node( const T &x = T() ) : value(x) {
		p = NULL;
		left = NULL;
		right = NULL;
		color = BLACK;
	}
};

template <typename T>
class node_iterator: public std::iterator <std::bidirectional_iterator_tag,T>
{

	typedef ft::node<T>*				node_ptr;
	typedef ft::node<const T>*			const_node_ptr;

	public:

		typedef T																						value_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef const T&																				const_reference;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::pointer			pointer;
		typedef const T*																				const_pointer;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

	private:
		node_ptr		_node;
		node_ptr		_root;
		node_ptr		_nil;

	public:
		node_iterator (const node_ptr node = 0x0, const node_ptr root = 0x0)
		: _node(node), _root(root), _nil (root->p) {};


		node_iterator (const node_iterator& x)
		: _node (x._node), _root(x._root), _nil (x._nil) {}

		~node_iterator(){}

		// convertion from non const iter to const iter
		template <class U>
		node_iterator(const node_iterator<U>& other,
		typename ft::enable_if<std::is_convertible<U, T>::value>::type* = 0)
		{
			_node = (const_node_ptr)other.base();
			_root = (const_node_ptr)other.get_root();
			_nil = (const_node_ptr)other.get_nil();
		}

		// operator node_iterator<const T> () {
			// return node_iterator<const T>( (const_node_ptr)_node, (const_node_ptr)_nil);
		// }

		node_iterator& operator = (const node_iterator& x) {
			if (this != &x) {
				_node = x._node;
				_nil = x._nil;
			}
			return *this;
		}

		bool operator == (const node_iterator& iter) const { return _node == iter._node; }

		bool operator != (const node_iterator& iter) const { return _node != iter._node; }

		reference		operator * () { return _node->value; }
		const_reference	operator * () const { return _node->value; }

		pointer			operator-> () { return &(_node->value); };
		const_pointer	operator-> () const { return &(_node->value); };

		node_iterator& operator ++ () {
			_node = next(_node);
			return (*this);
		}

		node_iterator operator ++ (int) {
			node_iterator tmp (*this);
			_node = next(_node);
			return tmp;
		}

		node_iterator& operator -- () {
			if (_node == _nil)
				_node = maximum(_root);
			else
				_node = prev (_node);
			return (*this);
		}

		node_iterator operator -- (int) {
			node_iterator tmp (*this);
			if (_node == _nil)
				_node = maximum(_root);
			else
				_node = prev (_node);
			return (tmp);
		}

		node_ptr	get_node () const { return _node; }
		node_ptr	get_root () const { return _root; }
		node_ptr	get_nil () const { return _nil; }
		node_ptr	base() const { return _node; }
		private:

			node_ptr minimum(node_ptr t)
			{
				if (t == _nil)
					return t;
				node_ptr tmp = t;
				while (tmp->left != _nil)
					tmp = tmp->left;
				return tmp;
			}

			node_ptr maximum(node_ptr t)
			{
				if (t == _nil)
					return t;
				node_ptr tmp = t;
				while (tmp->right != _nil)
					tmp = tmp->right;
				return tmp;
			}

			node_ptr next(node_ptr x)
			{
				if (x == _nil)
					return x;
				if (x->right != _nil)
					return minimum(x->right);
				node_ptr y = x->p;
				while (y != _nil && x == y->right)
				{
					x = y;
					y = y->p;
				}
				return y;
			}

			node_ptr prev(node_ptr x)
			{
				if (x == _nil)
					return x;
				if (x->left != _nil)
					return maximum(x->left);
				node_ptr y = x->p;
				while (y != _nil && x != y->right)
				{
					x = y;
					y = y->p;
				}
				return y;
			}

};

} // ft

#endif

#ifndef FT_MITERATOR_HPP
#define FT_MITERATOR_HPP

#include <iterator>


namespace ft {

template <typename RBT>
class node_iterator: public std::iterator <std::bidirectional_iterator_tag, typename RBT::value_type> {


	typedef	typename RBT::Node*		node_ptr;


	public:

		typedef typename RBT::value_type																value_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::pointer			pointer;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

	private:
		const RBT		*_tree;
		node_ptr		_node;

	public:
		node_iterator (const RBT* tree = 0x0, node_ptr const node = 0x0): _tree (tree), _node (node) {};

		node_iterator (const node_iterator& x): _tree (x._tree), _node (x._node) {}

		~node_iterator(){}

		template <typename T>
		operator node_iterator<T> () { return node_iterator<T> (reinterpret_cast <const T*> (_tree) , reinterpret_cast <typename T::node_pointer> (_node)); }

		node_iterator& operator = (const node_iterator& x) {
			if (this != &x) {
				_tree = x._tree;
				_node = x._node;
			}
			return *this;
		}

		bool operator == (const node_iterator& iter) const {
			return _node == iter._node;
		}

		bool operator != (const node_iterator& iter) const {
			return _node != iter._node;
		}

		reference	operator * () const {
			return _node->value;
		}
		pointer		operator-> () const { return &(_node->value); };

		node_iterator& operator ++ () {
			_node = _tree->successor (_node);
			return (*this);
		}

		node_iterator operator ++ (int) {
			node_iterator tmp (*this);
			_node = _tree->successor (_node);
			return tmp;
		}

		node_iterator& operator -- () {
			if (_node == _tree->nil ())
				_node = _tree->maximum(_tree->root());
			else
				_node = _tree->predecessor (_node);
			return (*this);
		}

		node_iterator operator -- (int) {
			node_iterator tmp (*this);

			if (_node == _tree->nil ())
				_node = _tree->maximum (_tree->root ());
			else
				_node = _tree->predecessor (_node);
			return (tmp);
		}

		node_ptr	get_node () const { return _node; }
		RBT*		get_tree () const { return _tree; }

};

} // ft

#endif

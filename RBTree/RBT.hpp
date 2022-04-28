#ifndef FT_RBT_HPP
#define FT_RBT_HPP

#define BLACK 0
#define RED 1

#include <iostream>
#include <memory>
#include "iterator.hpp"

namespace ft
{

template <typename T, typename Allocator>
class _RBT_base
{
	protected:
		// NOTA BENE
		// The stored instance is not actually of "allocator_type"'s
		// type.  Instead we rebind the type to
		// Allocator<node<Tp>>, which should probably be the same.
		// List_node<Tp> is not the same
		// size as Tp (it's 3 [p, left, right] pointers larger), and specializations on
		// Tp may go unused because List_node<Tp> is being bound
		// instead.
		//

		// types
		typedef typename Allocator::template rebind<node<T> >::other	Node_allocator_type;
		typedef typename Node_allocator_type::size_type					size_type;
		typedef node<T>													Node;

		Node_allocator_type _Node_allocator;

		_RBT_base(const Allocator &a) : _Node_allocator(a) {}

		~_RBT_base() {}

		Node *allocate_node() { return _Node_allocator.allocate(1); }

		void deallocate_node(Node *__p) { _Node_allocator.deallocate(__p, 1); }

		size_type max_size() const { return _Node_allocator.max_size(); }

		Node *create_node(const T &x = T()) {
			Node *p = this->allocate_node();
			_Node_allocator.construct(p, Node(x));
			return p;
		}

		void delete_node(Node *p) {
			_Node_allocator.destroy(p);
			deallocate_node(p);
		}
};

template <typename T, typename Compare, typename Alloc = std::allocator<T> >
class RBT : protected _RBT_base<T, Alloc>
{

	public: // types
		typedef _RBT_base<T, Alloc>					Base;
		typedef Alloc								allocator_type;
		typedef T									value_type;
		typedef Compare								key_compare;
		typedef node<T>								Node;
		typedef Node*								node_pointer;
		typedef typename Base::size_type			size_type;

	private: // atributes
		key_compare		_comp;
		allocator_type	_alloc;
		node_pointer	_NIL;
		node_pointer	_root;
		size_type		_size;

	public:
		RBT(
			const key_compare &c = key_compare(),
			const allocator_type &a = allocator_type()
			)
		: Base(a), _comp(c), _alloc(a)
		{
			_NIL = this->create_node();
			_root = _NIL;
			_size = 0;
		}

		RBT(const RBT &x)
			: Base(x._alloc), _comp(x._comp), _alloc(x._alloc)
		{
			_NIL = this->create_node();
			_root = x.clone(x._root, _NIL, this->Base::_Node_allocator);
			_root->p = _NIL;
			_size = x._size;
		}

		RBT &operator=(const RBT &x)
		{
			if (this != &x)
			{
				// assigne members of x to this members
				_size = x._size;
				_comp = x._comp;
				_alloc = x._alloc;
				// clear this.tree
				clear(_root);
				// get copy of x tree with this allocatore
				_root = x.clone(x._root, _NIL, Base::_Node_allocator);
				_root->p = _NIL;
			}
			return (*this);
		}

		~RBT()
		{
			// destructor of RBT clear the tree and delete NIL
			clear(_root);
			this->delete_node(_NIL);
		}

		pair<Node *, bool> insert(const value_type &x)
		{
			Node *z = this->create_node(x);
			return insert(z);
		}

		pair<Node *, bool> insert(Node *z)
		{
			Node *y = _NIL;
			Node *x = _root;
			while (x != _NIL)
			{
				y = x;
				if (_comp(z->value, x->value)) // <
					x = x->left;
				else if (_comp(x->value, z->value))
					x = x->right;
				else // if the key already excite return the exicted node and false
				{
					this->delete_node(z);
					return ft::make_pair(x, false);
				}
			}
			z->p = y;
			if (y == _NIL)
				_root = z;
			else if (_comp(z->value, y->value))
				y->left = z;
			else
				y->right = z;
			z->left = _NIL;
			z->right = _NIL;
			z->color = RED;
			insertFIXUP(z);
			// _NIL->p = maximum();
			_size++;
			return ft::make_pair(z, true);
		}

		size_type deleteNode(const value_type &value)
		{
			Node *z = search(value);
			if (z != _NIL)
			{
				deleteNode(z, false);
				_size--;
				return 1;
			}
			return 0;
		}

		void deleteNode(Node *z, bool size)
		{
			Node *y = z;
			Node *x;
			bool OriginalColor = y->color;
			if (z->left == _NIL)
			{
				x = z->right;
				TRANSPLANT(z, z->right);
			}
			else if (z->right == _NIL)
			{
				x = z->left;
				TRANSPLANT(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				OriginalColor = y->color;
				x = y->right;
				if (y->p == z)
					x->p = y;
				else
				{
					TRANSPLANT(y, y->right);
					y->right = z->right;
					y->right->p = y;
				}
				TRANSPLANT(z, y);
				y->left = z->left;
				y->left->p = y;
				y->color = z->color;
			}
			if (OriginalColor == BLACK)
				deleteFIXUP(x);
			this->delete_node(z);
			if (size)
				_size--;
			// _NIL->p = maximum();
		}

		Node *search(const value_type &value) const
		{
			Node *tmp = _root;
			while (tmp != _NIL)
			{
				if (_comp(value, tmp->value))
					tmp = tmp->left;
				else if (_comp(tmp->value, value))
					tmp = tmp->right;
				else
					return tmp;
			}
			return tmp;
		}

		Node *minimum() const
		{
			return minimum(_root);
		}

		Node *minimum(Node *t) const
		{
			if (t == _NIL)
				return t;
			Node *tmp = t;
			while (tmp->left != _NIL)
				tmp = tmp->left;
			return tmp;
		}

		Node *maximum() const
		{
			return maximum(_root);
		}

		Node *maximum(Node *t) const
		{
			if (t == _NIL)
				return t;
			Node *tmp = t;
			while (tmp->right != _NIL)
				tmp = tmp->right;
			return tmp;
		}
		Node *successor(Node *x) const
		{
			if (x == _NIL)
				return x;
			if (x->right != _NIL)
				return minimum(x->right);
			Node *y = x->p;
			while (y != _NIL && x == y->right)
			{
				x = y;
				y = y->p;
			}
			return y;
		}
		Node *predecessor(Node *x) const
		{
			if (x == _NIL)
				return x;
			if (x->left != _NIL)
				return maximum(x->left);
			Node *y = x->p;
			while (y != _NIL && x != y->right)
			{
				x = y;
				y = y->p;
			}
			return y;
		}

		Node *lower_bound(const value_type &value) const
		{
			Node *x = _root;
			Node *y = _NIL;
			while (x != _NIL)
			{
				if (_comp(value, x->value))
				{
					y = x;
					x = x->left;
				}
				else if (_comp(x->value, value))
					x = x->right;
				else
					return x;
			}
			return y;
		}

		Node *upper_bound(const value_type &value) const
		{
			Node *x = lower_bound(value);
			if (!_comp(x->value, value) && !_comp(value, x->value))
				return successor(x);
			return (x);
		}

		void clear()
		{
			clear(_root);
			_root = _NIL;
			_size = 0;
		}

		void swap(RBT &x)
		{
			std::swap(_NIL, x._NIL);
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
		}

		node_pointer const nil() const { return _NIL; }

		node_pointer const *root() const { return &_root; }
		// node_pointer *n_root() { return &_root; }

		size_type max_size() const { return Base::max_size(); }

		size_type size() const { return _size; }


	private: // mem functions
		// clone a new tree from the subtree rooted at x
		// and use new_nil as the new sentinel in case
		// we have different trees
		Node *clone(Node *x, Node *nil, typename Base::Node_allocator_type &alloc) const
		{
			if (x == _NIL)
				return nil;
			Node *_node = alloc.allocate(1);
			alloc.construct(_node, *x);
			_node->left = clone(x->left, nil, alloc);
			if (_node->left != nil)
				_node->left->p = _node;
			_node->right = clone(x->right, nil, alloc);
			if (_node->right != nil)
				_node->right->p = _node;
			return _node;
		}

		void clear(Node *node)
		{
			if (node == _NIL)
				return;

			/* first delete both subtrees */
			clear(node->left);
			clear(node->right);
			/* then delete the node */
			this->delete_node(node);
		}

		void TRANSPLANT(Node *u, Node *v)
		{
			if (u->p == _NIL)
				_root = v;
			else if (u->p->left == u)
				u->p->left = v;
			else
				u->p->right = v;
			v->p = u->p;
		}

		void LEFT_ROTATE(Node *x)
		{
			Node *y = x->right;
			x->right = y->left;
			if (y->left != _NIL)
				y->left->p = x;
			y->p = x->p;
			if (x->p == _NIL)
				_root = y;
			if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->left = x;
			x->p = y;
		}

		void RIGHT_ROTATE(Node *x)
		{
			Node *y = x->left;
			x->left = y->right;
			if (y->right != _NIL)
				y->right->p = x;
			y->p = x->p;
			if (x->p == _NIL)
				_root = y;
			if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->right = x;
			x->p = y;
		}

		void insertFIXUP(Node *z)
		{

			while (z->p->color == RED)
			{

				if (z->p == z->p->p->left)
				{
					Node *y = z->p->p->right;
					if (y->color == RED)
					{ // recolor
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else
					{ // do suitablle rotation and recolor
						if (z == z->p->right)
						{ // LR
							z = z->p;
							LEFT_ROTATE(z);
						}
						z->p->color = BLACK; // LL
						z->p->p->color = RED;
						RIGHT_ROTATE(z->p->p);
					}
				}
				else
				{ // z.p == z.p.p.right
					Node *y = z->p->p->left;
					if (y->color == RED)
					{ // recolor
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else
					{ // do suitablle rotation and recolor
						if (z == z->p->left)
						{ // RL
							z = z->p;
							RIGHT_ROTATE(z);
						}
						z->p->color = BLACK; // RR
						z->p->p->color = RED;
						LEFT_ROTATE(z->p->p);
					}
				}
			}
			_root->color = BLACK;
		}
		void deleteFIXUP(Node *x)
		{

			while (x != _root and x->color == BLACK)
			{
				if (x == x->p->left)
				{
					Node *w = x->p->right;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						LEFT_ROTATE(x->p);
						w = x->p->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{

						if (w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							RIGHT_ROTATE(w);
							w = x->p->right;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->right->color = BLACK;
						LEFT_ROTATE(x->p);
						x = _root;
					}
				}
				else
				{

					Node *w = x->p->left;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						RIGHT_ROTATE(x->p);
						w = x->p->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{

						if (w->left->color == BLACK)
						{
							w->right->color = BLACK;
							w->color = RED;
							LEFT_ROTATE(w);
							w = x->p->left;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->left->color = BLACK;
						RIGHT_ROTATE(x->p);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}
};

} // ft

#endif

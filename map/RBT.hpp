#ifndef FT_RBT_HPP
#define FT_RBT_HPP

#define BLACK 0
#define RED 1

namespace ft {

// node struct
template <typename _Tp >
struct node {

	_Tp _M_Data;
	bool _color;
	node *_p; //parent
	node *_left; // left child
	node *_right; // right child;
	node (const _Tp &x = _Tp(), node *par = NULL, node *lef = NULL, node *ri = NULL, bool col = BLACK)
	: _M_Data(x), _p(par), _left(lef), _right(ri), _color(col) {}
};


template<typename _Tp, typename _Alloc>
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

		typedef typename _Alloc::template rebind<node<_Tp> >::other	_Node_Alloc_type;

		_Node_Alloc_type _N_Alloc;

		node<_Tp>* _M_get_node()
		{ return _N_Alloc.allocate(1); }

		void	_M_put_node(node<_Tp>* __p)
		{ _N_Alloc.deallocate(__p, 1); }

	public:
		typedef _Alloc allocator_type;

		allocator_type get_allocator() const
		{ return allocator_type( _Node_Alloc_type() ); }

		_RBT_base(const allocator_type& __a) : _N_Alloc(__a) { }

		// This is what actually destroys the list.
		~_RBT_base() {}

};


template <typename T, typename Compare>
class RBT {

	public: // types
		typedef	T											value_type;
		typedef Compare										key_compare;
		typedef node<T>										Node;

	private: // atributes
		Node *_NIL;
		Node *_root;

	public:
		RBT(Node *nil):_NIL(nil), _root(_NIL) {}

		void insert(Node *z) { // check duplication
			Node *y = _NIL;
			Node *x = _root;
			while (x != _NIL) {
				y = x;
				if  (z->_M_Data.first < x->_M_Data.first) // <
					x = x->left;
				else x = x->right; // >
			}
			z->p = y;
			if (y == _NIL)
				_root =z;
			else if(z->_M_Data.first < y->_M_Data.first)
				y->left = z;
			else y->right = z;
			z->left = _NIL;
			z->right = _NIL;
			z->color = RED;
			insertFIXUP(z);
		}
		void deleteNode(const_reference value) {}

		Node *searchTree(const_reference key) const
		{
			Node *tmp = _root;
			while ( tmp != _NIL && tmp->_M_Data.first != key)
			{
				if (key < tmp->key)
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			return tmp;
		}

		Node *minimum(Node *t) const
		{
			if (t == _NIL)
				return t;
			Node *tmp = t;
			while (tmp->_M_Data.first != _NIL)
				tmp = tmp->_M_Data.first;
			return tmp;
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
			while (y != _NIL && x == y->right){
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
			while (y != _NIL && x != y->right){
				x = y;
				y = y->p;
			}
			return y;
		}

		void printBT(const std::string& prefix, const Node * root, bool isLeft)
		{
		    if( root != _NIL )
		    {
		        std::cout << prefix;
		        std::cout << (isLeft ? "├──" : "└──" );
		        // print the value of the node
		        std::cout << root->_M_Data.first << ':' << (root->color ? 'R' : 'B') << std::endl;
		        // enter the next tree level - left and right branch
		        printBT( prefix + (isLeft ? "│   " : "    "), root->left, true);
		        printBT( prefix + (isLeft ? "│   " : "    "), root->right, false);
		    }
		}

		void printBT()
		{
		    printBT("", _root, false);
		}

	private: // mem functions

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
			else x->p->right = y;
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
			else x->p->right = y;
			y->right = x;
			x->p = y;
		}

		void insertFIXUP(Node *z) {

			while (z->p->color == RED) {

				if (z->p == z->p->p->left)
				{
					Node *y = z->p->p->right;
					if (y->color == RED) { // recolor
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else{ // do suitablle rotation and recolor
						if (z == z->p->right) { // LR
							z = z->p;
							LEFT_ROTATE(z);
						}
						z->p->color = BLACK; // LL
						z->p->p->color = RED;
						RIGHT_ROTATE(z->p->p);
					}
				}
				else { // z.p == z.p.p.right
					Node *y = z->p->p->left;
					if (y->color == RED) { // recolor
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else { // do suitablle rotation and recolor
						if (z == z->p->left) { // RL
							z = z->p;
							RIGHT_ROTATE( z);
						}
						z->p->color = BLACK; // RR
						z->p->p->color = RED;
						LEFT_ROTATE( z->p->p);
					}
				}
			}
			_root->color = BLACK;
		}

		Node* _M_create_node(const value_type& __x = value_type())
		{
			_Node* __p = this->_M_get_node();
			try {
				std::_N_Alloc.construct(&__p->_M_data, __x);
			}
			catch(...) {
				_M_put_node(__p);
				__throw_exception_again;
			}
			return __p;
		}
};

} // ft

#endif

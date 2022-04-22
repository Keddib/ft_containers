#ifndef FT_RBT_HPP
#define FT_RBT_HPP

#define BLACK 0
#define RED 1


#include <memory>

namespace ft {

// node struct
template <typename _Tp >
struct node {

	_Tp value;
	bool color;
	node *p; //parent
	node *left; // left child
	node *right; // right child;
	node (const _Tp &x = _Tp(), node *par = NULL, node *lef = NULL, node *ri = NULL, bool col = BLACK)
	: value(x), p(par), left(lef), right(ri), color(col) {}
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
		typedef typename _Node_Alloc_type::size_type				size_type;
		typedef node<_Tp>											Node;

		_Node_Alloc_type _N_Alloc;

		Node* _M_get_node()
		{ return _N_Alloc.allocate(1); }

		void	_M_put_node(Node* __p)
		{ _N_Alloc.deallocate(__p, 1); }

	protected:
		typedef _Alloc allocator_type;

		allocator_type get_allocator() const { return allocator_type(); }
		size_type max_size() const { return _N_Alloc.max_size() ; }

		_RBT_base(const allocator_type& __a) : _N_Alloc(__a) { }

		~_RBT_base() {}

		Node* _create_node(const _Tp& __x = _Tp())
		{
			Node* p = this->_M_get_node();
			try {
				_N_Alloc.construct(p, Node(__x));
			}
			catch(...) {
				_M_put_node(p);
				// __throw_exception_again;
			}
			return p;
		}
		void _delete_node(Node *p)
		{
			try {
				_N_Alloc.destroy(p);
			}
			catch(...) {
				// __throw_exception_again;
			}
			_M_put_node(p);
		}
};


template <typename T, typename Compare, typename Alloc = std::allocator<T> >
class RBT : protected _RBT_base<T, Alloc> {

	public: // types
		typedef	T												value_type;
		typedef	typename T::first_type							Key;
		typedef	typename T::second_type							Value;
		typedef Compare											key_compare;
		typedef node<T>											Node;
		typedef _RBT_base<T, Alloc>								Base;
		typedef typename Base::size_type						size_type;
		// typedef _RBT_base<T, Alloc>::_Node_Alloc_type			node_alloc_type;

	private: // atributes
		Node *_NIL;
		Node *_root;
		key_compare _Com;
		Alloc _A;
		size_t	_size;

	public:
		RBT(const key_compare &c = key_compare(), const Alloc &a = Alloc()): _Com(c), _A(a), Base(_A){
			_NIL = this->_create_node();
			_root = _NIL;
			_size = 0;
		}

		~RBT() {
			clear(_root);
			this->_delete_node(_NIL);
			_root = NULL;
			_NIL = NULL;
		}

		pair<Node*, bool> insert(const value_type &x) {
			Node *z = this->_create_node(x);
			return insert(z);
		}

		pair<Node*, bool> insert(Node *z) { // check duplication
			Node *y = _NIL;
			Node *x = _root;
			while (x != _NIL) {
				y = x;
				if  (_Com(z->value.first, x->value.first)) // <
					x = x->left;
				else if (_Com(x->value.first, z->value.first))
					x = x->right;
				else {
					this->_delete_node(z);
					return std::make_pair(x, false);
				}
			}
			z->p = y;
			if (y == _NIL)
				_root =z;
			else if(z->value.first < y->value.first)
				y->left = z;
			else y->right = z;
			z->left = _NIL;
			z->right = _NIL;
			z->color = RED;
			insertFIXUP(z);
			_size++;
			return std::make_pair(z, true);
		}

		int deleteNode(const Key &key) {
			Node *z = search(key);
			if (z != _NIL) {
				deleteNode(z);
				_size--;
				return 1;
			}
			return 0;
		}

		void deleteNode(Node *z) {
			Node *y = z;
			Node *x;
			bool OriginalColor = y->color;
			if (z->left == _NIL) {
				x = z->right;
				TRANSPLANT(z, z->right);
			}
			else if (z->right == _NIL) {
				z = z->left;
				TRANSPLANT(z, z->left);
			} else {
				y = minimum(z->right);
				OriginalColor = y->color;
				x = y->right;
				if (y->p == z)
					x->p = y;
				else {
					TRANSPLANT(y , y->right);
					y->right = z->right;
					y->right->p = y;
				}
				TRANSPLANT(z, y);
				y->left = z->left;
				y->left->p = y;
				y->color = z->color;
			}
			this->_delete_node(z);
			if (OriginalColor == BLACK)
				deleteFIXUP(x);
		}

		Node *search(const Key &key) const
		{
			Node *tmp = _root;
			while ( tmp != _NIL )
			{
				if (_Com(key, tmp->value.first))
					tmp = tmp->left;
				else if (_Com(tmp->value.first, key))
					tmp = tmp->right;
				else
					return tmp;
			}
			return tmp;
		}

		Node *minimum() const {
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

		Node *maximum() const {
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

		Node *lower_bound(const value_type &key) {
			Node *x = _root;
			Node *y = _NIL;
			while (x != _NIL) {
				if (_Com(key, x->value.first)) {
					y = x;
					x = x->left;
				}
				else if (_Com(x->value.first, key))
					x = x->right;
				else
					return x;
			}
			return y;
		}

		Node *upper_bound(const value_type &key) {
			Node *x = lower_bound(key);
			if (!_Com(x->value, key) && !_Com(key, x->value))
				return successor(x);
			return (x);
		}

		void clear() {
			clear(_root);
			_root = _NIL;
			_size = 0;
		}

		Node* const nil() const { return	_NIL; }

		Node* const root() const { return	_root; }

		size_type	max_size() const { return Base::max_size(); }

		size_t size() const { return _size; }

		key_compare  key_comp() { return _Com; }

		void printBT(const std::string& prefix, const Node * root, bool isLeft)
		{
		    if( root != _NIL )
		    {
		        std::cout << prefix;
		        std::cout << (isLeft ? "├──" : "└──" );
		        // print the value of the node
		        std::cout << root->value.first << ':' << (root->color ? 'R' : 'B') << std::endl;
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

		void clear(Node* node)
		{
			if (node == _NIL) return;

			/* first delete both subtrees */
			clear(node->left);
			clear(node->right);
			/* then delete the node */
			this->_delete_node( node );
		}

		void TRANSPLANT(Node *u, Node *v) {
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
		void deleteFIXUP(Node *x) {

			while (x != _root and x->color == BLACK)
			{
				if (x == x->p->left) {
					Node *w = x->p->right;
					if (w->color == RED) {
						w->color = BLACK;
						x->p->color = RED;
						LEFT_ROTATE(x->p);
						w = x->p->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK) {
						w->color = RED;
						x = x->p;
					}
					else {

						if (w->right->color == BLACK) {
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
				else {
					// (same as then clause with “right” and “left” exchanged)
					Node *w = x->p->left;
					if (w->color == RED) {
						w->color = BLACK;
						x->p->color = RED;
						LEFT_ROTATE(x->p);
						w = x->p->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK) {
						w->color = RED;
						x = x->p;
					}
					else {

						if (w->left->color == BLACK) {
							w->right->color = BLACK;
							w->color = RED;
							RIGHT_ROTATE(w);
							w = x->p->left;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->left->color = BLACK;
						LEFT_ROTATE(x->p);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}
};

} // ft

#endif

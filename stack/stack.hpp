#include <vector>
#include <stdexcept>

namespace ft
{
	template <typename T, typename Container = std::vector<T> >
	class stack
	{
		public:
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::size_type			size_type;

		protected:
			container_type _c;

		public:
			stack( const container_type& c = container_type() ) : _c(c) {}

			// member functions

			bool empty () const{ return _c.empty(); }
			size_type size () const{ return _c.size(); }
			value_type& top () { return _c.back(); }
			value_type const& top () const { return _c.back(); }
			void push (value_type const& x) { _c.push_back(x); }
			void pop () { _c.pop_back(); }

			// relational operators (stack)
			friend bool operator == (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return x._c == y._c;
			}
			friend bool operator != (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return x._c != y._c;
			}
			friend bool operator > (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return x._c > y._c;
			}
			friend bool operator < (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return x._c < y._c;
			}
			friend bool operator >= (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return x._c >= y._c;
			}
			friend bool operator <= (const stack<T, Container>& x, const stack<T, Container>& y)
			{
				return x._c <= y._c;
			}
	};

}  // ft

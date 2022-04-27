#include <iostream>
#include <cstring>
#include <string>
#include "../utils/allocator.hpp"
#include <vector>
#include <iterator>
#include <typeinfo>


template <typename Iterator, typename Distance>
void advance_impl(Iterator& it, Distance n, typename std::forward_iterator_tag)
{
	std::cout << "forward\n";
	while (--n >= 0)
		++it;
}

template <typename Iterator, typename Distance>
void advance_impl(Iterator& it, Distance n, typename std::random_access_iterator_tag)
{
	std::cout << "random\n";
	it += n;
}

template <typename Iterator,typename Distance>
void advance (Iterator & it, Distance n) {
	typedef typename std::iterator_traits<Iterator>::iterator_category category;
	advance_impl (it, n, category ());
}


class A {
	public:
		A(int){}
		A(int, int) {}
		A(A const &) { std::cout << "copy\n"; }
		~A() { std::cout << "dis\n"; }
		operator bool() const { return true; }
};

class B {
	public:
		explicit B(int){}
		explicit B(int, int) {}
		B(A const &) { std::cout << "copy\n"; }
		 operator bool() const { return true; }
};


void func (std::vector<int>::const_iterator b, std::vector<int>::const_iterator e)
{
	while (b != e)
		std::cout << *b++ << ' ';
	std::cout << std::endl;
}



template <typename T>
class Ax {
	private:
		T *_p;
	public:
		Ax(T* p = 0x00): _p(p) {}
		operator Ax<const T> () {
			return _p;
		}

};

template <typename T>
class Bx {
	public:
	typedef Ax<T> iter;
	typedef Ax<const T> c_iter;
};


template <typename Tag>
class Tag_traits {
	public:
		//types
		typedef typename Tag::cat	cat;
};


class XXX {
	public:
		typedef int cat;
};


template<typename T>
class test{
	public:
	template<typename U>
	void _tag(U first, U second, typename U::cat) {
		std::cout << "_TAG WORKS\n";
	}
	template<typename U>
	test(U first, U end) {
		// std::cout << "cons1\n";
		typedef typename Tag_traits<U>::cat cat;
		_tag(first, end, cat() );
	}
	test(size_t n, const T &value) {
		std::cout << "cons2\n";
	}

};


struct AA {

};

void refconst(int const i)
{
	std::cout << "i = " << i << '\n';
}

int main (int, char **argv) {

	int f = std::atoi(argv[1]);
	int l = std::atoi(argv[2]);

	size_t size = 10;

	ft::Simple_alloc<int> alloc;

	int *p = alloc.allocate(10);
	for (int i = 0; i < size; i++)
		alloc.construct(p + i, i + 10);

	for (int i = 0; i < 10; i++)
		std::cout << *(p + i) << ' ';
	std::cout << std::endl;



	{

			// isert one element
			


			// erase range
			// size_t rang = l - f;
			// size_t pos = f;

			// for (size_t i = 0; (i < rang && i < size) ; i++)
			// {
			// 	alloc.destroy(p + (pos + i));
			// 	if (rang + (pos + i) < size)
			// 		alloc.construct(p + (pos + i), *(p + (rang + (pos + i) ) ) );
			// }
			// for (size_t i = pos + rang; i < size; i++)
			// {
			// 	alloc.destroy(p + i);
			// 	if (i + rang < size)
			// 		alloc.construct(p + i, *(p + i + rang));
			// }
			// std::cout << "s = " << size << " r = " << rang << '\n';
			// size = (size >= rang) ? size - rang : pos;
			// std::cout << "s = " << size << '\n';
	}




	for (int i = 0; i < size; i++)
		std::cout << *(p + i) << ' ';
	std::cout << std::endl;

	return 0;
}

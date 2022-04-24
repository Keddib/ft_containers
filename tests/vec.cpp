#include <iostream>


#include <vector>


class A {

	private:
	 int a;
	public:
		A(int x = 0): a(x) {}
		bool operator == (const A &other) const {
			return a == other.a;
		}
};


int main() {


	A x(10);
	std::vector<A> vec(10, x);
	std::vector<A> ve1(10, x);

	std::vector<A>::iterator iter = vec.begin();
	std::vector<A>::iterator iter2 = vec.end();


	std::cout << ( vec == ve1) << '\n';


	return 0;
}

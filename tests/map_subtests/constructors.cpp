#include "../tests_utils.hpp"

template <template <typename, typename> class Stack, template <typename, typename> class Vector>
void	stack_constructor(bool benchmark, std::fstream &out) {
  std::deque<int> mydeque (3,100);
  Vector<int, std::allocator<int> > myvector (2,200);

  Stack<int, Vector<int, std::allocator<int> > > first;
  Stack<int, Vector<int, std::allocator<int> > > second (mydeque);

  Stack<int, Vector<int, std::allocator<int> > > third;
  Stack<int, Vector<int, std::allocator<int> > > fourth (myvector);

	if (benchmark == false) {
		sout << "size of first: " << first.size() << '\n';
		sout << "size of second: " << second.size() << '\n';
		sout << "size of third: " << third.size() << '\n';
		sout << "size of fourth: " << fourth.size() << '\n';
		print_stack("Stack:", first, out);
		print_stack("Stack:", second, out);
		print_stack("Stack:", third, out);
		print_stack("Stack:", fourth, out);
	}
}

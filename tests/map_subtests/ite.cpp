#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(std::fstream& out) : value(), _verbose(false), out(out) { };
		foo(std::fstream& out, value_type src, const bool verbose = false) : value(src), _verbose(verbose), out(out) { };
		foo(std::fstream& out, foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose), out(out) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { out << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { out << "foo::m called [" << this->value << "]" << std::endl; };
		void stream(std::fstream& out) { this->out = out; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				out << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type		value;
		bool			_verbose;
		std::fstream&	out;
};

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_ite(bool benchmark, std::fstream& out)
{
	// Ite_arrow from mli42

	foo<int> c_foo(out);

	std::list<Pair<float, foo<int> > > lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<float, foo<int> >(2.5 + i, foo<int>(out, i + 1)));

	Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > > mp(lst.begin(), lst.end());
	typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::iterator it(mp.begin());
	typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::const_iterator ite(mp.begin());

	if (benchmark == false) {
		print_map("Map for iteration:", mp, out);
		typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::const_iterator tmpe;

		tmpe = ++ite;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite++;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite++;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ++ite;
		out << tmpe->first << " => " << tmpe->second << std::endl;

		it->second.m();
		ite->second.m();

		typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::iterator tmp;

		tmp = ++it;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it++;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it++;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = ++it;
		out << tmp->first << " => " << tmp->second << std::endl;

		tmpe = --ite;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite--;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = --ite;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite--;
		out << tmpe->first << " => " << tmpe->second << std::endl;

		(*it).second.m();
		(*ite).second.m();

		tmp = --it;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it--;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it--;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = --it;
		out << tmp->first << " => " << tmp->second << std::endl;

	} else {
		++ite;
		ite++;
		++ite;
		ite++;

		++it;
		it++;
		it++;
		++it;

		--ite;
		ite--;
		--ite;
		ite--;

		--it;
		it--;
		it--;
		--it;
	}

	// Ite_no0 and Ite_n1 from mli42

	// CAN'T WORK WITH -Werror FLAG, UNCOMMENT TO TRY IT
	//Map<int, int, Comp<int>, std::allocator<Pair<const int,int > > > mpite0;
	//mpite0[1] = 2;

	//typename Map<int, int, Comp<int>, std::allocator<Pair<const int,int > > >::const_iterator ite0 = mpite0.begin();
	//*ite0 = 42;

	//Map<int, int, Comp<int>, std::allocator<Pair<const int,int > > > const mpite1;
	//typename Map<int, int, Comp<int>, std::allocator<Pair<const int,int > > >::iterator ite1 = mpite1.begin();

	typename Map<int, int, Comp<int>, std::allocator<Pair<const int,int > > >::iterator it2;
	typename Map<int, int, Comp<int>, std::allocator<Pair<const int,int > > >::const_iterator ite2;

	if (benchmark == false) {
		out << (it2 != ite2) << std::endl;
	}

}

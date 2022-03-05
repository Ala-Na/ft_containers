#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo() : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) {};
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
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
};

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_ite(bool benchmark, std::fstream& out)
{
	// Ite_arrow from mli42

	foo<int> c_foo();

	std::list<Pair<float, foo<int> > > lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<float, foo<int> >(2.5 + i, foo<int>(i + 1)));

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

		out << it->second.getValue() << std::endl;
		out << ite->second.getValue() << std::endl;

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


		out << (*it).second.getValue() << std::endl;
		out << (*ite).second.getValue() << std::endl;

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

#include "../main_tests/tests_utils.hpp"
// Taken and adapted from mli42 ft_containers tester

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_op_sqbr(bool benchmark, std::fstream& out)
{
	// Ite_arrow from mli42

	Map<float, std::string, Comp<float>, std::allocator<Pair<const float, std::string > > > mp;

	mp['a'] = "an element";
	mp['b'] = "another element";
	mp['c'] = mp['b'];
	mp['b'] = "old element";

	if (benchmark == false) {
		print_map("Map for operator at[]:", mp, out);
		out << "insert a new element via operator[]: " << mp['d'] << std::endl;
		print_map("After insert with operator at[]:", mp, out);
	} else {
		mp['d'];
	}


}

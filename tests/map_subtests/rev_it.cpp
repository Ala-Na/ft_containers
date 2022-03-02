#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair>
void	map_rev_it(bool benchmark, std::fstream& out)
{

	// rev_ite_construct from mli42

	Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > > mp;

	typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::iterator it = mp.begin();
	typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::const_iterator cit = mp.begin();

	typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::reverse_iterator rit(it);

	typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::const_reverse_iterator crit(rit);
	typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::const_reverse_iterator crit_(it);
	typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::const_reverse_iterator crit_2(cit);

	// error expected
	//typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::reverse_iterator rit_(crit);
	//typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::reverse_iterator rit2(cit);
	//typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::iterator it2(rit);
	//typename Map<int, int, Comp<int>, std::allocator<Pair<const int, int > > >::const_iterator cit2(crit);

	mp[1] = 42;
	mp[3] = 0;
	mp[4] = 666;
	mp[0] = 9999;

	if (benchmark == false) {
		out << "---------------------" << std::endl;
		out << "Map for reverse iteration:\n";
		rit = mp.rbegin();
		for (; rit != mp.rend(); ++rit) {
			out << rit->first << " => " << rit->second << std::endl;
		}
	}

	std::list<Pair<char, int> > lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<char, int>('a' + i, (i + 1) * 7));

	// rite from mli42

	Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > > mp2(lst.begin(), lst.end());
	typename Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > >::iterator it_2 = mp2.begin();
	typename Map<char, int, Comp<char>, std::allocator<Pair<const char, int > > >::reverse_iterator it2(it_2), ite2;

	if (benchmark == false) {
		print_map("Map for 2nd reverse iteration:", mp2, out);

		out << (it_2 == it2.base()) << std::endl;
		out << (it_2 == dec(it2, 3).base()) << std::endl;

		out << it2.base()->first << " => " << it2.base()->second << std::endl;
		out << inc(it2.base()->first, 1) << " => " << inc(it2.base()->second, 1) << std::endl;
		out << "TEST OFFSET" << std::endl;
		--it2;
		out << it2.base()->first << " => " << it2.base()->second << std::endl;
		out << it2->first << " => " << it2->second << std::endl;

	}

	it2 = mp2.rbegin(); ite2 = mp2.rend();
	if (benchmark == false) {
		for (;it2 != ite2; it2++)
			out << "[rev] " << it2->first << " => " << it2->second << std::endl;
		out << "---------------------" << std::endl;
		out << "Map for reverse iteration:\n";
		it2 = mp2.rbegin();
		for (; it2 != mp2.rend(); ++it2) {
			out << it2->first << " => " << it2->second << std::endl;
		}
	}

	// rev_ite_arrow from mli42
	std::list<Pair<float, foo<int> > > lst3;
	unsigned int lst_size3 = 5;
	for (unsigned int i = 0; i < lst_size3; ++i)
		lst3.push_back(Pair<float, foo<int> >(2.5 - i, foo<int>(out, (i + 1) * 7)));

	Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > > mp3(lst3.begin(), lst3.end());
	typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::reverse_iterator it3(mp3.rbegin());
	typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::const_reverse_iterator ite3(mp3.rbegin());

	if (benchmark == false) {
		print_map("Map for 3nd reverse iteration:", mp3, out);

		typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::const_reverse_iterator tmpe;

		tmpe = ++ite3;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite3++;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite3++;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ++ite3;
		out << tmpe->first << " => " << tmpe->second << std::endl;

		it3->second.m();
		ite3->second.m();

		typename Map<float, foo<int>, Comp<float>, std::allocator<Pair<const float, foo<int> > > >::reverse_iterator tmp;

		tmp = ++it3;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it3++;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it3++;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = ++it3;
		out << tmp->first << " => " << tmp->second << std::endl;

		tmpe = --ite3;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite3--;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = --ite3;
		out << tmpe->first << " => " << tmpe->second << std::endl;
		tmpe = ite3--;
		out << tmpe->first << " => " << tmpe->second << std::endl;

		(*it3).second.m();
		(*ite3).second.m();

		tmp = --it3;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it3--;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = it3--;
		out << tmp->first << " => " << tmp->second << std::endl;
		tmp = --it3;
		out << tmp->first << " => " << tmp->second << std::endl;

	} else {
		++ite3;
		ite3++;
		++ite3;
		ite3++;

		++it3;
		it3++;
		it3++;
		++it3;

		--ite3;
		ite3--;
		--ite3;
		ite3--;

		--it3;
		it3--;
		it3--;
		--it3;
	}
}

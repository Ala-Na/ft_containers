#include "../main_tests/tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester

template <typename Map, typename U>
void	ft_erase(Map &mp, U param, bool benchmark, std::fstream& out)
{
	int iter = 0;
	if (benchmark == false) {
		out << "-- [" << iter++ << "] --" << std::endl;
	}
	mp.erase(param);
	if (benchmark == false) {
		print_map("After erase:", mp, out);
	}
}

template <typename Map, typename U, typename V>
void	ft_erase(Map &mp, U param, V param2, bool benchmark, std::fstream& out)
{
	int iter = 0;
	if (benchmark == false) {
		out << "-- [" << iter++ << "] --" << std::endl;
	}
	mp.erase(param, param2);
	if (benchmark == false) {
		print_map("After erase:", mp, out);
	}
}

template <template <class, class, class, class> class Map, template <class> class Comp, template <class, class> class Pair, template <typename, typename> class Vector>
void	map_erase(bool benchmark, std::fstream& out)
{
	// Erase from mli42

	Vector<Pair<int, std::string>, std::allocator<Pair<int, std::string> > > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(Pair<int, std::string>(i, std::string((lst_size - i), i + 65)));
	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mp(lst.begin(), lst.end());
	if (benchmark == false) {
		print_map("Map for erase testing:", mp, out);
	}

	ft_erase(mp, ++mp.begin(), benchmark, out);

	ft_erase(mp, mp.begin(), benchmark, out);
	ft_erase(mp, --mp.end(), benchmark, out);
	ft_erase(mp, mp.begin(), ++(++(++mp.begin())), benchmark, out);
	ft_erase(mp, --(--(--mp.end())), --mp.end(), benchmark, out);

	mp[10] = "Hello";
	mp[11] = "Hi there";
	if (benchmark == false) {
		print_map("Map after some erasing:", mp, out);
	}
	ft_erase(mp, --(--(--mp.end())), mp.end(), benchmark, out);

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	if (benchmark == false) {
		print_map("Map after some adding:", mp, out);
	}
	ft_erase(mp, mp.begin(), mp.end(), benchmark, out);
	if (benchmark == false) {
		print_map("Map after complete erasing:", mp, out);
	}

	// Erase2 from mli42

	std::list<Pair<int, std::string> > lst2;
	unsigned int lst_size2 = 6;
	for (unsigned int i = 0; i < lst_size2; ++i)
		lst2.push_back(Pair<int, std::string>(i, std::string((lst_size - i), i + 65)));
	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mp2(lst.begin(), lst.end());
	if (benchmark == false) {
		print_map("Map for 2nd erase testing:", mp2, out);
	}

	for (int i = 2; i < 4; ++i)
		ft_erase(mp2, i, benchmark, out);

	ft_erase(mp2, mp2.begin()->first, benchmark, out);
	ft_erase(mp2, (--mp2.end())->first, benchmark, out);

	mp2[-1] = "Hello";
	mp2[10] = "Hi there";
	mp2[10] = "Hi there";
	if (benchmark == false) {
		print_map("Map after deletions/additions:", mp2, out);
	}

	ft_erase(mp2, 0, benchmark, out);
	ft_erase(mp2, 1, benchmark, out);

	if (benchmark == false) {
		print_map("Map after finale deletions:", mp2, out);
	}

	// Tricky erase from mli42
	Map<int, std::string, Comp<int>, std::allocator<Pair<const int, std::string> > > mp3;

	mp3[42] = "lol";

	mp3[50] = "mdr";
	mp3[25] = "funny";

	mp3[46] = "bunny";
	mp3[21] = "fizz";
	mp3[30] = "buzz";
	mp3[55] = "fuzzy";

	mp3[18] = "bee";
	mp3[23] = "coconut";
	mp3[28] = "diary";
	mp3[35] = "fiesta";
	mp3[44] = "hello";
	mp3[48] = "world";
	mp3[53] = "this is a test";
	mp3[80] = "hey";

	mp3[12] = "no";
	mp3[20] = "idea";
	mp3[22] = "123";
	mp3[24] = "345";
	mp3[27] = "27";
	mp3[29] = "29";
	mp3[33] = "33";
	mp3[38] = "38";

	mp3[43] = "1";
	mp3[45] = "2";
	mp3[47] = "3";
	mp3[49] = "4";
	mp3[51] = "5";
	mp3[54] = "6";
	mp3[60] = "7";
	mp3[90] = "8";

	if (benchmark == false) {
		print_map("Map for tricky erase testing:", mp3, out);
	}
	ft_erase(mp3, 25, benchmark, out);
	ft_erase(mp3, 55, benchmark, out);
	ft_erase(mp3, 24, benchmark, out);
	ft_erase(mp3, 54, benchmark, out);
	ft_erase(mp3, 22, benchmark, out);
	ft_erase(mp3, 51, benchmark, out);
	ft_erase(mp3, 21, benchmark, out);
	ft_erase(mp3, 53, benchmark, out);
	ft_erase(mp3, 20, benchmark, out);
	ft_erase(mp3, 23, benchmark, out);
	ft_erase(mp3, 42, benchmark, out);
	ft_erase(mp3, 38, benchmark, out);
	ft_erase(mp3, 35, benchmark, out);
	ft_erase(mp3, 33, benchmark, out);

	if (benchmark == false) {
		print_map("Map after tricky erase testing:", mp3, out);
	}
}

#include "../tests_utils.hpp"

// Taken and adapted from mli42 ft_containers tester


template <typename Ite_1, typename Ite_2>
void ft_eq_ope_rev(const Ite_1 &first, const Ite_2 &second, bool benchmark, std::fstream& out, const bool redo = 1)
{
	if (benchmark == false) {
		out << "inf:" << (first < second) << " " << *first << " " << *second << std::endl;
		out << "inf or eq:" << (first <= second) << std::endl;
		out << "sup:" << (first > second) << std::endl;
		out << "sup or eq:" << (first >= second) << std::endl;
		out << std::endl;
	} else {
		first < second;
		first <= second;
		first > second;
		first >= second;
	}
	if (redo)
		ft_eq_ope_rev(second, first, benchmark, out, 0);
}

template <template <typename, typename> class Vector>
void	vector_rev_it(bool benchmark, std::fstream& out) {
	Vector<int, std::allocator<int> > vct;
	typename Vector<int, std::allocator<int> >::iterator it = vct.begin();
	typename Vector<int, std::allocator<int> >::const_iterator cit = vct.begin();

	typename Vector<int, std::allocator<int> >::reverse_iterator rit(it);

	typename Vector<int, std::allocator<int> >::const_reverse_iterator crit(rit);
	typename Vector<int, std::allocator<int> >::const_reverse_iterator crit_(it);
	typename Vector<int, std::allocator<int> >::const_reverse_iterator crit_2(cit);

	//error expected
	//Vector<int, std::allocator<int> >::reverse_iterator rit_(crit);
	//Vector<int, std::allocator<int> >::reverse_iterator rit2(cit);
	//Vector<int, std::allocator<int> >::iterator it2(rit);
	//Vector<int, std::allocator<int> >::const_iterator cit2(crit);
	if (benchmark == false)
		out << "OK" << std::endl;

	const int size2 = 5;
	Vector<int, std::allocator<int> > vct2(size2);
	typename Vector<int, std::allocator<int> >::iterator it2 = vct2.begin();
	typename Vector<int, std::allocator<int> >::reverse_iterator ite2(it2);

	for (int i = 0; i < size2; ++i)
		vct2[i] = (i + 1) * 5;

	if (benchmark == false) {
		print_vector("Vector for rev_it:", vct2, out);
		out << (it2 == ite2.base()) << std::endl;
		out << (it2 == (ite2 + 3).base()) << std::endl;

		out << *(ite2.base() + 1) << std::endl;
		out << *(ite2 - 3) << std::endl;
		out << *(ite2 - 3).base() << std::endl;
	}
	ite2 -= 3;

	if (benchmark == false) {
		out << *ite2.base() << std::endl;

		out << "TEST OFFSET" << std::endl;
		out << *(ite2) << std::endl;
		out << *(ite2).base() << std::endl;
		out << *(ite2 - 0) << std::endl;
		out << *(ite2 - 0).base() << std::endl;
		out << *(ite2 - 1).base() << std::endl;
	}

	const int size3 = 5;
	Vector<int, std::allocator<int> > vct3(size3);
	typename Vector<int, std::allocator<int> >::reverse_iterator it3 = vct3.rbegin();
	typename Vector<int, std::allocator<int> >::const_reverse_iterator ite3 = vct3.rbegin();

	for (int i = 0; i < size3; ++i)
		it3[i] = (size3 - i) * 5;

	it3 = it3 + 5;
	it3 = 1 + it3;
	it3 = it3 - 4;

	if (benchmark == false) {
		out << *(it3 += 2) << std::endl;
		out << *(it3 -= 1) << std::endl;
	}

	*(it3 -= 2) = 42;
	*(it3 += 2) = 21;

	if (benchmark == false) {
		out << "const_ite +=/-=: " << *(ite3 += 2) << " | " << *(ite3 -= 2) << std::endl;

		out << "(it3 == const_it): " << (ite3 == it3) << std::endl;
		out << "(const_ite - it3): " << (ite3 - it3) << std::endl;
		out << "(ite3 + 3 == it3): " << (ite3 + 3 == it3) << std::endl;
		print_vector("Vector for rev_it:", vct3, out);
	}

	const int size4 = 5;
	Vector<foo<int>, std::allocator<foo<int> > > vct4(size4);
	typename Vector<foo<int>, std::allocator<foo<int> > >::reverse_iterator it4(vct4.rbegin());
	typename Vector<foo<int>, std::allocator<foo<int> > >::const_reverse_iterator ite4(vct4.rend());

	for (int i = 1; it4 != ite4; ++i)
		*it4++ = (i * 7);
	if (benchmark == false) {
		print_vector("Vector for rev_it:", vct4, out);

		it4 = vct4.rbegin();
		ite4 = vct4.rbegin();

		out << *(++ite4) << std::endl;
		out << *(ite4++) << std::endl;
		out << *ite4++ << std::endl;
		out << *++ite4 << std::endl;

		out << it4->getValue() << std::endl;
		out << ite4->getValue() << std::endl;

		out << *(++it4) << std::endl;
		out << *(it4++) << std::endl;
		out << *it4++ << std::endl;
		out << *++it4 << std::endl;

		out << *(--ite4) << std::endl;
		out << *(ite4--) << std::endl;
		out << *--ite4 << std::endl;
		out << *ite4-- << std::endl;

		out << (*it4).getValue() << std::endl;
		out << (*ite4).getValue() << std::endl;

		out << *(--it4) << std::endl;
		out << *(it4--) << std::endl;
		out << *it4-- << std::endl;
		out << *--it4 << std::endl;
	} else {
		it4 = vct4.rbegin();
		ite4 = vct4.rbegin();

		++ite4;
		ite4++;
		ite4++;
		++ite4;

		++it4;
		it4++;
		it4++;
		++it4;

		--ite4;
		ite4--;
		ite4--;
		--ite4;

		--it4;
		it4--;
		it4--;
		--it4;
	}

	const int size5 = 5;
	Vector<foo<int>, std::allocator<foo<int> > > vct5(size5);
	typename Vector<foo<int>, std::allocator<foo<int> > >::reverse_iterator it_0(vct5.rbegin());
	typename Vector<foo<int>, std::allocator<foo<int> > >::reverse_iterator it_1(vct5.rend());
	typename Vector<foo<int>, std::allocator<foo<int> > >::reverse_iterator it_mid;

	typename Vector<foo<int>, std::allocator<foo<int> > >::const_reverse_iterator cit_0 = vct5.rbegin();
	typename Vector<foo<int>, std::allocator<foo<int> > >::const_reverse_iterator cit_1;
	typename Vector<foo<int>, std::allocator<foo<int> > >::const_reverse_iterator cit_mid;

	for (int i = size5; it_0 != it_1; --i)
		*it_0++ = i;

	if (benchmark == false)
		print_vector("Vector for rev_it:", vct5, out);
	it_0 = vct5.rbegin();
	cit_1 = vct5.rend();
	it_mid = it_0 + 3;
	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	if (benchmark == false) {
		out << std::boolalpha;
		out << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

		out << "\t\tft_eq_ope:" << std::endl;
	}

	if (benchmark == false)
		print_vector("Vector for rev_it:", vct5, out);

	if (benchmark == false)
		out << "regular it" << std::endl;
	ft_eq_ope_rev(it_0 + 3, it_mid, benchmark, out);
	ft_eq_ope_rev(it_0, it_1, benchmark, out);
	ft_eq_ope_rev(it_1 - 3, it_mid, benchmark, out);

	if (benchmark == false)
		out << "constant it" << std::endl;
	ft_eq_ope_rev(cit_0 + 3, cit_mid, benchmark, out);
	ft_eq_ope_rev(cit_0, cit_1, benchmark, out);
	ft_eq_ope_rev(cit_1 - 3, cit_mid, benchmark, out);

	if (benchmark == false)
		out << "both it" << std::endl;
	ft_eq_ope_rev(it_0 + 3, cit_mid, benchmark, out);
	ft_eq_ope_rev(it_mid, cit_0 + 3, benchmark, out);
	ft_eq_ope_rev(it_0, cit_1, benchmark, out);
	ft_eq_ope_rev(it_1, cit_0, benchmark, out);
	ft_eq_ope_rev(it_1 - 3, cit_mid, benchmark, out);
	ft_eq_ope_rev(it_mid, cit_1 - 3, benchmark, out);

}

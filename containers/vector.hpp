/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:21:45 by anadege           #+#    #+#             */
/*   Updated: 2022/03/16 22:03:17 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "./utils/id_comp.hpp"
#include "./utils/exceptions.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			// ---------------------------
			// Members types definitions :
			// ---------------------------

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename std::ptrdiff_t							difference_type;
			typedef typename std::size_t							size_type;

		protected:

			// -----------------
			// Member objects :
			// -----------------

			allocator_type	alloc; //allocator object
			size_type		vec_capacity; //max vec_capacity of vector
			size_type		filled; //present number of element in vector
			value_type*		first_elem; //pointer to first element of vector

		public:

			// -----------------
			// Member functions :
			// -----------------

			// --------------------
			// --- CONSTRUCTORS ---
			// --------------------

			// - Default constructor
			explicit vector (const allocator_type &alloc = allocator_type()) :
				alloc(alloc), vec_capacity(0), filled(0), first_elem(NULL) {}

			// - Fill constructor
			explicit vector (size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type()) :
				alloc(alloc), vec_capacity(n), filled(0)
			{
				if (this->vec_capacity > this->max_size()) {
					throw MaxSizeExceededException();
				}
				this->first_elem = this->alloc.allocate(this->vec_capacity);
				for (size_type i = 0; i < this->vec_capacity; i++) {
					this->alloc.construct(this->first_elem + i, val);
					this->filled++;
				}
			}

			// - Range constructor

			// Memo : enable_if is use to differenciate from fill constructor.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				alloc(alloc), vec_capacity(0), filled(0)
			{
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				}
				if (first == last) {
					this->first_elem = NULL;
					return ;
				}
				InputIterator	tmp = first;
				while (tmp != last) {
					++tmp;
					++this->vec_capacity;
				}
				if (this->vec_capacity > this->max_size()) {
						throw MaxSizeExceededException();
				}
				this->first_elem = this->alloc.allocate(this->vec_capacity);
				for (size_type i = 0; i < this->vec_capacity; i++, first++) {
					this->alloc.construct(this->first_elem + i, *first);
					this->filled++;
				}
			}

			// - Copy constructor

			// Deep copy is created
			vector (const vector& x) :
				alloc(x.alloc), vec_capacity(x.vec_capacity), filled (0)
			{
				this->first_elem = this->alloc.allocate(this->vec_capacity);
				for (size_type i = 0; i < x.filled; i++) {
					this->alloc.construct(this->first_elem + i, *(x.first_elem + i));
					this->filled++;
				}
			}

			// ------------------
			// --- DESTRUCTOR ---
			// ------------------

			~vector () {
				this->clear();
				this->alloc.deallocate(this->first_elem, this->vec_capacity);
			}

			// --------------------------
			// -- ASSIGNMENT OPERATOR ---
			// --------------------------

			vector&	operator= (const vector& other) {
				this->clear();
				this->alloc.deallocate(this->first_elem, this->vec_capacity);
				this->first_elem = this->alloc.allocate(other.vec_capacity);
				this->vec_capacity = other.vec_capacity;
				for (size_type i = 0; i < other.filled; i++) {
					this->alloc.construct(this->first_elem + i, *(other.first_elem + i));
					this->filled++;
				}
				return *this;
			}

			// -----------------
			// --- ALLOCATOR ---
			// -----------------

			// Returns the allocator object of vector
			allocator_type	get_allocator() const {
				return this->alloc;
			}

			// -----------------
			// --- ITERATORS ---
			// -----------------

			// - Begin functions

			// Returns iterator to first element.
			iterator	begin() {
				return static_cast<iterator>(this->first_elem);
			}

			// Returns constant iterator to first element.
			const_iterator	begin() const {
				return static_cast<const_iterator>(this->first_elem);
			}

			// - End functions

			// Returns iterator to last element.
			iterator	end() {
				return static_cast<iterator>(this->first_elem + this->filled);
			}

			// Returns constant iterator to last element.
			const_iterator	end() const {
				return static_cast<const_iterator>(this->first_elem
					+ this->filled);
			}

			// - Reverse begin functions

			// Returns reverse iterator, starting from last element.
			reverse_iterator	rbegin() {
				return static_cast<reverse_iterator>(this->end());
			}

			// Returns constant reverse iterator, starting from last element.
			const_reverse_iterator	rbegin() const {
				return static_cast<const_reverse_iterator>(this->end());
			}

			// - Reverse end functions

			// Returns reverse iterator, starting from first element.
			reverse_iterator	rend() {
				return static_cast<reverse_iterator>(this->begin());
			}

			// Returns constant reverse iterator, starting from first element.
			const_reverse_iterator	rend() const {
				return static_cast<const_reverse_iterator>(this->begin());
			}

			// ----------------
			// --- vec_capacity ---
			// -----------------

			// - Size function

			// Returns number of elements already present.
			size_type	size () const {
				return this->filled;
			}

			// - Maximum size function

			// Returns the vec_capacity of the allocator object, not the current
			// vec_capacity of the vector.
			size_type	max_size () const {
				return static_cast<size_type>(this->alloc.max_size());
			}

			// - Resize function

			// Resize the container to size n.
			// Behaviour is different depending of previous size.
			// If n is lesser, the rest is deleted.
			// If n is greater, elements of value val are inserted after the
			// original content.
			// Reallocation can be made if vec_capacity is exceeded.
			void	resize (size_type n, value_type val = value_type()) {
				if (n > this->max_size()) {
					throw MaxSizeExceededException();
				} else if (n > this->vec_capacity) {
					this->reserve(n);
				}
				if (n > this->filled) {
					for (; this->filled < n; this->filled++) {
						this->alloc.construct(this->first_elem + this->filled,
							val);
					}
				} else if (n < this->filled) {
					for (; this->filled != n; this->filled--) {
						this->alloc.destroy(this->first_elem + this->filled - 1);
					}
				}
			}

			// - vec_capacity function

			// Returns size of allocated storage vec_capacity, which can be equal
			// or greater than size.
			size_type	capacity () const {
				return this->vec_capacity;
			}

			// - Empty function

			// Boolean returning true when size is 0.
			bool	empty () const {
				return (this->filled == 0 ? true : false);
			}

			// - Reserve function

			// Change the vec_vec_capacity to contains at least n elements.
			// Reallocation only occurs if n is greater than current vec_capacity.
			void	reserve (size_type n) {
				if (n <= this->vec_capacity) {
					return ;
				} else if (n > this->max_size()) {
					throw MaxSizeExceededException();
				}
				size_type	new_vec_capacity = (this->vec_capacity == 0 ? 1 : this->vec_capacity);
				while (new_vec_capacity <= n) {
					new_vec_capacity *= 2;
				}
				if (new_vec_capacity > this->max_size()) {
					throw MaxSizeExceededException();
				}
				value_type*	new_first_elem = alloc.allocate(new_vec_capacity);
				for (size_type i = 0; i < this->filled; i++) {
					this->alloc.construct(new_first_elem + i,
						*(this->first_elem + i));
					this->alloc.destroy(this->first_elem + i);
				}
				this->alloc.deallocate(this->first_elem, this->vec_capacity);
				this->vec_capacity = new_vec_capacity;
				this->first_elem = new_first_elem;
			}

			// ----------------------
			// --- ELEMENT ACCESS ---
			// ----------------------

			reference	operator[] (size_type n) {
				return *(this->first_elem + n);
			}

			const_reference	operator[] (size_type n) const {
				return *(this->first_elem + n);
			}

			reference	at (size_type n) {
				if (n >= this->filled) {
					throw OutOfRangeException();
				}
				return *(this->first_elem + n);
			}

			const_reference	at (size_type n) const {
				if (n >= this->filled) {
					throw OutOfRangeException();
				}
				return *(this->first_elem + n);
			}

			reference	front () {
				return *this->first_elem;
			}

			const_reference	front () const {
				return *this->first_elem;
			}

			reference	back () {
				return *(this->first_elem + this->filled - 1);
			}

			const_reference	back () const {
				return *(this->first_elem + this->filled - 1);
			}

			// -----------------
			// --- MODIFIERS ---
			// -----------------

			// - Fill assign function

			// Replace the contents with count copies of value value.
			// vec_capacity is modified only if count is superior to it.
			void	assign (size_type count, const value_type& value) {
				this->clear();
				if (count > this->vec_capacity) {
					this->alloc.deallocate(this->first_elem, this->vec_capacity);
					this->vec_capacity = count;
					this->first_elem = this->alloc.allocate(this->vec_capacity);
				}
				for (size_type i = 0; i < count; i++) {
					this->alloc.construct(this->first_elem + i, value);
					this->filled++;
				}
			}

			// - Range assign function

			// Replace the contents with copies of those in the range first-last
			// . May cause a reallocation if distance between first and last
			// exceed vec_capacity.
			template <class InputIt>
			void	assign (InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
			{
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				}
				size_type	count = 0;
				InputIt	tmp = first;
				while (tmp != last) {
					++tmp;
					++count;
				}
				if (count > this->max_size()) {
					throw MaxSizeExceededException();
				}
				this->clear();
				if (first == last) {
					return ;
				}
				if (count > this->vec_capacity) {
					this->alloc.deallocate(this->first_elem, this->vec_capacity);
					this->vec_capacity = count;
					this->first_elem = this->alloc.allocate(this->vec_capacity);
				}
				for (size_type i = 0; i < count; i++, first++) {
					this->alloc.construct(this->first_elem + i, *first);
					this->filled++;
				}
			}

			// - Push back function

			// Add an element at the end. May cause a reallocation if vec_capacity
			// is exceeded.
			void	push_back (const value_type& val) {
				if (this->filled == this->vec_capacity) {
					this->reserve(this->filled + 1);
				}
				this->alloc.construct(this->first_elem + this->filled, val);
				this->filled++;
			}

			// - Pop back function

			// Function to delete last element
			void	pop_back() {
				if (this->filled == 0) {
					return;
				}
				this->alloc.destroy(this->first_elem + this->filled - 1);
				this->filled--;
			}

			// - Single element insert function

			// Insert element before the given position. May cause reallocation
			// if vec_capacity is exceeded.
			iterator	insert (iterator position, const value_type& val) {
				size_type	pos = position - this->begin();
				size_type	new_vec_capacity = this->vec_capacity;
				if (this->filled == this->vec_capacity) {
					new_vec_capacity == 0 ? new_vec_capacity = 1 : new_vec_capacity *= 2;
				}
				if (new_vec_capacity > this->max_size()) {
					throw MaxSizeExceededException();
				}
				T*	new_first_elem = this->alloc.allocate(new_vec_capacity);
				this->filled++;
				for (size_type i = 0; i < this->filled; i++) {
					if (i == pos) {
						this->alloc.construct(new_first_elem + i, val);
					}
					else if (i < pos) {
						this->alloc.construct(new_first_elem + i, *(this->first_elem + i));
						this->alloc.destroy(this->first_elem + i);
					}
					else {
						this->alloc.construct(new_first_elem + i, *(this->first_elem + i - 1));
						this->alloc.destroy(this->first_elem + i - 1);
					}
				}
				this->alloc.deallocate(this->first_elem, this->vec_capacity);
				this->vec_capacity = new_vec_capacity;
				this->first_elem = new_first_elem;
				return (this->begin() + pos);
			}

			// - Fill insert function

			// Insert n elements of value val starting from iterator position.
			// May cause reallocation if vec_capacity is exceeded.
			void	insert (iterator position, size_type n, const value_type& value) {
				if (n == 0) {
					return;
				}
				size_type	pos = 	position - this->begin();
				size_type	new_vec_capacity = this->vec_capacity;
				while (this->filled + n > new_vec_capacity) {
					new_vec_capacity == 0 ? new_vec_capacity = 1 : new_vec_capacity *= 2;
				}
				if (new_vec_capacity > this->max_size()) {
					throw MaxSizeExceededException();
				}
				value_type*	new_first_elem = this->alloc.allocate(new_vec_capacity);
				for (size_type i = 0; i < this->filled + n; i++)
				{
					if (i < pos) {
						this->alloc.construct(new_first_elem + i, *(this->first_elem + i));
						this->alloc.destroy(this->first_elem + i);
					}
					else if (i < pos + n) {
						this->alloc.construct(new_first_elem + i, value);
					}
					else {
						this->alloc.construct(new_first_elem + i, *(this->first_elem + i - n));
						this->alloc.destroy(this->first_elem + i - n);
					}
				}
				this->filled += n;
				this->alloc.deallocate(this->first_elem, this->vec_capacity);
				this->vec_capacity = new_vec_capacity;
				this->first_elem = new_first_elem;
			}

			// - Range insert function

			// Insert elements from first to last iterator starting from
			// position. May cause reallocation if vec_capacity is exceeded.
			template <class InputIterator>
			void	insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				if (is_valid_input_iterator(first) == false) {
					throw InvalidIteratorTypeException();
				}
				if (first == last) {
					return ;
				}
				size_type	size = 0;
				InputIterator	tmp = first;
				while (tmp != last) {
					++tmp;
					++size;
				}
				size_type	pos = position - this->begin();
				size_type	new_vec_capacity = this->vec_capacity;
				while (this->filled + size > new_vec_capacity) {
					new_vec_capacity == 0 ? new_vec_capacity = 1 : new_vec_capacity *= 2;
				}
				if (new_vec_capacity > this->max_size()) {
					throw MaxSizeExceededException();
				}
				T*	new_first_elem = this->alloc.allocate(new_vec_capacity);
				for (size_type i = 0; i < this->filled + size; i++) {
					if (i < pos) {
						this->alloc.construct(new_first_elem + i, *(this->first_elem + i));
						this->alloc.destroy(this->first_elem + i);
					}
					else if (i < pos + size) {
						this->alloc.construct(new_first_elem + i, *first);
						first++;
					}
					else {
						this->alloc.construct(new_first_elem + i, *(this->first_elem + i - size));
						this->alloc.destroy(this->first_elem + i - size);
					}
				}
				this->filled += size;
				this->alloc.deallocate(this->first_elem, this->vec_capacity);
				this->vec_capacity = new_vec_capacity;
				this->first_elem = new_first_elem;
			}

			// - Erase single element function

			// Erase a single element of the container pointed by an iterator.
			iterator	erase (iterator position)
			{
				size_type	pos = position - this->begin();
				this->alloc.destroy(this->first_elem + pos);
				this->filled--;
				if (pos != this->filled + 1) {
					for (size_type i = pos; i < this->filled; i++) {
						this->alloc.construct(this->first_elem + i, *(this->first_elem + i + 1));
						this->alloc.destroy(this->first_elem + i);
					}
				}
				return (this->begin() + pos);
			}

			// - Erase multiple element function

			// Erase elements from a range of iterator (first to last).
			iterator	erase (iterator first, iterator last)
			{
				if (first == last)
					return this->begin();
				size_type start = first - this->begin();
				size_type end = last - this->begin();
				size_type size = last - first;
				for (size_type i = start; i < end; i++) {
					this->alloc.destroy(this->first_elem + 1);
				}
				this->filled -= size;
				if (end != this->filled + size)
				{
					for (size_type i = start; i < this->filled; i++) {
						this->alloc.construct(this->first_elem + i, *(this->first_elem + i + size));
						this->alloc.destroy(this->first_elem + i);
					}
				}
				return (this->begin() + start);
			}

			// - Swap function

			// Exchange one container for another.
			void	swap (vector& x)
			{
				if (x == *this) {
					return ;
				}
				size_type	tmp_vec_capacity = this->vec_capacity;
				size_type	tmp_filled = this->filled;
				T*	tmp_first_elem = this->first_elem;
				this->vec_capacity = x.vec_capacity;
				this->filled = x.filled;
				this->first_elem = x.first_elem;
				x.vec_capacity = tmp_vec_capacity;
				x.filled = tmp_filled;
				x.first_elem = tmp_first_elem;
			}

			void	clear ()
			{
				for (size_type i = 0; i < this->filled; i++) {
					this->alloc.destroy(this->first_elem + i);
				}
				this->filled = 0;
			}
	};


	// ----------------------
	// Non member functions :
	// ----------------------

	// - Relational operators functions

	template <typename T, class Alloc>
	bool	operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size()) {
			return false;
		}
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	template <typename T, class Alloc>
	bool	operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	};

	template <typename T, class Alloc>
	bool	operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <typename T, class Alloc>
	bool	operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	};

	template <typename T, class Alloc>
	bool	operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	};

	template <typename T, class Alloc>
	bool	operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	};

	// - Swap function, non member overload
	template <typename T, class Alloc>
	void	swap (vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	};
};

#endif

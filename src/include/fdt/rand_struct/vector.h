#ifndef FDT_RAND_STRUCT_VECTOR_H
#define FDT_RAND_STRUCT_VECTOR_H

#include <memory>
#include <initializer_list>
#include <utility>
#include "fdt/iterator.h"
#include "fdt/exception.h"

namespace fdt {
	template <typename Ty, class Allocator = std::allocator<Ty> >
	class vector {
	public:
		using value_type = Ty;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = rand_iterator<Ty>;
		using const_iterator = const rand_iterator<Ty>;
		using reverse_iterator = reverse_rand_iterator<Ty>;
		using const_reverse_iterator = const reverse_rand_iterator<Ty>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		/**
		 * @brief Default constructor. Allocates a buffer with
		 * a predefined allocation size for more efficient insertion
		 * of further elements in the vector.
		 */
		constexpr vector()
			: _data(AllocTraits::allocate(_alloc, _def_alloc)), _size(0),
			_capacity(_def_alloc)
		{}

		/**
		 * @brief Pre-allocation constructor. Creates a vector of the given
		 * size with preallocated memory. A default preallocation size is
		 * added to the given size in order to allow more efficient insertions
		 * of further elements. The complexity of this container is linear
		 * in the specified size.
		 */
		constexpr vector(std::size_t n)
			: _data(AllocTraits::allocate(_alloc, _def_alloc + n)), _size(n),
			_capacity(_def_alloc + n)
		{
			for (size_t i = 0; i < _size; ++i)
				AllocTraits::construct(_alloc, _data + i);
		}

		/**
		 * @brief Copy constructor. Copies the content of another vector
		 * preserving the data stored inside the container. The complexity of
		 * this constructor is linear in size of the vector.
		 */
		constexpr vector(const vector& other)
			: _data(AllocTraits::allocate(_alloc, other._capacity)),
			_size(other._size),
			_capacity(other._capacity)
		{
			for (size_t i = 0; i < other.size(); ++i)
				AllocTraits::construct(_alloc, _data + i, other[i]);
		}

		/**
		 * @brief Move constructor. Moves the pointer of another vector
		 * provided as rvalue-reference, avoiding unnecessary copies
		 * wherever the content of the "original" container must not
		 * be preserved. The complexity of this constructor is constant.
		 * 
		 */
		constexpr vector(vector&& other)
			: _data(std::move(other._data)),
			_size(other._size), _capacity(other._capacity)
		{
			other._data = nullptr;
			other._size = 0;
			other._capacity = 0;
		}

		/**
		 * @brief Initializer list constructor. Takes an initializer
		 * list which will be used to initialize the content of the
		 * container, provided that the specified literal values are
		 * type-compliant with the template type parameter of the
		 * vector. The complexity of this constructor is linear in
		 * length of the initializer list.
		 */
		constexpr vector(const std::initializer_list<Ty>& ilist)
			: _data(AllocTraits::allocate(_alloc, _def_alloc + ilist.size())),
			_size(ilist.size()), _capacity(_def_alloc + ilist.size())
		{

			for (size_t i = 0; i < ilist.size(); ++i)
				AllocTraits::construct(_alloc, _data + i,
					*(ilist.begin() + i));
		}

		/**
		 * @brief Assigns another vector to this instance copying
		 * the contents of the other container and preserving the
		 * original object. The complexity of this operator call
		 * is linear in the size of the vector.
		 * @param other vector to copy-assign.
		 * @return constexpr reference assigned vector. 
		 */
		constexpr vector& operator=(const vector& other)
		{
			if (_capacity < other._capacity) {
				AllocTraits::deallocate(_alloc, _data, _capacity);
				_data = AllocTraits(_alloc, other._capacity);
				_capacity = other._capacity;
			}
			_size = other._size;
			for (size_t i = 0; i < _size; ++i)
				AllocTraits::construct(_alloc, _data + i, other[i]);
			return *this;
		}

		/**
		 * @brief Assigns another vector to this instanche using move
		 * semantics. The pointer to the unerlying data structure is moved
		 * and the other object is reset to an empty state. The complexity
		 * of this operator call is constant.
		 * @param other 
		 * @return constexpr reference 
		 */
		constexpr vector& operator=(vector&& other)
		{
			_data = std::move(other._data);
			other._data = nullptr;
			_capacity = other._capacity;
			_size = other._capacity;
			other._capacity = 0;
			other._size = 0;
			return *this;
		}

		~vector()
		{
			AllocTraits::deallocate(_alloc, _data, _capacity);
		}

		/**
		 * @brief Returns a boolean after checking if the vector is
		 * empty. 
		 * @return true if vector is empty.
		 * @return false if vector is not empty.
		 */
		[[nodiscard]]
		constexpr bool empty() const noexcept { return _size == 0 || _capacity == 0; }

		/**
		 * @brief Returns the size of the vector (number of elements).
		 * @return constexpr size_type size of vector.
		 */
		constexpr size_type size() const { return _size; }
		
		/**
		 * @brief Returns the capacity of the vector, which represents
		 * the number of allocated slots able to store elements. Usually,
		 * memory locations past size() are not initialized or constructed.
		 * @return constexpr size_type capacity of the vector.
		 */
		constexpr size_type capacity() const { return _capacity; }

		/**
		 * @brief Returns the first element of the vector.
		 * @return constexpr reference to the first element of the vector.
		 */
		constexpr reference front() { return *_data; }
		constexpr const_reference front() const { return *_data; }

		/**
		 * @brief Returns the last element of the vector.
		 * @return constexpr reference to the last element of the vector.
		 */
		constexpr reference back() { return *(_data + _size - 1); }
		constexpr const_reference back() const { return *(_data + _size - 1); }

		/**
		 * @brief Returns a pointer to the underlying data structure
		 * containing all the elements of the vector.
		 * @return constexpr pointer to the underlying memory area.
		 */
		constexpr pointer data() { return _data; }
		constexpr const_pointer data() const { return _data; }

		/**
		 * @brief Returns an element with position i using bounds-checked
		 * array access. An exception of type array_out_of_range() is thrown
		 * if i is out of bounds.
		 * @param i position.
		 * @return constexpr reference to the element.
		 */
		constexpr reference at(size_t i)
		{
			if (i >= _size) throw array_out_of_range();
			return *(_data + i);
		}
		constexpr const_reference at(size_t i) const
		{
			if (i >= _size) throw array_out_of_range();
			return *(_data + i);
		}

		/**
		 * @brief Returns an element with position i.
		 * @param i position.
		 * @return constexpr reference to the element.
		 */
		constexpr reference operator[](size_t i) noexcept
		{
			return *(_data + i);
		}
		constexpr const_reference operator[](size_t i) const noexcept
		{
			return *(_data + i);
		}

		/**
		 * @brief Returns an iterator to the beginning of the vector.
		 * @return constexpr iterator value to the start of the vector.
		 */
		constexpr iterator begin() { return iterator(_data); }
		constexpr const_iterator begin() const noexcept
		{
			return iterator(_data);
		}

		/**
		 * @brief Returns a constant iterator to the beginning of the vector.
		 * @return constexpr const_iterator value to the start of the vector.
		 */
		constexpr const_iterator cbegin() const noexcept
		{
			return iterator(_data);
		}

		/**
		 * @brief Returns an iterator to the end of the vector.
		 * @return constexpr iterator value to the end of the vector.
		 */
		constexpr iterator end() { return iterator(_data + _size); }

		constexpr const_iterator end() const noexcept
		{
			return iterator(_data + _size);
		}

		/**
		 * @brief Returns a constant iterator to the end of the vector.
		 * @return constexpr const_iterator value to the end of the vector.
		 */
		constexpr const_iterator cend() const noexcept
		{
			return iterator(_data + _size);
		}

		/**
		 * @brief Returns a reverse iterator to the beginning of the vector.
		 * @return constexpr reverse_iterator value to the start of the vector.
		 */
		constexpr reverse_iterator rbegin() { return reverse_iterator(_data + _size - 1); }
		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return reverse_iterator(_data + _size - 1);
		}

		/**
		 * @brief Returns a constant reverse iterator to the beginning of the
		 * vector.
		 * @return constexpr const_reverse_iterator value to the start of the
		 * vector.
		 */
		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return reverse_iterator(_data + _size - 1);
		}

		/**
		 * @brief Returns a reverse iterator to the end of the vector.
		 * @return constexpr reverse_iterator value to the end of the vector.
		 */
		constexpr reverse_iterator rend() { return reverse_iterator(_data); }
		constexpr const_reverse_iterator rend() const noexcept
		{
			return reverse_iterator(_data);
		}

		/**
		 * @brief Returns a constant reverse iterator to the end of the vector.
		 * @return constexpr const_reverse_iterator value to the end of the
		 * vector.
		 */
		constexpr const_reverse_iterator crend() const noexcept
		{
			return reverse_iterator(_data);
		}

		/**
		 * @brief Preallocates n elements in order to speed up insertions
		 * using push_back and emplace_back functions. The complexity
		 * of this function call is, at most, linear in size of n.
		 * @param n number of slots to preallocate.
		 */
		constexpr void reserve(size_t n)
		{
			if (n <= _capacity) return;
			auto* a = _data;
			a = AllocTraits::allocate(_alloc, n);

			// copying vector elements into new buffer
			std::copy(_data, _data + _size, a);

			// de-allocating old buffer
			AllocTraits::deallocate(_alloc, _data, _capacity);
			_capacity = n;
			_data = a;
		}

		/**
		 * @brief Resizes the vector to the given size. If the provided value
		 * is larger than the vector's current size, a reallocation happens
		 * automatically. If the provided value is smaller than the current
		 * size, size is set and elements past its index are discarded.
		 * @param n new size of the vector.
		 */
		constexpr void resize(size_t n)
        {
		    if (n <= _size) {
		        _size = n;
		        return;
		    }

		    reserve(n * 2);
		    _size = n;
        }

		/**
		 * @brief Resizes the vector in order to perfectly fit the number of
		 * elements inside the container. It is not recommended to call
		 * shrink_to_fit() if a large number of insertions is planned in the
		 * future, because it will perform relocations, decreasing the
		 * container's efficiency.
		 */
		constexpr void shrink_to_fit()
		{
			if (_size == _capacity) return;
			auto* a = _data;

			a = AllocTraits::allocate(_alloc, _size);
			std::copy(_data, _data + _size, a);

			AllocTraits::deallocate(_alloc, _data, _capacity);
			_capacity = _size;
			_data = a;
		}

		/**
		 * @brief Adds an element of the given value to the end of the vector.
		 * @param value element to add to the end of the vector.
		 */
        constexpr void push_back(const Ty& value)
        {
		    if (_size + 1 < _capacity) {
		        _size++;
		        AllocTraits::construct(_alloc, _data + _size - 1, value);
		    } else {
		        reserve(_capacity * 2);
		        _size++;
		        AllocTraits::construct(_alloc, _data + _size - 1, value);
		    }
        }

		/**
		 * @brief Constructs a new element at the end of the vector.
		 * @tparam Args variadic template parameter of constructor arguments.
		 * @param args variadic constructor arguments.
		 * @return constexpr reference to the constructed element.
		 */
        template <typename... Args>
        constexpr reference emplace_back(Args&&... args)
        {
		    if (_size + 1 < _capacity) {
		        _size++;
				AllocTraits::construct(_alloc, _data + _size - 1, 
					std::forward<Args>(args)...);
				return *(_data + _size - 1);
		    } else {
		        reserve(_capacity * 2);
		        _size++;
				AllocTraits::construct(_alloc, _data + _size - 1,
					std::forward<Args>(args)...);
				return *(_data + _size - 1);
		    }
        }

		/**
		 * @brief Removes an element at the end of the vector by decreasing
		 * the vector's size. This operation has constant complexity.
		 */
        constexpr void pop_back()
        {
		    _size--;
        }

		/**
		 * @brief swaps the contents of another vector with the current instance of
		 * the vector
		 * @param other another vector instance to swap elements with.
		 */
        constexpr void swap(vector& other) noexcept
        {
			if (other._size > _size) resize(other._size);
            for (size_t i = 0; i < _size; ++i)
                std::swap(*(_data + i), *(other._data + i));
			std::swap(_size, other._size);
        }

	private:
		const size_type _def_alloc = 8;
		Ty* _data = nullptr;
		size_type _size;
		size_type _capacity;
		Allocator _alloc;
		using AllocTraits = std::allocator_traits<Allocator>;
	};

	/**
	 * @brief Lexicographically compares the values of two different vectors
	 * to check if they are equal.
	 * @tparam Ty deduced type of the container.
	 * @param l vector container.
	 * @param r vector container.
	 * @return true if the elements inside the vector are all equal.
	 * @return false if the elements inside the vector are different.
	 */
	template <typename Ty>
	constexpr bool operator==(const vector<Ty>& l, const vector<Ty>& r)
	{
		if (l.data() == nullptr || r.data() == nullptr) return false;
		if (l.size() != r.size()) return false;
		for (size_t i = 0; i < l.size(); ++i)
			if (l[i] != r[i]) return false;
		return true;
	}

	template <typename Ty>
	constexpr bool operator!=(const vector<Ty>& l, const vector<Ty>& r)
	{
		return !(l == r);
	}

	/**
	 * @brief Performs the summation of two vectors, provided that the type
	 * of the container is arithmetic-compliant or provides correctly
	 * overloaded operators.
	 * @tparam Ty deduced type of the container.
	 * @param l vector.
	 * @param r vector.
	 * @return constexpr auto new vector containing the summation result.
	 */
	template <typename Ty>
	constexpr auto operator+(const vector<Ty>& l, const vector<Ty>& r)
	{
		if (l.size() != r.size()) throw vector_size_mismatch();
		vector<Ty> sum;
		for (size_t i = 0; i < l.size(); ++i)
			sum.emplace_back(l[i] + r[i]);
		return sum;
	}

	/**
	 * @brief Performs the subtraction of two vectors, provided that the type
	 * of the container is arithmetic-compliant or provides correctly
	 * overloaded operators.
	 * @tparam Ty deduced type of the container.
	 * @param l vector.
	 * @param r vector.
	 * @return constexpr auto new vector containing the subtraction result.
	 */
	template <typename Ty>
	constexpr auto operator-(const vector<Ty>& l, const vector<Ty>& r)
	{
		if (l.size() != r.size()) throw vector_size_mismatch();
		vector<Ty> sum;
		for (size_t i = 0; i < l.size(); ++i)
			sum.emplace_back(l[i] - r[i]);
		return sum;
	}
}

#endif

#ifndef FDT_RANDOM_ARRAY_H
#define FDT_RANDOM_ARRAY_H

#include <memory>
#include <algorithm>
#include <initializer_list>
#include <cstddef>
#include "iterator.h"
#include "exception.h"

namespace fdt {
	
	/**
	 * @brief Static array container. Provides safe access to a standard
	 * stack allocated static array. Size is provided as a template parameter
	 * and is, therefore, part of the type.
	 * @tparam Ty type of the container.
	*/
	template <typename Ty, std::size_t Size>
	class array {
	public:
		using value_type = Ty;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = rand_iterator<Ty>;
		using const_iterator = rand_iterator<Ty>;
		using reverse_iterator = reverse_rand_iterator<Ty>;
		using const_reverse_iterator = const reverse_rand_iterator<Ty>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		constexpr array() = default;

		/**
		 * @brief Copies data from another instance into the current instance
		 * of array.
		 * @param other another array instance. 
		*/
		constexpr array(const array& other)
		{
			std::copy(
				std::begin(other._data), std::begin(other._data) + Size, _data); 
		}

		/**
		 * @brief Copies another instance of array using move semantics.
		 * @param other another array instance
		*/
		constexpr array(array&& other) : _data(std::move(other._data)) {}

		/**
		 * @brief Initializes the array using an std::initializer_list constructor.
		 * @param ilist initializer list with array elements.
		*/
		constexpr array(const std::initializer_list<Ty>& ilist)
		{
			std::copy(ilist.begin(), ilist.end(), _data);
		}

		/**
		 * @brief Returns the size of the array.
		 * @return size_type containing the size of the array.
		*/
		constexpr auto size() const noexcept { return Size; }

		/**
		* @brief Checks if the array is empty.
		* @return true if the size is 0, false otherwise.
		*/
		[[nodiscard]]
		constexpr bool empty() const noexcept { return Size == 0; }

		/**
		 * @brief Returns the first element of the array.
		 * @return a reference to the first element of the array.
		*/
		constexpr reference front() { return *_data; }

		constexpr const_reference front() const { return *_data; }

		/**
		 * @brief Returns the last element of the array.
		 * @return a reference to the last element of the array.
		*/
		constexpr reference back() { return *(_data + (Size - 1)); }

		constexpr const_reference back() const { return *(_data + (Size - 1)); }

		/**
		 * @brief Returns a pointer to the underlying array.
		 * @return pointer to the underlying array.
		*/
		constexpr pointer data() { return _data; }

		constexpr const_pointer data() const { return _data; }

		/**
		 * @brief Returns the element at the specified position.
		 * @param i index.
		 * @return the element at array[i].
		*/
		constexpr reference operator[](size_t i) { return *(_data + i); }

		constexpr const_reference operator[](size_t i) const { return *(_data + i); }
		
		/**
		 * @brief Returns the element at the specified position, throwing an
		 * exception if the access is out of bounds.
		 * @param i index.
		 * @return the element at array[i].
		*/
		constexpr reference at(size_t i)
		{
			if (i >= Size) throw array_out_of_range();
			return *(_data + i);
		}

		constexpr const_reference at(size_t i) const
		{	
			if (i >= Size) throw array_out_of_range();
			return *(_data + i);
		}
		
		/**
		 * @brief Returns an iterator to the beginning of the array.
		 * @return random access iterator to the beginning of the array.
		*/
		constexpr iterator begin()
		{
			return iterator(_data);
		}

		constexpr const_iterator begin() const
		{
			return iterator(_data);
		}

		constexpr const_iterator cbegin() const
		{
			return iterator(_data);
		}

		/**
		 * @brief Returns an iterator to the end of the array.
		 * @return random access iterator to the end of the array.
		*/
		constexpr iterator end()
		{
			return iterator(_data + Size);
		}

		constexpr const_iterator end() const
		{
			return iterator(_data + Size);
		}

		constexpr const_iterator cend() const
		{
			return iterator(_data + Size);
		}

		/**
		 * @brief Returns a reverse iterator to the (reverse) beginning
		 * of the array.
		 * @return reverse random access iterator to the (reverse) beginning
		 * of the array.
		*/
		constexpr reverse_iterator rbegin()
		{
			return reverse_iterator(_data + Size - 1);
		}

		constexpr const_reverse_iterator rbegin() const
		{
			return reverse_iterator(_data + Size - 1);
		}

		constexpr const_reverse_iterator crbegin() const
		{
			return reverse_iterator(_data + Size - 1);
		}

		/**
		 * @brief Returns an iterator to the (reverse) end of the array.
		 * @return reverse random access iterator to the (reverse)
		 * end of the array.
		*/
		constexpr reverse_iterator rend()
		{
			return reverse_iterator(_data);
		}

		constexpr const_reverse_iterator rend() const
		{
			return reverse_iterator(_data);
		}

		constexpr const_reverse_iterator crend() const
		{
			return reverse_iterator(_data);
		}

		/**
		 * @brief Fills the array with the given value.
		 * @param value used to fill the array.
		*/
		constexpr void fill(const Ty& value)
		{
			std::fill_n(_data, Size, value);
		}

		/**
		 * @brief Swaps the array content with another array instance.
		 * @param other another array instance.
		*/
		constexpr void swap(array& other)
		{
			std::swap(other._data, _data);
		}

		constexpr array& operator=(const array& other)
		{
			array copy(other);
			copy.swap(*this);
			return *this;
		}

		constexpr array& operator=(array&& other)
		{
			array copy(std::move(other));
			copy.swap(*this);
			return *this;
		}

	private:
		Ty _data[Size];
	};

	template <typename Ty, std::size_t N>
	constexpr bool operator==(const array<Ty, N>& l, const array<Ty, N>& r)
	{
		for (size_t i = 0; i < N; ++i)
			if (l[i] != r[i]) return false;
		return true;
	}

	template <typename Ty, std::size_t N>
	constexpr bool operator!=(const array<Ty, N>& l, const array<Ty, N>& r)
	{
		return !(l == r);
	}
}

#endif

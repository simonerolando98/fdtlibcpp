#ifndef FDT_RAND_STRUCT_ARRAY_H
#define FDT_RAND_STRUCT_ARRAY_H

#include <memory>
#include <algorithm>
#include <initializer_list>
#include <cstddef>
#include "fdt/iterator.h"
#include "fdt/exception.h"

namespace fdt {
	
	template <typename Ty, std::size_t Size>
	class array {
	public:
		using value_type = Ty;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = fdt::rand_iterator<Ty>;
		using const_iterator = fdt::rand_iterator<Ty>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		constexpr array() = default;

		constexpr explicit array(const array& other)
		{
			std::copy(
				std::begin(other._data), std::begin(other._data) + Size, _data); 
		}

		constexpr explicit array(array&& other) : _data(std::move(other._data)) {}

		constexpr explicit array(const std::initializer_list<Ty>& list)
		{
			std::copy(list.begin(), list.end(), _data);
		}

		constexpr auto size() const { return Size; }

		constexpr bool empty() const { return Size == 0; };

		constexpr reference front() { return *_data; }
		constexpr const_reference front() const { return *_data; }

		constexpr reference back() { return *(_data + (Size - 1)); }
		constexpr const_reference back() const { return *(_data + (Size - 1)); }

		constexpr pointer data() { return _data; }
		constexpr const_pointer data() const { return _data; }

		[[nodiscard]]
		constexpr reference operator[](size_t i) { return *(_data + i); }
		[[nodiscard]]
		constexpr const_reference operator[](size_t i) const { return *(_data + i); }
		
		[[nodiscard]]
		constexpr reference at(size_t i)
		{
			if (i >= Size) throw array_out_of_range();
			return *(_data + i);
		}
		[[nodiscard]]
		constexpr const_reference at(size_t i) const
		{	
			if (i >= Size) throw array_out_of_range();
			return *(_data + i);
		}
		
		[[nodiscard]]
		constexpr iterator begin()
		{
			return iterator(_data);
		}
		[[nodiscard]]
		constexpr const_iterator begin() const
		{
			return iterator(_data);
		}
		[[nodiscard]]
		constexpr const_iterator cbegin() const
		{
			return iterator(_data);
		}

		[[nodiscard]]
		constexpr iterator end()
		{
			return iterator(_data + Size);
		}
		[[nodiscard]]
		constexpr const_iterator end() const
		{
			return iterator(_data + Size);
		}
		[[nodiscard]]
		constexpr const_iterator cend() const
		{
			return iterator(_data + Size);
		}

		constexpr void fill(const Ty& value)
		{
			std::fill_n(_data, Size, value);
		}

		constexpr void swap(array& other)
		{
			for (size_t i = 0; i < Size; ++i) std::swap(_data + i, other._data + i);
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
}

#endif

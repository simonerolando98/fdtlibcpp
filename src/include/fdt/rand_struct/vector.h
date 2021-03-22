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
		using reverse_iterator = rand_iterator<Ty>;
		using const_reverse_iterator = const rand_iterator<Ty>;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		constexpr vector()
			: _data(AllocTraits::allocate(_alloc, _def_alloc)), _size(0),
			_capacity(_def_alloc)
		{}

		constexpr explicit vector(std::size_t n)
			: _data(AllocTraits::allocate(_alloc, _def_alloc + n)), _size(n),
			_capacity(_def_alloc + n)
		{}

		constexpr vector(const vector& other)
			: _data(AllocTraits::allocate(_alloc, other._capacity)),
			_size(other._size),
			_capacity(other._capacity)
		{
			for (size_t i = 0; i < other.size(); ++i)
				AllocTraits::construct(_alloc, _data + i, other[i]);
		}

		constexpr vector(vector&& other)
			: _data(std::move(other._data)),
			_size(other._size), _capacity(other._capacity)
		{
			other._data = nullptr;
			other._size = 0;
			other._capacity = 0;
		}

		constexpr vector(const std::initializer_list<Ty>& ilist)
			: _data(AllocTraits::allocate(_alloc, _def_alloc + ilist.size())),
			_size(ilist.size()), _capacity(_def_alloc + ilist.size())
		{

			for (size_t i = 0; i < ilist.size(); ++i)
				AllocTraits::construct(_alloc, _data + i,
					*(ilist.begin() + i));
		}

		constexpr auto operator=(const vector& other)
		{
			if (_capacity < other._capacity) {
				AllocTraits::deallocate(_alloc, _data, _capacity);
				_data = AllocTraits(_alloc, other._capacity);
				_capacity = other._capacity;
			}
			_size = other._size;
			for (size_t i = 0; i < _size; ++i)
				AllocTraits::construct(_alloc, _data + i, other[i]);
		}

		constexpr auto operator=(vector&& other)
		{
			_data = std::move(other._data);
			other._data = nullptr;
			_capacity = other._capacity;
			_size = other._capacity;
			other._capacity = 0;
			other._size = 0;
		}

		~vector()
		{
			AllocTraits::deallocate(_alloc, _data, _capacity);
		}

		constexpr bool empty() const { return _size == 0 || _capacity == 0; }

		constexpr size_type size() const { return _size; }
		
		constexpr size_type capacity() const { return _capacity; }

		[[nodiscard]]
		constexpr reference front() { return *_data; }
		[[nodiscard]]
		constexpr const_reference front() const { return *_data; }

		[[nodiscard]]
		constexpr reference back() { return *(_data + _size - 1); }
		[[nodiscard]]
		constexpr const_reference back() const { return *(_data + _size - 1); }
		
		[[nodiscard]]
		constexpr pointer data() { return _data; }
		[[nodiscard]]
		constexpr const_pointer data() const { return _data; }
	
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

		constexpr reference operator[](size_t i) noexcept
		{
			return *(_data + i);
		}
		constexpr const_reference operator[](size_t i) const noexcept
		{
			return *(_data + i);
		}

		constexpr iterator begin() { return iterator(_data); }
		constexpr const_iterator begin() const noexcept
		{ return iterator(_data); }
		constexpr const_iterator cbegin() const noexcept
		{ return iterator(_data); }

		constexpr iterator end() { return iterator(_data + _size); }
		constexpr const_iterator end() const noexcept
		{ return iterator(_data + _size); }
		constexpr const_iterator cend() const noexcept
		{ return iterator(_data + _size); }

		constexpr reverse_iterator rbegin() { return iterator(_data + _size); }
		constexpr const_reverse_iterator rbegin() const noexcept
		{ return reverse_iterator(_data + _size); }
		constexpr const_reverse_iterator crbegin() const noexcept
		{ return reverse_iterator(_data + _size); }

		constexpr reverse_iterator rend() { return reverse_iterator(_data); }
		constexpr const_reverse_iterator rend() const noexcept
		{ return reverse_iterator(_data); }
		constexpr const_reverse_iterator crend() const noexcept
		{ return reverse_iterator(_data); }

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

		constexpr void resize(size_t n)
        {
		    if (n <= _size) {
		        _size = n;
		        return;
		    }

		    reserve(n * 2);
		    _size = n;
        }

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

        constexpr void pop_back()
        {
		    _size--;
        }

        constexpr void swap(vector& other) noexcept
        {
            for (size_t i = 0; i < _size; ++i)
                std::swap(*(_data + i), *(other._data + i));
        }

	private:
		const size_type _def_alloc = 8;
		Ty* _data = nullptr;
		size_type _size;
		size_type _capacity;
		Allocator _alloc;
		using AllocTraits = std::allocator_traits<Allocator>;
	};

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
	constexpr auto operator+(const vector<Ty>& l, const vector<Ty>& r)
	{
		if (l.size() != r.size()) throw vector_size_mismatch();
		vector<Ty> sum;
		for (size_t i = 0; i < l.size(); ++i)
			sum.emplace_back(l[i] + r[i]);
		return sum;
	}

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

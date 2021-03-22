#ifndef FDT_RAND_STRUCT_DARRAY_H
#define FDT_RAND_STRUCT_DARRAY_H

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
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		constexpr vector()
		{ 
			_data = _allocator.allocate(_real_alloc, _def_alloc);
			_size = 0;
			_capacity = _def_alloc;
		}

		constexpr explicit vector(std::size_t n)
		{
			_data = _allocator.allocate(_real_alloc, n + _def_alloc);
			_size = n;
			_capacity = _def_alloc + n;
		}

		constexpr explicit vector(const std::initializer_list<Ty>& list)
		{
			_data = _allocator.allocate(_real_alloc, _def_alloc + list.size());
			_size = list.size();
			_capacity = list.size() + _def_alloc;
			std::copy(std::begin(list), std::end(list), _data);
		}

		~vector()
		{
			_allocator.deallocate(_real_alloc, _data, _capacity);
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
		constexpr const_iterator begin() const { return iterator(_data); }
		constexpr const_iterator cbegin() const { return iterator(_data); }

		constexpr iterator end() { return iterator(_data + _size); }
		constexpr const_iterator end() const { return iterator(_data + _size); }
		constexpr const_iterator cend() const { return iterator(_data + _size); }

		constexpr void reserve(size_t n)
		{
			if (n <= _capacity) return;
			auto a = _data;
			a = _allocator.allocate(_real_alloc, n);

			// copying vector elements into new buffer
			std::copy(_data, _data + _size, a);

			// deallocating old buffer
			_allocator.deallocate(_real_alloc, _data, _capacity);
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

        constexpr void push_back(const Ty& value)
        {
		    if (_size + 1 < _capacity) {
		        _size++;
		        _data[_size - 1] = value;
		    } else {
		        reserve(_capacity * 2);
		        _size++;
		        _data[_size - 1] = value;
		    }
        }

        template <typename... Args>
        constexpr reference emplace_back(Args&&... args)
        {
		    if (_size + 1 < _capacity) {
		        _size++;
				new (_data + _size - 1) value_type(std::forward<Args>(args)...);
				//_allocator.construct(_real_alloc, _data + _size - 1, std::forward<Args>(args)...);
				return *(_data + _size - 1);
		    } else {
		        reserve(_capacity * 2);
		        _size++;
				new (_data + _size - 1) value_type(std::forward<Args>(args)...);
		        //_allocator.construct(_real_alloc, _data + _size - 1, std::forward<Args>(args)...);
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
		Ty* _data;
		size_type _size;
		size_type _capacity;
		std::allocator_traits<Allocator> _allocator;
		Allocator _real_alloc;
	};
}

#endif

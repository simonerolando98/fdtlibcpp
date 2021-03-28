#ifndef FDT_SEQUENTIAL_SINGLY_LINKED_LIST_H
#define FDT_SEQUENTIAL_SINGLY_LINKED_LIST_H

#include <cstddef>
#include <memory>
#include <utility>
#include <algorithm>
#include "utility.h"
#include "iterator.h"

namespace fdt {
	template <typename Tx>
	struct fwd_list_node {
	public:
		using value_type = Tx;

		constexpr fwd_list_node() : _next(nullptr) {}

		constexpr fwd_list_node(const Tx& data, fwd_list_node<Tx>* next = nullptr)
			: _data(data), _next(next) {}

		template <typename... Args>
		constexpr explicit fwd_list_node(Args&&... args, fwd_list_node<Tx>* next = nullptr)
			: _data(std::forward<Args>(args)...), _next(next) {}

		Tx _data;
		fwd_list_node<Tx>* _next;
	};

	template <typename Ty, 
		typename Allocator = std::allocator<fwd_list_node<Ty> > >
	class singly_linked_list {
	public:
		using value_type = Ty;
		using size_type = std::size_t;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = forward_list_iterator<fwd_list_node<Ty> >;
		using const_iterator = const forward_list_iterator<fwd_list_node<Ty> >;
		using allocator_type = Allocator;

		constexpr singly_linked_list() : _list(nullptr), _size(0) {}

		constexpr singly_linked_list(const singly_linked_list<Ty>& other)
		{
			_list = nullptr;
			_size = 0;
			for (auto x : other) emplace_back(x);
		}

		constexpr singly_linked_list(singly_linked_list&& other)
			: _list(std::move(other._list)), _size(other._size)
		{
			other._list = nullptr;
			other._size = 0;
		}

		constexpr singly_linked_list& operator=(const singly_linked_list& other)
		{
			singly_linked_list copy(other);
			copy.swap(*this);
			return *this;
		}

		constexpr singly_linked_list& operator=(singly_linked_list&& other)
		{
			singly_linked_list copy(std::move(other));
			copy.swap(*this);
			return *this;
		}
		
		~singly_linked_list()
		{
			_list_destroy_clear();
		}

		constexpr allocator_type get_allocator() const noexcept
		{
			return _alloc;
		}

		[[nodiscard]]
		constexpr bool empty() const noexcept { return _size == 0 && is_null(_list); }

		constexpr size_type size() const noexcept { return _size; }

		constexpr void clear() { _list_destroy_clear(); }

		constexpr void push_front(const Ty& data)
		{
			if (is_null(_list)) {
				_list = allocator_traits::allocate(_alloc, 1);
				allocator_traits::construct(_alloc, _list, data);
				_size++;
			}
			else {
				auto n = allocator_traits::allocate(_alloc, 1);
				allocator_traits::construct(_alloc, n, data, _list);
				_list = n;
				_size++;
			}
		}

		template <typename... Args>
		constexpr void emplace_front(Args&&... args)
		{
			if (is_null(_list)) {
				_list = allocator_traits::allocate(_alloc, 1);
				allocator_traits::construct(_alloc, _list, std::forward<Args>(args)...);
				_size++;
			}
			else {
				auto n = _list = allocator_traits::allocate(_alloc, 1);
				allocator_traits::construct(_alloc, n, std::forward<Args>(args)..., _list);
				_list = n;
				_size++;
			}
		}

		constexpr void push_back(const Ty& data)
		{
			if (is_null(_list)) push_front(data);
			else {
				auto iter = _list;
				for (; !is_null(iter->_next); iter = iter->_next);
				iter->_next = allocator_traits::allocate(_alloc, 1);
				allocator_traits::construct(_alloc, iter->_next, data);
			}
		}

		template <typename... Args>
		constexpr void emplace_back(Args&&... args)
		{
			if (is_null(_list)) emplace_front(std::forward<Args>(args)...);
			else {
				auto iter = _list;
				for (; !is_null(iter->_next); iter = iter->_next);
				iter->_next = allocator_traits::allocate(_alloc, 1);
				allocator_traits::construct(_alloc, iter->_next, std::forward<Args>(args)...);
				_size++;
			}
		}

		constexpr iterator begin() noexcept { return iterator(_list); }
		constexpr const_iterator begin() const noexcept { return iterator(_list); }

		constexpr iterator end() noexcept { return iterator(nullptr); }
		constexpr const_iterator end() const noexcept { return iterator(nullptr); }

		constexpr reference front() { return _list->_data; }
		constexpr const_reference front() const { return _list->_data; }

		constexpr reference back()
		{
			auto list = _list;
			for (; !is_null(list->_next); list = list->_next);
			return list->_data;
		}
		constexpr const_reference back() const
		{
			auto list = _list;
			for (; !is_null(list->_next); list = list->_next);
			return list->_data;
		}

		constexpr void swap(singly_linked_list& other) noexcept
		{
			std::swap(other._list, _list);
			std::swap(other._size, _size);
			std::swap(other._alloc, _alloc);
		}

	private:
		constexpr void _list_destroy_clear()
		{
			if (is_null(_list)) return;
			auto iter = _list;
			while (!is_null(iter)) {
				auto tmp = iter;
				iter = iter->_next;
				allocator_traits::deallocate(_alloc, tmp, 1);
			}
			_list = nullptr;
			_size = 0;
		}

        friend class forward_list_iterator<fwd_list_node<Ty> >;
		using _list_type = fwd_list_node<Ty>*;
		using allocator_traits = std::allocator_traits<Allocator>;
		allocator_type _alloc;
		_list_type _list;
		std::size_t _size;
	};
}

#endif

#ifndef FDT_LIST_SINGLY_LINKED_LIST_H
#define FDT_LIST_SINGLY_LINKED_LIST_H

#include <cstddef>
#include <memory>
#include <utility>
#include <algorithm>
#include "fdt/utility.h"
#include "fdt/iterator.h"

namespace fdt {
	/// <summary>
	/// Linked list template implementation.
	/// </summary>
	/// <typeparam name="Ty">Type parameter.</typeparam>
	template <class Ty>
	class singly_linked_list {
	public:
		/// <summary>
		/// Linked list data node implementation.
		/// </summary>
		/// <typeparam name="Ty">Linked list payload data.</typeparam>
        template <class Tx = Ty>
		class fwd_list_node {
		public:
			using value_type = Tx;

			constexpr fwd_list_node() : _next(nullptr) {}

			constexpr explicit fwd_list_node(const Tx& data, fwd_list_node<Tx>* next = nullptr)
				: _data(data), _next(next) {}

			template <typename... Args>
			constexpr explicit fwd_list_node(Args&&... args, fwd_list_node<Tx>* next = nullptr)
				: _data(std::forward<Args>(args)...), _next(next) {}
		private:
			friend class singly_linked_list<Tx>;
            friend class forward_list_iterator<fwd_list_node>;
            Tx _data;
			fwd_list_node<Tx>* _next;
		};

		using value_type = Ty;
		using size_type = std::size_t;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = forward_list_iterator<fwd_list_node<Ty> >;
		using const_iterator = const forward_list_iterator<fwd_list_node<Ty> >;

		/// <summary>
		/// 
		/// </summary>
		constexpr singly_linked_list() : _list(nullptr), _size(0) {}

		/// <summary>
		/// Standard copy constructor.
		/// </summary>
		/// <param name="other">another linked list object to be copied.</param>
		singly_linked_list(const singly_linked_list<Ty>& other)
		{
			_list = nullptr;
			_size = 0;
			for (auto x : other) emplace_back(x);
		}

		/// <summary>
		/// Standard move constructor.
		/// </summary>
		/// <param name="other">rvalue reference to another
		/// list object to be moved.</param>
		explicit singly_linked_list(singly_linked_list&& other)
			: _list(std::move(other._list)), _size(other._size)
		{
			other._list = nullptr;
			other._size = 0;
		}
		
		~singly_linked_list()
		{
			_list_destroy_clear();
		}

		/// <summary>
		/// Returns true if the list, otherwise false.
		/// </summary>
		/// <returns>a boolean representing the status of the list.</returns>
		constexpr bool empty() const { return _size == 0 && is_null(_list); }

		/// <summary>
		/// Returns the size of the list.
		/// </summary>
		/// <returns>a size_t value representing the size of the list
		/// in number of nodes.</returns>
		constexpr size_type size() const { return _size; }

		/// <summary>
		/// Clears the list, freeing memory and deleting its content.
		/// </summary>
		constexpr void clear() { _list_destroy_clear(); }

		/// <summary>
		/// Adds an element to the front of the list.
		/// This operation has O(1) complexity.
		/// </summary>
		/// <param name="data">data to be added to the list node.</param>
		constexpr void push_front(const Ty& data)
		{
			if (is_null(_list)) {
				_list = new fwd_list_node<Ty>(data);
				_size++;
			}
			else {
				_list = new fwd_list_node<Ty>(data, _list);
				_size++;
			}
		}

		/// <summary>
		/// Constructs an element in the front of the list.
		/// This operation has O(1) complexity.
		/// </summary>
		/// <typeparam name="...Args">a list of type parameters.</typeparam>
		/// <param name="...args">a list of arguments to be forwarded
		/// to the underlying type constructor.</param>
		template <typename... Args>
		constexpr void emplace_front(Args&&... args)
		{
			if (is_null(_list)) {
				_list = new fwd_list_node<Ty>(std::forward<Args>(args)...);
				_size++;
			}
			else {
				_list = new fwd_list_node<Ty>(std::forward<Args>(args)..., _list);
				_size++;
			}
		}

		/// <summary>
		/// Adds an element to the end of the list.
		/// </summary>
		/// <param name="data">data to be added to the list node.</param>
		constexpr void push_back(const Ty& data)
		{
			if (is_null(_list)) push_front(data);
			else {
				auto iter = _list;
				for (; !is_null(iter->_next); iter = iter->_next);
				iter->_next = new fwd_list_node<Ty>(data);
			}
		}

		/// <summary>
		/// Constructs an element at the end of the list.
		/// </summary>
		/// <typeparam name="...Args">a list of type parameters.</typeparam>
		/// <param name="...args">a list of parameters to be forwarded
		/// to the underlying type constructor.</param>
		template <typename... Args>
		constexpr void emplace_back(Args&&... args)
		{
			if (is_null(_list)) emplace_front(std::forward<Args>(args)...);
			else {
				auto iter = _list;
				for (; !is_null(iter->_next); iter = iter->_next);
				iter->_next = new fwd_list_node<Ty>(std::forward<Args>(args)...);
				_size++;
			}
		}

		/// <summary>
		/// Returns the iterator pointing at the start of
		/// the list.
		/// </summary>
		/// <returns>iterator pointing at the start of the list.</returns>
		constexpr iterator begin() noexcept { return iterator(_list); }
		constexpr const_iterator begin() const noexcept { return iterator(_list); }

		/// <summary>
		/// Returns the iterator pointing to an element past the
		/// end of the list, which is always nullptr.
		/// </summary>
		/// <returns>iterator pointing to an element past the end
		/// of the list, always nullptr.</returns>
		constexpr iterator end() noexcept { return iterator(nullptr); }
		constexpr const_iterator end() const noexcept { return iterator(nullptr); }

		/// <summary>
		/// Returns the element at the start of the list.
		/// </summary>
		/// <returns>a reference containing the first element of the list.</returns>
		constexpr reference front() { return _list->_data; }
		constexpr const_reference front() const { return _list->_data; }

		/// <summary>
		/// Returns the last element of the list.
		/// </summary>
		/// <returns>a reference containing the last element of the list.</returns>
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

	private:
		constexpr void _list_destroy_clear()
		{
			if (is_null(_list)) return;
			auto iter = _list;
			while (!is_null(iter)) {
				auto tmp = iter;
				iter = iter->_next;
				delete tmp;
			}
			_list = nullptr;
			_size = 0;
		}

        friend class forward_list_iterator<fwd_list_node<Ty> >;
		using _list_type = fwd_list_node<Ty>*;
		_list_type _list;
		std::size_t _size;
	};
}

#endif

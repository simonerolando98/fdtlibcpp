#ifndef FDT_SEQUENTIAL_LINKED_LIST_H
#define FDT_SEQUENTIAL_LINKED_LIST_H

#include <cstddef>
#include <memory>
#include <utility>
#include <algorithm>
#include <fdt/utility.h>
#include <fdt/iterator.h>

namespace fdt {

    /**
     * @brief Doubly linked list node template implementation.
     * @tparam Tx type of linked list node data payload.
    */
    template <typename Tx>
    struct dl_node {
    public:
        using value_type = Tx;

        constexpr dl_node() : _prev(nullptr), _next(nullptr) {}

        constexpr
            explicit dl_node(const Tx& data, dl_node<Tx>* prev = nullptr, dl_node<Tx>* next = nullptr)
            : _data(data), _prev(prev), _next(next) {}

        template <typename... Args>
        explicit constexpr
            dl_node(Args&&... args, dl_node<Tx>* prev = nullptr, dl_node<Tx>* next = nullptr)
            : _data(std::forward<Args>(args)...), _prev(prev), _next(next) {}

        Tx _data;
        dl_node<Tx>* _prev;
        dl_node<Tx>* _next;
    };

    /**
     * @brief Template doubly linked list container.
     * @tparam Ty list data payload type.
    */
    template <typename Ty, typename Allocator = std::allocator<dl_node<Ty> > >
    class linked_list {
    public:        
        using value_type = Ty;
        using size_type = std::size_t;
        using reference = Ty&;
        using const_reference = const Ty&;
        using pointer = Ty*;
        using const_pointer = const Ty*;
        using iterator = list_iterator<dl_node<Ty> >;
        using const_iterator = const list_iterator<dl_node<Ty> >;
        using allocator_type = Allocator;

        /**
         * @brief Default constructor. Constructs an empty list.
        */
        constexpr linked_list() : _list_start(nullptr), _size(0) {}

        /**
         * @brief Copies another list object.
         * @param other another linked list object.
        */
        constexpr linked_list(const linked_list& other)
            : _list_start(nullptr),
            _size(0)
        {
            for (auto& x : other) push_back(x);
        }

        /**
         * @brief Moves a list into this object instance.
         * @param other another list instance, provided as rvalue reference.
         * It could be a just-constructed anonymous list.
        */
        constexpr linked_list(linked_list&& other) noexcept
            : _list_start(std::move(other._list_start)),
            _size(std::move(other._size)) {}

        /**
         * @brief Copies another list using operator =.
         * @param other another list object instance.
         * @return this list instance.
        */
        constexpr linked_list& operator=(const linked_list& other)
        {
            linked_list copy(other);
            copy.swap(*this);
            return *this;
        }

        /**
         * @brief Moves a list object instance into this instance.
         * @param other another list instance, provided as rvalue reference.
         * It could represent an anonymous just-constructed list or another
         * type of rvalue reference.
         * @return this list instance.
        */
        constexpr linked_list& operator=(linked_list&& other) noexcept
        {
            linked_list copy(std::move(other));
            copy.swap(*this);
            return *this;
        }

        ~linked_list() { _list_destroy_clear(); }

    	
        /**
         * @brief Returns the status of the list.
         * @return true if empty, false otherwise.
        */
        [[nodiscard]]
        constexpr bool empty() const noexcept
        { return _size == 0 && is_null(_list_start); }

        /**
         * @brief Returns the size of the list.
         * @return linked_list::size_type list size.
        */
        constexpr size_type size() const noexcept { return _size; }

        /**
         * @brief Clears the list deleting every element and freeing memory.
        */
        constexpr void clear() { _list_destroy_clear(); }

        /**
         * @brief Adds an element to the front of the list, copying its data.
         * @param data data payload to copy inside the new list node.
        */
        constexpr void push_front(const Ty& data)
        {
            if (is_null(_list_start)) {
                _list_start = allocator_traits::allocate(_alloc, 1);
                allocator_traits::construct(_alloc, _list_start, data);
                _size++;
            }
            else {
                _list_start->_prev = allocator_traits::allocate(_alloc, 1);
                allocator_traits::construct(_alloc, _list_start->_prev, data, nullptr, _list_start);
                _list_start = _list_start->_prev;
                _size++;
            }
        }

        /**
         * @brief Adds an element to the front of the list, constructing it
         * in place.
         * @tparam Args rvalue reference to an argument list. 
         * @param args constructor arguments.
        */
        template <typename... Args>
        constexpr reference emplace_front(Args&&... args)
        {
            if (is_null(_list_start)) {
                _list_start = allocator_traits::allocate(_alloc, 1);
                allocator_traits::construct(_alloc, _list_start, std::forward<Args>(args)...);
                _size++;
                return _list_start->_data;
            }
            else {
                _list_start->_prev = allocator_traits::allocate(_alloc, 1);
                allocator_traits::construct(_alloc, _list_start->_prev, std::forward<Args>(args)..., nullptr, _list_start);
                _list_start = _list_start->_prev;
                _size++;
                return _list_start->_prev->_data;
            }
        }

        /**
         * @brief Adds an element to the end of the list, copying its data.
         * @param data data payload to copy inside the node.
        */
        constexpr void push_back(const Ty& data)
        {
            if (is_null(_list_start)) return push_front(data);

            auto list = _list_start;
            for (; !is_null(list->_next); list = list->_next);
            list->_next = allocator_traits::allocate(_alloc, 1);
            allocator_traits::construct(_alloc, list->_next, data, list, nullptr);
        }

        /**
         * @brief Adds an element to the end of the list, constructing it
         * in place.
         * @tparam Args rvalue reference to an argument list. 
         * @param args constructor arguments.
        */
        template <typename... Args>
        constexpr void emplace_back(Args&&... args)
        {
            if (is_null(_list_start))
                return emplace_front(std::forward<Args>(args)...);

            auto list = _list_start;
            for (; !is_null(list->_next); list = list->_next);
            list->_next = allocator_traits::allocate(_alloc, 1);
            allocator_traits::construct(_alloc, list->_next, std::forward<Args>(args)..., list, nullptr);
        }

        /**
         * @brief Removes the first element of the list, freeing its memory.
        */
        constexpr void pop_front()
        {
            if (is_null(_list_start)) return;

            auto del = _list_start;
            _list_start = _list_start->_next;
            _list_start->_prev = nullptr;
            allocator_traits::deallocate(_alloc, del, 1);
            --_size;
        }

        /**
         * @brief Removes the last element of the list, freeing its memory.
        */
        constexpr void pop_back()
        {
            auto list = _list_start;
            for (; !is_null(list->_next); list = list->_next);
            auto del = list;
            list = list->_prev;
            list->_next = nullptr;
            allocator_traits::deallocate(_alloc, del, 1);
            --_size;
        }

    	constexpr iterator erase(const_iterator pos)
        {
            return iterator(nullptr);
        }

    	constexpr iterator erase(const_iterator first, const_iterator last)
        {
            return iterator(nullptr);
        }

        /**
         * @brief Random access iterator encapsulating the start point of
         * the list.
         * @return linked_list::rand_iterator<Ty> encapsulating list start point.
        */
        constexpr iterator begin() noexcept { return iterator(_list_start); }

    	constexpr const_iterator begin() const noexcept { return iterator(_list_start); }

        /**
         * @brief Random access iterator encapsulating list end point, which
         * is always nullptr.
         * @return nullptr_t.
        */
        constexpr iterator end() noexcept { return iterator(nullptr); }

    	constexpr iterator end() const noexcept { return iterator(nullptr); }

        /**
         * @brief Returns the first element of the list.
         * @return linked_list::reference to the first element of the list.
        */
        constexpr reference front() { return _list_start->_data; }

    	constexpr const_reference  front() const noexcept { return _list_start->_data; }

        /**
         * @brief Returns the last element of the list.
         * @return linked_list::reference to the last element of the list.
        */
        constexpr reference back()
        {
            auto list = _list_start;
            for (; !is_null(list->_next); list = list->_next);
            return list->_data;
        }

        constexpr const_reference back() const
        {
            auto list = _list_start;
            for (; !is_null(list->_next); list = list->_next);
            return list->_data;
        }

        constexpr void swap(linked_list& other) noexcept
        {
            std::swap(other._list_start, _list_start);
            std::swap(other._size, _size);
            std::swap(other._alloc, _alloc);
        }

    private:
        constexpr void _list_destroy_clear()
        {
            if (is_null(_list_start)) return;

			dl_node<Ty>* curr = _list_start;
			dl_node<Ty>* next = nullptr;

			while (!is_null(curr)) {
				next = curr->_next;
				allocator_traits::deallocate(_alloc, curr, 1);
				curr = next;
			}

			_list_start = nullptr;
        }

        using _list_type = dl_node<Ty>*;
        allocator_type _alloc;
        _list_type _list_start;
        std::size_t _size;
        using allocator_traits = std::allocator_traits<Allocator>;
    };
}

#endif

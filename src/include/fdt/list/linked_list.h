#ifndef FDT_LIST_LINKED_LIST_H
#define FDT_LIST_LINKED_LIST_H

#include <cstddef>
#include <memory>
#include <utility>
#include <algorithm>
#include "fdt/utility.h"
#include "fdt/iterator.h"

namespace fdt {

    /**
     * @brief Template doubly linked list container.
     * @tparam Ty list data payload type.
    */
    template <class Ty>
    class linked_list {
    public:
        /**
         * @brief Doubly linked list node template implementation.
         * @tparam Tx type of linked list node data payload.
        */
        template <class Tx = Ty>
        class Node {
        public:
            using value_type = Tx;
            
            constexpr Node() : _prev(nullptr), _next(nullptr) {}
            
            constexpr
            explicit Node(const Tx& data, Node<Tx>* prev = nullptr, Node<Tx>* next = nullptr)
                : _data(data), _prev(prev), _next(next) {}
            
            template <typename... Args>
            explicit constexpr
                Node(Args&&... args, Node<Ty>* prev = nullptr, Node<Tx>* next = nullptr)
                : _data(std::forward<Args>(args)...), _prev(prev), _next(next) {}
        private:
            friend class linked_list<Tx>;
            friend class list_iterator<Node<Tx> >;
            
            Tx _data;
            Node<Tx>* _prev;
            Node<Tx>* _next;
        };
        
        using value_type = Ty;
        using size_type = std::size_t;
        using reference = Ty&;
        using const_reference = const Ty&;
        using pointer = Ty*;
        using const_pointer = const Ty*;
        using iterator = list_iterator<Node<Ty> >;
        using const_iterator = const list_iterator<Node<Ty> >;

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
            _list_start = nullptr;
            _size = 0;
            for (auto& x : other) push_back(x);
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
            if (this == &other)
                return *this;
        	
            _list_start = std::move(other._list_start);
            _size = std::move(other._size);
            return *this;
        }

        ~linked_list() { _list_destroy_clear(); }

    	
        /**
         * @brief Returns the status of the list.
         * @return true if empty, false otherwise.
        */
        [[nodiscard]]
        constexpr bool empty() const
        { return _size == 0 && is_null(_list_start); }

        /**
         * @brief Returns the size of the list.
         * @return linked_list::size_type list size.
        */
        [[nodiscard]]
        constexpr size_type size() const { return _size; }

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
                _list_start = new Node<Ty>(data);
                _size++;
            }
            else {
                _list_start->_prev = new Node<Ty>(data, nullptr, _list_start);
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
        constexpr void emplace_front(Args&&... args)
        {
            if (is_null(_list_start)) {
                _list_start = new Node<Ty>(std::forward<Args>(args)...);
                _size++;
            }
            else {
                _list_start->_prev = new Node<Ty>(std::forward<Args>(args)...,
                    nullptr, _list_start);
                _list_start = _list_start->_prev;
                _size++;
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
            list->_next = new Node<Ty>(data, list, nullptr);
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
            list->_next = new Node<Ty>(std::forward<Args>(args)...,
                    list, nullptr);
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
            delete del;
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
            delete del;
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
        [[nodiscard]]
    	constexpr const_iterator begin() const noexcept { return iterator(_list_start); }

        /**
         * @brief Random access iterator encapsulating list end point, which
         * is always nullptr.
         * @return nullptr_t.
        */
        constexpr iterator end() noexcept { return iterator(nullptr); }
    	[[nodiscard]]
    	constexpr iterator end() const noexcept { return iterator(nullptr); }

        /**
         * @brief Returns the first element of the list.
         * @return linked_list::reference to the first element of the list.
        */
        constexpr reference front() { return _list_start->_data; }
    	[[nodiscard]]
    	constexpr const_reference  front() const { return _list_start->_data; }

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
    	[[nodiscard]]
        constexpr const_reference back() const
        {
            auto list = _list_start;
            for (; !is_null(list->_next); list = list->_next);
            return list->_data;
        }

    private:
        constexpr void _list_destroy_clear()
        {
            if (is_null(_list_start)) return;

            auto list = _list_start;
            while (!is_null(list->_next)) {
                auto del = list;
                list = list->_next;
                delete del;
            }
            _list_start = nullptr;
            _size = 0;
        }

        using _list_type = Node<Ty>*;
        _list_type _list_start;
        std::size_t _size;
    };
}

#endif

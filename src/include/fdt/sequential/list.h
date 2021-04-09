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
     * @tparam T type of linked list node data payload.
    */
    template <typename T>
    struct dl_node {
    public:
        using value_type = T;

        constexpr dl_node() : _prev(nullptr), _next(nullptr) {}

        constexpr
            explicit dl_node(const T& data, dl_node<T>* prev = nullptr, dl_node<T>* next = nullptr)
            : _data(data), _prev(prev), _next(next) {}

        template <typename... Args>
        explicit constexpr
            dl_node(Args&&... args, dl_node<T>* prev = nullptr, dl_node<T>* next = nullptr)
            : _data(std::forward<Args>(args)...), _prev(prev), _next(next) {}

        T _data;
        dl_node<T>* _prev;
        dl_node<T>* _next;
    };

    /**
     * @brief Template doubly linked list container.
     * @tparam T list data payload type.
    */
    template <typename T, typename Allocator = std::allocator<dl_node<T>>>
    class list {
    public:        
        using value_type = T;
        using size_type = std::size_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = list_iterator<dl_node<T> >;
        using const_iterator = const list_iterator<dl_node<T> >;
        using allocator_type = Allocator;

        /**
         * @brief Default constructor. Constructs an empty list.
        */
        constexpr list() : list_start_(nullptr), size_(0) {}

        constexpr explicit list(const Allocator& alloc)
        : list_start_(nullptr), size_(0), alloc_(alloc) {}

        constexpr list(size_t count, const T& value, const Allocator& alloc = Allocator())
        : list_start_(nullptr), size_(0), alloc_(alloc)
        {
            for (size_t i = 0; i < count; ++i) emplace_front(value);
        }

        constexpr explicit list(size_t count)
        : list_start_(nullptr), size_(0)
        {
            for (size_t i = 0; i < count; ++i) emplace_front(T());
        }

        constexpr explicit list(size_t count, const Allocator& alloc = Allocator())
        : list_start_(nullptr), size_(0), alloc_(alloc)
        {
            for (size_t i = 0; i < count; ++i) emplace_front(T());
        }

        template <typename InputIt>
        constexpr list(InputIt first, InputIt last, const Allocator& alloc = Allocator())
        : list_start_(nullptr), size_(0), alloc_(alloc)
        {
            for (; first != last; ++first) emplace_back(*first);
        }

        /**
         * @brief Copies another list object.
         * @param other another linked list object.
        */
        constexpr list(const list& other)
        : list_start_(nullptr), size_(0)
        {
            for (auto& x : other) push_back(x);
        }

        /**
         * @brief Moves a list into this object instance.
         * @param other another list instance, provided as rvalue reference.
         * It could be a just-constructed anonymous list.
        */
        constexpr list(list&& other) noexcept
        : list_start_(std::move(other.list_start_)),
          size_(std::move(other.size_)) {}

        /**
         * @brief Copies another list using operator =.
         * @param other another list object instance.
         * @return this list instance.
        */
        constexpr list& operator=(const list& other)
        {
            list copy(other);
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
        constexpr list& operator=(list&& other) noexcept
        {
            list copy(std::move(other));
            copy.swap(*this);
            return *this;
        }

        ~list() { _list_destroy_clear(); }

    	
        /**
         * @brief Returns the status of the list.
         * @return true if empty, false otherwise.
        */
        [[nodiscard]]
        constexpr bool empty() const noexcept
        { return size_ == 0 && is_null(list_start_); }

        /**
         * @brief Returns the size of the list.
         * @return list::size_type list size.
        */
        constexpr size_type size() const noexcept { return size_; }

        /**
         * @brief Clears the list deleting every element and freeing memory.
        */
        constexpr void clear() { _list_destroy_clear(); }

        /**
         * @brief Adds an element to the front of the list, copying its data.
         * @param data data payload to copy inside the new list node.
        */
        constexpr void push_front(const T& data)
        {
            if (is_null(list_start_)) {
                list_start_ = allocator_traits::allocate(alloc_, 1);
                allocator_traits::construct(alloc_, list_start_, data);
                size_++;
            }
            else {
                list_start_->_prev = allocator_traits::allocate(alloc_, 1);
                allocator_traits::construct(alloc_, list_start_->_prev, data, nullptr, list_start_);
                list_start_ = list_start_->_prev;
                size_++;
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
            if (is_null(list_start_)) {
                list_start_ = allocator_traits::allocate(alloc_, 1);
                allocator_traits::construct(alloc_, list_start_, std::forward<Args>(args)...);
                size_++;
                return list_start_->_data;
            }
            else {
                list_start_->_prev = allocator_traits::allocate(alloc_, 1);
                allocator_traits::construct(alloc_, list_start_->_prev, std::forward<Args>(args)..., nullptr, list_start_);
                list_start_ = list_start_->_prev;
                size_++;
                return list_start_->_prev->_data;
            }
        }

        /**
         * @brief Adds an element to the end of the list, copying its data.
         * @param data data payload to copy inside the node.
        */
        constexpr void push_back(const T& data)
        {
            if (is_null(list_start_)) return push_front(data);

            auto list = list_start_;
            for (; !is_null(list->_next); list = list->_next);
            list->_next = allocator_traits::allocate(alloc_, 1);
            allocator_traits::construct(alloc_, list->_next, data, list, nullptr);
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
            if (is_null(list_start_))
                return emplace_front(std::forward<Args>(args)...);

            auto list = list_start_;
            for (; !is_null(list->_next); list = list->_next);
            list->_next = allocator_traits::allocate(alloc_, 1);
            allocator_traits::construct(alloc_, list->_next, std::forward<Args>(args)..., list, nullptr);
        }

        /**
         * @brief Removes the first element of the list, freeing its memory.
        */
        constexpr void pop_front()
        {
            if (is_null(list_start_)) return;

            auto del = list_start_;
            list_start_ = list_start_->_next;
            list_start_->_prev = nullptr;
            allocator_traits::deallocate(alloc_, del, 1);
            --size_;
        }

        /**
         * @brief Removes the last element of the list, freeing its memory.
        */
        constexpr void pop_back()
        {
            auto list = list_start_;
            for (; !is_null(list->_next); list = list->_next);
            auto del = list;
            list = list->_prev;
            list->_next = nullptr;
            allocator_traits::deallocate(alloc_, del, 1);
            --size_;
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
         * @return list::rand_iterator<T> encapsulating list start point.
        */
        constexpr iterator begin() noexcept { return iterator(list_start_); }

    	constexpr const_iterator begin() const noexcept { return iterator(list_start_); }

        /**
         * @brief Random access iterator encapsulating list end point, which
         * is always nullptr.
         * @return nullptr_t.
        */
        constexpr iterator end() noexcept { return iterator(nullptr); }

    	constexpr iterator end() const noexcept { return iterator(nullptr); }

        /**
         * @brief Returns the first element of the list.
         * @return list::reference to the first element of the list.
        */
        constexpr reference front() { return list_start_->_data; }

    	constexpr const_reference  front() const noexcept { return list_start_->_data; }

        /**
         * @brief Returns the last element of the list.
         * @return list::reference to the last element of the list.
        */
        constexpr reference back()
        {
            auto list = list_start_;
            for (; !is_null(list->_next); list = list->_next);
            return list->_data;
        }

        constexpr const_reference back() const
        {
            auto list = list_start_;
            for (; !is_null(list->_next); list = list->_next);
            return list->_data;
        }

        constexpr void swap(list& other) noexcept
        {
            std::swap(other.list_start_, list_start_);
            std::swap(other.size_, size_);
            std::swap(other.alloc_, alloc_);
        }

    private:
        constexpr void _list_destroy_clear()
        {
            if (is_null(list_start_)) return;

			dl_node<T>* curr = list_start_;
			dl_node<T>* next = nullptr;

			while (!is_null(curr)) {
				next = curr->_next;
				allocator_traits::deallocate(alloc_, curr, 1);
				curr = next;
			}

            list_start_ = nullptr;
        }

        using list_type = dl_node<T>*;
        allocator_type alloc_;
        list_type list_start_;
        std::size_t size_;
        using allocator_traits = std::allocator_traits<Allocator>;
    };
}

#endif

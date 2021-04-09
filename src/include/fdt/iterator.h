#ifndef FDTLIBCPP_ITERATOR_H
#define FDTLIBCPP_ITERATOR_H

namespace fdt {

    template <typename T>
    class random_access_iterator {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using difference_type = std::ptrdiff_t;

        constexpr random_access_iterator()
            : ptr_(nullptr) {}

        constexpr explicit random_access_iterator(T* ptr_val)
            : ptr_(ptr_val) {}

        constexpr explicit random_access_iterator(std::nullptr_t)
            : ptr_(nullptr) {}

        constexpr random_access_iterator(const random_access_iterator& other)
            : ptr_(other.ptr_) {}

        constexpr random_access_iterator(random_access_iterator&& other)
        noexcept : ptr_(other.ptr_) {}

        constexpr void operator++()
        {
            ++ptr_;
        }

        constexpr void operator++(int)
        {
            ptr_++;
        }

        constexpr void operator--()
        {
            --ptr_;
        }

        constexpr void operator--(int)
        {
            ptr_--;
        }

        constexpr bool operator==(const random_access_iterator& other) const
        {
            return ptr_ == other.ptr_;
        }

        constexpr bool operator!=(const random_access_iterator& other) const
        {
            return !(*this == other);
        }

        constexpr bool operator<(const random_access_iterator& other) const
        {
            return (ptr_ - other.ptr_) < 0;
        }

        constexpr bool operator>(const random_access_iterator& other) const
        {
            return !(*this < other);
        }

        constexpr bool operator<=(const random_access_iterator& other) const
        {
            return (ptr_ - other._ptr) <= 0;
        }

        constexpr bool operator>=(const random_access_iterator& other) const
        {
            return !(*this <= other);
        }

        constexpr reference operator*() noexcept
        {
            return *ptr_;
        }

        constexpr const_reference operator*() const noexcept
        {
            return *ptr_;
        }

        constexpr random_access_iterator operator+(size_t p)
        {
            return random_access_iterator(ptr_ + p);
        }

        constexpr random_access_iterator operator+(int p)
        {
            return random_access_iterator(ptr_ + p);
        }

        constexpr random_access_iterator operator-(size_t p)
        {
            return random_access_iterator(ptr_ - p);
        }

        constexpr random_access_iterator operator-(int p)
        {
            return random_access_iterator(ptr_ - p);
        }

        constexpr explicit operator pointer() const { return ptr_; }

        constexpr bool operator==(std::nullptr_t) const
        {
            return ptr_ == nullptr;
        }

    private:
        pointer ptr_;
    };

    template <typename Node>
    class forward_list_iterator {
    public:
        using value_type = typename Node::value_type;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using difference_type = std::ptrdiff_t;

        constexpr forward_list_iterator()
            : node_(nullptr) {}

        constexpr explicit forward_list_iterator(Node* node)
            : node_(node) {}

        constexpr explicit forward_list_iterator(const Node* node)
            : node_(const_cast<Node*>(node)) {}

        constexpr explicit forward_list_iterator(std::nullptr_t) : node_(nullptr) {}

        constexpr forward_list_iterator(const forward_list_iterator& other) : node_(other.node_) {}

        constexpr forward_list_iterator(forward_list_iterator&& other)  noexcept : node_(other.node_) {}

        constexpr forward_list_iterator& operator=(const forward_list_iterator& other)
        {
            if (this == &other) return *this;

            forward_list_iterator copy(other);
            copy.swap(*this);
            return *this;
        }

        constexpr forward_list_iterator& operator=(forward_list_iterator&& other)
 noexcept         {
            if (this == &other) return *this;

            forward_list_iterator copy(std::move(other));
            copy.swap(*this);
            return *this;
        }

        constexpr void operator++()
        {
            node_ = node_->next_;
        }

        constexpr void operator++(int)
        {
            node_ = node_->next_;
        }

        forward_list_iterator operator+(size_t p)
        {
            auto iter = *this;

            for (size_t i = 0; i < p; ++i) {
                if (iter.node_) ++iter;
                else break;
            }

            return iter;
        }

        forward_list_iterator operator+(int p)
        {
            auto iter = *this;

            for (int i = 0; i < p; ++i) {
                if (iter.node_) ++iter;
                else break;
            }

            return iter;
        }

        constexpr bool operator==(const forward_list_iterator& other) const
        {
            return node_ == other.node_;
        }

        constexpr bool operator!=(const forward_list_iterator& other) const
        {
            return node_ != other.node_;
        }

        constexpr const typename Node::value_type& operator*() const
        {
            return node_->data_;
        }

        constexpr typename Node::value_type& operator*()
        {
            return node_->data_;
        }

        constexpr bool operator==(std::nullptr_t) const
        {
            return node_ == nullptr;
        }

        constexpr bool operator!=(std::nullptr_t) const
        {
            return node_ == nullptr;
        }

        constexpr void swap(forward_list_iterator& other)
        {
            Node* tmp = other.node_;
            other.node_ = node_;
            node_ = other.node_;
        }
    private:
        Node* node_;
        template <typename T, typename Allocator>
        friend class forward_list;
    };

    template <typename Node>
    class list_iterator {
    public:
        using value_type = typename Node::value_type;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using difference_type = std::ptrdiff_t;

        constexpr list_iterator() : node_(nullptr) {}

        constexpr explicit list_iterator(Node* node) : node_(node) {}

        constexpr explicit list_iterator(const Node* node) : node_(const_cast<Node*>(node)) {}

        constexpr explicit list_iterator(std::nullptr_t) : node_(nullptr) {}

        constexpr list_iterator(const list_iterator& other) : node_(other.node_) {}

        constexpr list_iterator(list_iterator&& other)  noexcept : node_(other.node_) {}

        constexpr list_iterator& operator=(const list_iterator& iter)
        {
            if (this == &iter) return *this;

            list_iterator copy(iter);
            copy.swap(*this);
            return *this;
        }

        constexpr list_iterator& operator=(list_iterator&& other) noexcept
        {
            if (this == &other) return *this;

            list_iterator copy(std::move(other));
            copy.swap(*this);
            return *this;
        }

        list_iterator operator+(size_t p)
        {
            auto iter = *this;

            for (size_t i = 0; i < p; ++i) {
                if (iter.node_) ++iter;
                else break;
            }

            return iter;
        }

        list_iterator operator-(size_t p)
        {
            auto iter = *this;

            for (size_t i = 0; i < p; ++i) {
                if (iter.node_) --iter;
                else break;
            }

            return iter;
        }

        constexpr bool operator==(const list_iterator& other) const
        {
            return node_ == other.node_;
        }

        constexpr bool operator!=(const list_iterator& other) const
        {
            return !(*this == other);
        }

        constexpr reference operator*()
        {
            return node_->_data;
        }

        constexpr const_reference operator*() const
        {
            return node_->data_;
        }

        constexpr explicit operator Node*() const { return node_; }

        constexpr bool operator==(std::nullptr_t) const { return node_ == nullptr; }

        constexpr bool operator!=(std::nullptr_t) const { return !(*this == nullptr); }

        constexpr void swap(list_iterator& other)
        {
            Node* tmp = other.node_;
            other.node_ = node_;
            node_ = tmp;
        }

    private:
        Node* node_;
    };

    template <class Iterator>
    class reverse_iterator {
    public:
        using value_type = typename Iterator::value_type;
        using reference = typename Iterator::reference;
        using const_reference = typename Iterator::const_reference;
        using pointer = typename Iterator::pointer;
        using const_pointer = typename Iterator::const_pointer;
        using difference_type = typename Iterator::difference_type;

        constexpr reverse_iterator() : iter_(nullptr) {}

        constexpr explicit reverse_iterator(pointer ptr) : iter_(ptr) {}

        constexpr explicit reverse_iterator(const_pointer ptr) : iter_(const_cast<pointer>(ptr)) {}

        constexpr explicit reverse_iterator(std::nullptr_t) : iter_(nullptr) {}

        constexpr void operator++()
        {
            --iter_;
        }

        constexpr void operator++(int)
        {
            iter_--;
        }

        constexpr void operator--()
        {
            ++iter_;
        }

        constexpr void operator--(int)
        {
            iter_++;
        }

        constexpr bool operator==(const reverse_iterator& other)
        {
            return iter_ == other.iter_;
        }

        constexpr bool operator!=(const reverse_iterator& other)
        {
            return iter_ != other.iter_;
        }

        constexpr reference operator*()
        {
            return *iter_;
        }

        constexpr const_reference operator*() const
        {
            return *iter_;
        }

        reverse_iterator operator+(size_t p)
        {
            auto iter = *this;

            for (size_t i = 0; i < p; ++i) {
                if (iter.iter_) ++iter;
                else break;
            }

            return iter;
        }

        reverse_iterator operator-(size_t p)
        {
            auto iter = *this;

            for (size_t i = 0; i < p; ++i) {
                if (iter.iter_) --iter;
                else break;
            }

            return iter;
        }

        constexpr explicit operator pointer() const
        {
            return iter_;
        }

        constexpr bool operator==(std::nullptr_t) const
        {
            return iter_ == nullptr;
        }

        constexpr bool operator!=(std::nullptr_t) const
        {
            return iter_ != nullptr;
        }
    private:
        Iterator iter_;
    };

    template <typename Node>
    constexpr forward_list_iterator<Node>
    operator+(forward_list_iterator<Node> it, size_t pos)
    {
        for (size_t i = 0; i < pos; ++i) ++it;
        return it;
    }

    template <typename Node>
    constexpr std::ptrdiff_t distance(forward_list_iterator<Node> first,
                                      forward_list_iterator<Node> last)
    {
        ptrdiff_t dist = 0;
        for (auto it = first; it != last; ++it) ++dist;
        return dist;
    }
}

#endif

#ifndef FDTLIBCPP_ITERATOR_H
#define FDTLIBCPP_ITERATOR_H

namespace fdt {
    /**
     * @brief Random access iterator class. Provides access to containers
     * using range-based representation to reduce code clutter and potential
     * user error.
     * @tparam T iterator ptr type. 
    */
    template <typename T>
    class rand_iterator {
    public:
        constexpr rand_iterator() : iter_(nullptr) {}
        constexpr explicit rand_iterator(T* ptr) : iter_(ptr) {}
        constexpr explicit rand_iterator(const T* ptr) : iter_(const_cast<T*>(ptr)) {}
        constexpr explicit rand_iterator(std::nullptr_t) : iter_(nullptr) {}

        constexpr void operator++() { ++iter_; }
        constexpr void operator--() { --iter_; }
        constexpr void operator++(int) { iter_++; }
        constexpr void operator--(int) { iter_--; }


        constexpr bool operator==(const rand_iterator& other) const
        { return iter_ == other.iter_; }

        constexpr bool operator!=(const rand_iterator& other) const
        { return iter_ != other.iter_; }


        constexpr bool operator>(const rand_iterator& other) const
        { return ((iter_ - other.iter_) > 0); }

        constexpr bool operator<(const rand_iterator& other) const
        { return ((iter_ - other.iter_) < 0); }

        constexpr bool operator>=(const rand_iterator& other) const
        { return ((iter_ - other.iter_) >= 0); }

        constexpr bool operator<=(const rand_iterator& other) const
        { return ((iter_ - other.iter_) <= 0); }


        constexpr T& operator*() noexcept { return *iter_; }

        constexpr const T& operator*() const noexcept { return *iter_; }

        constexpr rand_iterator operator+(size_t p)
        {
            return rand_iterator(iter_ + p);
        }

        constexpr rand_iterator operator+(int p)
        {
            return rand_iterator(iter_ + p);
        }

        constexpr explicit operator T*() const { return iter_; }
		constexpr bool operator==(const std::nullptr_t null) const
		{
			return iter_ == null;
		}
    private:
        T* iter_;
    };


    /**
     * @brief Reverse random access iterator class. Provides access to
     * sequential containers in reverse order, and allows the usage of
     * range-based semantics in order to minimize user error and code
     * clutter.
     * @tparam T iterator ptr type.
    */
    template <typename T>
    class reverse_rand_iterator {
    public:
        constexpr reverse_rand_iterator() : iter_(nullptr) {}
        constexpr reverse_rand_iterator(T* ptr) : iter_(ptr) {}
        constexpr reverse_rand_iterator(const T* ptr) : iter_(const_cast<T*>(ptr)) {}
        constexpr reverse_rand_iterator(std::nullptr_t) : iter_(nullptr) {}

        constexpr void operator++() { --iter_; }
        constexpr void operator--() { ++iter_; }
        constexpr void operator++(int) { iter_--; }
        constexpr void operator--(int) { iter_++; }

        constexpr bool operator==(const reverse_rand_iterator& other) const
        {
            return iter_ == other.iter_;
        }

        constexpr bool operator!=(const reverse_rand_iterator& other) const
        {
            return iter_ != other.iter_;
        }


        constexpr bool operator>(const reverse_rand_iterator& other) const
        {
            return ((iter_ - other.iter_) > 0);
        }

        constexpr bool operator<(const reverse_rand_iterator& other) const
        {
            return ((iter_ - other.iter_) < 0);
        }

        constexpr bool operator>=(const reverse_rand_iterator& other) const
        {
            return ((iter_ - other.iter_) >= 0);
        }

        constexpr bool operator<=(const reverse_rand_iterator& other) const
        {
            return ((iter_ - other.iter_) <= 0);
        }


        constexpr auto operator*() { return *iter_; }

        constexpr auto operator*() const { return *iter_; }

        constexpr reverse_rand_iterator operator+(size_t p)
        {
            return rand_iterator(iter_ - p);
        }

        constexpr reverse_rand_iterator operator+(int p)
        {
            return rand_iterator(iter_ - p);
        }

        constexpr explicit operator T* () const { return iter_; }
        
        constexpr bool operator==(std::nullptr_t) { return iter_ == nullptr; }
    private:
        T* iter_;
    };

    template <typename Node>
    class forward_list_iterator {
    public:
        constexpr forward_list_iterator(Node* node) : node(node) {}
        constexpr forward_list_iterator(const Node* node) : node(const_cast<Node*>(node)) {}
        constexpr forward_list_iterator(std::nullptr_t) : node(nullptr) {}

        constexpr void operator++() { node = node->next_; }
        constexpr void operator++(int) { node = node->next_; }

        auto operator+(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter.node) ++iter;
                else break;
            }
            return iter;
        }

        constexpr bool operator!=(const forward_list_iterator& other) const
        {
            return node != other.node;
        }

        constexpr bool operator==(const forward_list_iterator& other) const
        {
            return node == other.node;
        }

        constexpr bool operator>(const forward_list_iterator& other) const
        {
            return (node - other.node) > 0;
        }

        constexpr bool operator<(const forward_list_iterator& other) const
        {
            return (node - other.node) < 0;
        }

        constexpr bool operator>=(const forward_list_iterator& other) const
        {
            return (node - other.node) >= 0;
        }

        constexpr bool operator<=(const forward_list_iterator& other) const
        {
            return (node - other.node) <= 0;
        }

        constexpr typename Node::value_type operator*()
        {
            return node->data_;
        }

        constexpr typename Node::value_type operator*() const
        {
            return node->data_;
        }

        constexpr bool operator==(std::nullptr_t) const { return node == nullptr; }
        constexpr bool operator!=(std::nullptr_t) const { return node != nullptr; }
    private:
        template <typename Ty, typename Allocator>
        friend class forward_list;
        Node* node;
    };

    template <typename TyNode>
    constexpr forward_list_iterator<TyNode>
    operator+(forward_list_iterator<TyNode> it, size_t pos)
    {
        for (size_t i = 0; i < pos; ++i) ++it;
        return it;
    }

    template <typename TyNode>
    constexpr std::ptrdiff_t distance(forward_list_iterator<TyNode> begin,
                                        forward_list_iterator<TyNode> end)
	{
		ptrdiff_t dist = 0;
        for (auto it = begin; it != end; ++it) dist++;
        return dist;
	}

    template <typename Node>
    class list_iterator {
    public:
        constexpr list_iterator(Node* ptr) : node(ptr) {}
        constexpr list_iterator(const Node* ptr) : node(const_cast<Node*>(ptr)) {}
        constexpr list_iterator(std::nullptr_t) : node(nullptr) {}

        constexpr void operator++() { node = node->_next; }
        constexpr void operator--() { node = node->_prev; }
        constexpr void operator++(int) { node = node->_next; }
        constexpr void operator--(int) { node = node->_prev; }

        auto operator+(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter.node) ++iter;
                else break;
            }
            return iter;
        }

        auto operator-(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter.node) --iter;
                else break;
            }
            return iter;
        }

        constexpr bool operator!=(const list_iterator<Node>& r) const
        {
            return node != r.node;
        }

        constexpr bool operator==(const list_iterator<Node>& r) const
        {
            return node == r.node;
        }

        constexpr bool operator>(const list_iterator<Node>& r) const
        {
            return ((node - r.node) > 0);
        }

        constexpr bool operator>=(const list_iterator<Node>& r) const
        {
            return ((node - r.node) >= 0);
        }

        constexpr bool operator<=(const list_iterator<Node>& r) const
        {
            return ((node - r.node) <= 0);
        }

        constexpr typename Node::value_type operator*()
        {
            return node->_data;
        }

        constexpr typename Node::value_type operator*() const
        {
            return node->_data;
        }

        constexpr explicit operator Node*() const { return node; }
        constexpr bool operator==(std::nullptr_t) const { return node == nullptr; }
        constexpr bool operator!=(std::nullptr_t) const { return node != nullptr; }
    private:
        Node* node;
    };

    template <typename Node>
    class reverse_list_iterator {
    public:
        constexpr reverse_list_iterator(Node* ptr) : node(ptr) {}
        constexpr reverse_list_iterator(const Node* ptr) : node(const_cast<Node*>(ptr)) {}
        constexpr reverse_list_iterator(std::nullptr_t) : node(nullptr) {}

        constexpr void operator++() { node = node->_prev; }
        constexpr void operator--() { node = node->_next; }
        constexpr void operator++(int) { node = node->_prev; }
        constexpr void operator--(int) { node = node->_next; }

        constexpr bool operator!=(const reverse_list_iterator<Node>& r) const
        {
            return node != r.node;
        }

        constexpr bool operator==(const reverse_list_iterator<Node>& r) const
        {
            return node == r.node;
        }

        constexpr bool operator>(const reverse_list_iterator<Node>& r) const
        {
            return ((node - r.node) > 0);
        }

        constexpr bool operator>=(const reverse_list_iterator<Node>& r) const
        {
            return ((node - r.node) >= 0);
        }

        constexpr bool operator<=(const reverse_list_iterator<Node>& r) const
        {
            return ((node - r.node) <= 0);
        }

        constexpr typename Node::value_type operator*()
        {
            return node->_data;
        }

        constexpr typename Node::value_type operator*() const
        {
            return node->_data;
        }

        auto operator+(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter.node) ++iter;
                else break;
            }
            return iter;
        }

        auto operator-(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter.node) --iter;
                else break;
            }
            return iter;
        }

        constexpr explicit operator Node* () const { return node; }
        constexpr bool operator==(std::nullptr_t) const { return node == nullptr; }
        constexpr bool operator!=(std::nullptr_t) const { return node != nullptr; }
    private:
        Node* node;
    };
}

#endif

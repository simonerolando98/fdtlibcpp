#ifndef FDTLIBCPP_ITERATOR_H
#define FDTLIBCPP_ITERATOR_H

namespace fdt {
    /**
     * @brief Random access iterator class. Provides access to containers
     * using range-based representation to reduce code clutter and potential
     * user error.
     * @tparam Ty iterator ptr type. 
    */
    template <typename Ty>
    class rand_iterator {
    public:
        constexpr rand_iterator() : _iter(nullptr) {}
        constexpr rand_iterator(Ty* ptr) : _iter(ptr) {}
        constexpr rand_iterator(const Ty* ptr) : _iter(const_cast<Ty*>(ptr)) {}
        constexpr rand_iterator(std::nullptr_t) : _iter(nullptr) {}

        constexpr void operator++() { _iter++; }
        constexpr void operator--() { _iter--; }
        constexpr void operator++(int) { _iter++; }
        constexpr void operator--(int) { _iter--; }

        [[nodiscard]]
        constexpr bool operator==(const rand_iterator& other) const
        { return _iter == other._iter; }
        [[nodiscard]]
        constexpr bool operator!=(const rand_iterator& other) const
        { return _iter != other._iter; }

        [[nodiscard]]
        constexpr bool operator>(const rand_iterator& other) const
        { return ((_iter - other._iter) > 0); }
        [[nodiscard]]
        constexpr bool operator<(const rand_iterator& other) const
        { return ((_iter - other._iter) < 0); }
        [[nodiscard]]
        constexpr bool operator>=(const rand_iterator& other) const
        { return ((_iter - other._iter) >= 0); }
        [[nodiscard]]
        constexpr bool operator<=(const rand_iterator& other) const
        { return ((_iter - other._iter) <= 0); }

        [[nodiscard]]
        constexpr auto operator*() { return *_iter; }
        [[nodiscard]]
        constexpr auto operator*() const { return *_iter; }

        auto operator+(int p)
        {
            auto iter = _iter;
            for (int i = 0; i < p; ++i) {
                if (iter) ++iter;
                else break;
            }
            return iter;
        }

        constexpr explicit operator Ty*() const { return _iter; }
		constexpr bool operator==(const std::nullptr_t null) const
		{
			return _iter == null;
		}
    private:
        Ty* _iter;
    };

    /**
     * @brief Reverse random access iterator class. Provides access to
     * sequential containers in reverse order, and allows the usage of
     * range-based semantics in order to minimize user error and code
     * clutter.
     * @tparam Ty iterator ptr type.
    */
    template <typename Ty>
    class reverse_rand_iterator {
    public:
        constexpr reverse_rand_iterator() : _iter(nullptr) {}
        constexpr reverse_rand_iterator(Ty* ptr) : _iter(ptr) {}
        constexpr reverse_rand_iterator(const Ty* ptr) : _iter(const_cast<Ty*>(ptr)) {}
        constexpr reverse_rand_iterator(std::nullptr_t) : _iter(nullptr) {}

        constexpr void operator++() { _iter--; }
        constexpr void operator--() { _iter++; }
        constexpr void operator++(int) { _iter--; }
        constexpr void operator--(int) { _iter++; }

        constexpr bool operator==(const reverse_rand_iterator& other) const
        {
            return _iter == other._iter;
        }

        constexpr bool operator!=(const reverse_rand_iterator& other) const
        {
            return _iter != other._iter;
        }


        constexpr bool operator>(const reverse_rand_iterator& other) const
        {
            return ((_iter - other._iter) > 0);
        }

        constexpr bool operator<(const reverse_rand_iterator& other) const
        {
            return ((_iter - other._iter) < 0);
        }

        constexpr bool operator>=(const reverse_rand_iterator& other) const
        {
            return ((_iter - other._iter) >= 0);
        }

        constexpr bool operator<=(const reverse_rand_iterator& other) const
        {
            return ((_iter - other._iter) <= 0);
        }


        constexpr auto operator*() { return *_iter; }

        constexpr auto operator*() const { return *_iter; }

        constexpr auto operator+(int p)
        {
            auto iter = *this + p;
            return iter;
        }

        constexpr explicit operator Ty* () const { return _iter; }
        
        constexpr bool operator==(std::nullptr_t) { return _iter == nullptr; }
    private:
        Ty* _iter;
    };

    template <typename TyNode>
    class forward_list_iterator {
    public:
        constexpr forward_list_iterator(TyNode* node) : _node(node) {}
        constexpr forward_list_iterator(const TyNode* node) : _node(const_cast<TyNode*>(node)) {}
        constexpr forward_list_iterator(std::nullptr_t) : _node(nullptr) {}

        constexpr void operator++() { _node = _node->_next; }
        constexpr void operator++(int) { _node = _node->_next; }

        constexpr bool operator!=(const forward_list_iterator& other) const
        {
            return _node != other._node;
        }

        constexpr bool operator==(const forward_list_iterator& other) const
        {
            return _node == other._node;
        }

        constexpr bool operator>(const forward_list_iterator& other) const
        {
            return (_node - other._node) > 0;
        }

        constexpr bool operator<(const forward_list_iterator& other) const
        {
            return (_node - other._node) < 0;
        }

        constexpr bool operator>=(const forward_list_iterator& other) const
        {
            return (_node - other._node) >= 0;
        }

        constexpr bool operator<=(const forward_list_iterator& other) const
        {
            return (_node - other._node) <= 0;
        }

        constexpr typename TyNode::value_type operator*()
        {
            return _node->_data;
        }

        constexpr typename TyNode::value_type operator*() const
        {
            return _node->_data;
        }

        forward_list_iterator operator+(size_t p)
        {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter._node) iter++;
                else break;
            }
            return iter;
        }
        ;
        constexpr bool operator==(std::nullptr_t) const { return _node == nullptr; }
        constexpr bool operator!=(std::nullptr_t) const { return _node != nullptr; }
    private:
        TyNode* _node;
    };

    template <typename TyNode>
    class list_iterator {
    public:
        constexpr list_iterator(TyNode* ptr) : _node(ptr) {}
        constexpr list_iterator(const TyNode* ptr) : _node(const_cast<TyNode*>(ptr)) {}
        constexpr list_iterator(std::nullptr_t) : _node(nullptr) {}

        constexpr void operator++() { _node = _node->_next; }
        constexpr void operator--() { _node = _node->_prev; }
        constexpr void operator++(int) { _node = _node->_next; }
        constexpr void operator--(int) { _node = _node->_prev; }

        constexpr bool operator!=(const list_iterator<TyNode>& r) const
        {
            return _node != r._node;
        }

        constexpr bool operator==(const list_iterator<TyNode>& r) const
        {
            return _node == r._node;
        }

        constexpr bool operator>(const list_iterator<TyNode>& r) const
        {
            return ((_node - r._node) > 0);
        }

        constexpr bool operator>=(const list_iterator<TyNode>& r) const
        {
            return ((_node - r._node) >= 0);
        }

        constexpr bool operator<=(const list_iterator<TyNode>& r) const
        {
            return ((_node - r._node) <= 0);
        }

        constexpr typename TyNode::value_type operator*()
        {
            return _node->_data;
        }

        constexpr typename TyNode::value_type operator*() const
        {
            return _node->_data;
        }

        auto operator+(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter._node) ++iter;
                else break;
            }
            return iter;
        }

        auto operator-(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter._node) --iter;
                else break;
            }
            return iter;
        }

        constexpr explicit operator TyNode*() const { return _node; }
        constexpr bool operator==(std::nullptr_t) const { return _node == nullptr; }
        constexpr bool operator!=(std::nullptr_t) const { return _node != nullptr; }
    private:
        TyNode* _node;
    };

    template <typename TyNode>
    class reverse_list_iterator {
    public:
        constexpr reverse_list_iterator(TyNode* ptr) : _node(ptr) {}
        constexpr reverse_list_iterator(const TyNode* ptr) : _node(const_cast<TyNode*>(ptr)) {}
        constexpr reverse_list_iterator(std::nullptr_t) : _node(nullptr) {}

        constexpr void operator++() { _node = _node->_prev; }
        constexpr void operator--() { _node = _node->_next; }
        constexpr void operator++(int) { _node = _node->_prev; }
        constexpr void operator--(int) { _node = _node->_next; }

        constexpr bool operator!=(const reverse_list_iterator<TyNode>& r) const
        {
            return _node != r._node;
        }

        constexpr bool operator==(const reverse_list_iterator<TyNode>& r) const
        {
            return _node == r._node;
        }

        constexpr bool operator>(const reverse_list_iterator<TyNode>& r) const
        {
            return ((_node - r._node) > 0);
        }

        constexpr bool operator>=(const reverse_list_iterator<TyNode>& r) const
        {
            return ((_node - r._node) >= 0);
        }

        constexpr bool operator<=(const reverse_list_iterator<TyNode>& r) const
        {
            return ((_node - r._node) <= 0);
        }

        constexpr typename TyNode::value_type operator*()
        {
            return _node->_data;
        }

        constexpr typename TyNode::value_type operator*() const
        {
            return _node->_data;
        }

        auto operator+(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter._node) ++iter;
                else break;
            }
            return iter;
        }

        auto operator-(size_t p) {
            auto iter = *this;
            for (size_t i = 0; i < p; ++i) {
                if (iter._node) --iter;
                else break;
            }
            return iter;
        }

        constexpr explicit operator TyNode* () const { return _node; }
        constexpr bool operator==(std::nullptr_t) const { return _node == nullptr; }
        constexpr bool operator!=(std::nullptr_t) const { return _node != nullptr; }
    private:
        TyNode* _node;
    };
}

#endif

//
// Created by Simone Rolando on 19/03/21.
//

#ifndef FDTLIBCPP_ITERATOR_H
#define FDTLIBCPP_ITERATOR_H

namespace fdt {
    template <typename Ty>
    class rand_iterator {
    public:
        constexpr rand_iterator() : _iter(nullptr) {}
        constexpr explicit rand_iterator(Ty* ptr) : _iter(ptr) {}

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

    template <typename TyNode>
    class forward_list_iterator {
    public:
        constexpr explicit forward_list_iterator(TyNode* node) : _node(node) {}

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

        constexpr bool operator==(const std::nullptr_t null_val) const
        {
            return _node == null_val;
        }
    private:
        TyNode* _node;
    };

    template <typename Ty>
    class reverse_rand_iterator {
    public:
        constexpr reverse_rand_iterator() : _iter(nullptr) {}
        constexpr explicit reverse_rand_iterator(Ty* ptr) : _iter(ptr) {}

        constexpr void operator++() { _iter--; }
        constexpr void operator--() { _iter++; }
        constexpr void operator++(int) { _iter--; }
        constexpr void operator--(int) { _iter++; }

        [[nodiscard]]
        constexpr bool operator==(const reverse_rand_iterator& other) const
        { return _iter == other._iter; }
        [[nodiscard]]
        constexpr bool operator!=(const reverse_rand_iterator& other) const
        { return _iter != other._iter; }

        [[nodiscard]]
        constexpr bool operator>(const reverse_rand_iterator& other) const
        { return ((_iter - other._iter) > 0); }
        [[nodiscard]]
        constexpr bool operator<(const reverse_rand_iterator& other) const
        { return ((_iter - other._iter) < 0); }
        [[nodiscard]]
        constexpr bool operator>=(const reverse_rand_iterator& other) const
        { return ((_iter - other._iter) >= 0); }
        [[nodiscard]]
        constexpr bool operator<=(const reverse_rand_iterator& other) const
        { return ((_iter - other._iter) <= 0); }

        [[nodiscard]]
        constexpr auto operator*() { return *_iter; }
        [[nodiscard]]
        constexpr auto operator*() const { return *_iter; }

        auto operator+(int p)
        {
            auto iter = _iter;
            for (int i = 0; i < p; ++i) {
                if (iter) --iter;
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

    template <typename TyNode>
    class list_iterator {
    public:
        constexpr explicit list_iterator(TyNode* ptr) : _node(ptr) {}
        constexpr void operator++() { _node = _node->_next; }
        constexpr void operator--() { _node = _node->_prev; }
        constexpr void operator++(int) { _node = _node->_next; }
        constexpr void operator--(int) { _node = _node->_next; }

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
		constexpr bool operator==(const std::nullptr_t null) const
		{
			return _node == null;
		}
    private:
        TyNode* _node;
    };
}

#endif //FDTLIBCPP_ITERATOR_H

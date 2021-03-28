#ifndef FDT_SEQUENTIAL_STACK_H
#define FDT_SEQUENTIAL_STACK_H

#include "random/vector.h"

namespace fdt {
    template <typename Ty,
            typename Container = vector<Ty>>
    class stack {
    public:
        using value_type = typename Container::value_type;
        using size_type = typename Container::size_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
    
        constexpr stack() : cont_() {}

        constexpr stack(const stack& other) : cont_(other.cont_) {}

        constexpr stack(stack&& other) : cont_(std::move(other._cont)) {}

        ~stack() = default;

        constexpr stack& operator=(const stack& other)
        {
            stack copy(other);
            copy.swap(*this);
            return *this;
        }

        constexpr stack& operator=(stack&& other)
        {
            stack copy(std::move(other));
            copy.swap(*this);
            return *this;
        }

        [[nodiscard]]
        constexpr bool empty() const noexcept { return cont_.empty(); }

        constexpr size_type size() const noexcept { return cont_.size(); }

        constexpr reference top() { return cont_.back(); }

        constexpr const_reference top() const { return cont_.back(); }

        constexpr void pop()
        {
            cont_.pop_back();
        }

        constexpr void push(const Ty& e)
        {
            cont_.push_back(e);
        }

        template <typename... Args>
        constexpr void emplace(Args&&... args)
        {
            cont_.emplace_back(std::forward<Args>(args)...);
        }

        constexpr void swap(stack& other) noexcept
        {
            swap(other.cont_, cont_);
        }
    private:
        Container cont_;

        friend constexpr bool operator==(const stack&, const stack&);
        friend constexpr bool operator!=(const stack&, const stack&);
        friend constexpr bool operator<(const stack&, const stack&);
        friend constexpr bool operator>(const stack&, const stack&);
        friend constexpr bool operator<=(const stack&, const stack&);
        friend constexpr bool operator>=(const stack&, const stack&);
    };

    template <typename Ty, typename Container>
    constexpr bool operator==(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return (l.cont_ == r.cont_);
    }

    template <typename Ty, typename Container>
    constexpr bool operator!=(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return !(l == r);
    }

    template <typename Ty, typename Container>
    constexpr bool operator<(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return (l.cont_ < r.cont_);
    }

    template <typename Ty, typename Container>
    constexpr bool operator>(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return !(l < r);
    }

    template <typename Ty, typename Container>
    constexpr bool operator<=(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return (l.cont_ <= r.cont_);
    }

    template <typename Ty, typename Container>
    constexpr bool operator>=(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return !(l <= r);
    }
}

#endif
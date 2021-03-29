#ifndef FDT_SEQUENTIAL_STACK_H
#define FDT_SEQUENTIAL_STACK_H

#include "random/vector.h"

namespace fdt {
    /**
     * @brief Stack adaptor interface which represents a LIFO stack
     * data structure, which allows amortized constant insertion and
     * removal of elements from the container. Default container is
     * a vector.
     * @tparam Ty type of data contained in the stack. 
     * @tparam Container template-based container which supports insertion
     * and deletion of elements on the back, preferably with constant
     * time operations.
     */
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

        /**
         * @brief Stack copy assignment operator.
         * @param other another stack object.
         * @return constexpr stack& *this object.
         */
        constexpr stack& operator=(const stack& other)
        {
            stack copy(other);
            copy.swap(*this);
            return *this;
        }

        /**
         * @brief Stack move assignment operator.
         * @param other rvalue reference stack object.
         * @return constexpr stack& *this object.
         */
        constexpr stack& operator=(stack&& other)
        {
            stack copy(std::move(other));
            copy.swap(*this);
            return *this;
        }

        /**
         * @brief Returns a boolean representing the state of the stack.
         * @return true if the stack is empty (size == 0).
         * @return false if the stack is not empty (size > 0).
         */
        [[nodiscard]]
        constexpr bool empty() const noexcept { return cont_.empty(); }

        /**
         * @brief Returns the size of the stack.
         * @return constexpr size_type size of the stack as unsigned
         * integer value.
         */
        constexpr size_type size() const noexcept { return cont_.size(); }

        /**
         * @brief Returns the last-inserted element. This element can be
         * removed from the stack by calling pop().
         * @return constexpr reference to the last-inserted element.
         */
        constexpr reference top() { return cont_.back(); }

        constexpr const_reference top() const { return cont_.back(); }

        /**
         * @brief Removes the last-inserted element from the stack.
         */
        constexpr void pop()
        {
            cont_.pop_back();
        }

        /**
         * @brief Adds a new element on the top of the stack.
         * @param e the new element reference.
         */
        constexpr void push(const Ty& e)
        {
            cont_.push_back(e);
        }

        /**
         * @brief Adds a new element on the top of the stack, constructing
         * it in place.
         * @tparam Args constructor arguments types. 
         * @param args constructor arguments to be forwarded to the type
         * constructor.
         */
        template <typename... Args>
        constexpr void emplace(Args&&... args)
        {
            cont_.emplace_back(std::forward<Args>(args)...);
        }

        /**
         * @brief Swaps the contents of this stack with another stack.
         * @param other another stack object.
         */
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

    /**
     * @brief Stack equality check.
     * @return true if both stacks are equal.
     * @return false if the stacks are not equal.
    */
    template <typename Ty, typename Container>
    constexpr bool operator==(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return (l.cont_ == r.cont_);
    }

    /**
     * @brief Stack non-equality check.
     * @return true if the stacks are not equal.
     * @return false if both stacks are equal.
    */
    template <typename Ty, typename Container>
    constexpr bool operator!=(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return !(l == r);
    }

    /**
     * @brief Stacks lexicographical comparison.
    */
    template <typename Ty, typename Container>
    constexpr bool operator<(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return (l.cont_ < r.cont_);
    }

    /**
     * @brief Stacks lexicographical comparison.
    */
    template <typename Ty, typename Container>
    constexpr bool operator>(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return !(l < r);
    }

    /**
     * @brief Stacks lexicographical comparison.
    */
    template <typename Ty, typename Container>
    constexpr bool operator<=(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return (l.cont_ <= r.cont_);
    }

    /**
     * @brief Stacks lexicographical comparison.
    */
    template <typename Ty, typename Container>
    constexpr bool operator>=(const stack<Ty, Container>& l,
                                const stack<Ty, Container>& r)
    {
        return !(l <= r);
    }
}

#endif
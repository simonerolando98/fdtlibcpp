#ifndef FDT_SEQUENTIAL_DEQUE_H
#define FDT_SEQUENTIAL_DEQUE_H

#include <initializer_list>
#include <memory>
#include <algorithm>
#include "utility.h"
#include "iterator.h"

namespace fdt {
    template <typename Ty, typename Allocator = std::allocator<Ty>>
    class deque {
    public:
        using value_type = Ty;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = Ty&;
        using const_reference = const Ty&;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer = 
            typename std::allocator_traits<Allocator>::const_pointer;
        
        deque(std::size_t n, const Ty& value);
        deque(std::initializer_list<Ty>& ilist);
        deque(const deque& other);
        deque(deque&& other);
        ~deque();
    };
}

#endif
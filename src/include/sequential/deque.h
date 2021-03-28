#ifndef FDT_SEQUENTIAL_DEQUE_H
#define FDT_SEQUENTIAL_DEQUE_H

#include <memory>
#include <initializer_list>
#include <algorithm>
#include "iterator.h"
#include "utility.h"

namespace fdt {
	template <typename Ty, typename Allocator = std::allocator<Ty> >
	class deque {
	public:
		using value_type = Ty;
		using size_type = std::size_t;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;

	};
}

#endif
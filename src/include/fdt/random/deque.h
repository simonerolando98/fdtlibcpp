#ifndef FDT_RANDOM_DEQUE_H
#define FDT_RANDOM_DEQUE_H

#include <fdt/iterator.h>
#include <memory>

namespace fdt {
	template<typename T, typename Allocator = std::allocator<T>>
	class deque {
	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = T&;
		using const_reference = const T&;
		using pointer = T*;
		using const_pointer = const T*;
		using iterator = rand_iterator<T>;
		using const_iterator = const rand_iterator<T>;
	private:
		allocator_type va;
		using va_traits = std::allocator_traits<Allocator>;
		
		pointer* ab;
		pointer* cb;
		pointer* ae;
		pointer* ce;
	};
}

#endif
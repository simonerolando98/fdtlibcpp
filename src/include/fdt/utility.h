#ifndef FDT_UTILITY_H
#define FDT_UTILITY_H

#include <cmath>
#include <iterator>
#include <type_traits>

namespace fdt {
	/**
	 * @brief Checks if a pointer of any type is equal to nullptr.
	 * @tparam Ptr pointer type. Can be deduced at compile time.
	 * @param ptr effective pointer.
	 * @return true if the pointer is null, false otherwise.
	*/
	template <class Ptr>
	constexpr bool is_null(Ptr ptr) { return nullptr == ptr; }
}

#endif

#ifndef FDT_UTILITY_H
#define FDT_UTILITY_H

#include <cmath>
#include <iterator>
#include <type_traits>

namespace fdt {
	/**
	 * @brief Simple reimplementation of a pair of data.
	 * @tparam Tx first element type.
	 * @tparam Ty second element type.
	 */
	template <typename Tx, typename Ty>
	struct pair {
		using first_type = Tx;
		using second_type = Ty;

		constexpr pair() = default;

		constexpr pair(const Tx& first, const Ty& second)
			: first(first), second(second) {}

		constexpr pair(Tx&& first, Ty&& second)
			: first(std::move(first)), second(std::move(second)) {}

		constexpr pair(const pair& other)
			: first(other.first), second(other.second) {}

		constexpr pair(pair&& other)
			: first(std::move(other.first)), second(std::move(other.second)) {}

		constexpr pair& operator=(const pair& other)
		{
			pair copy(other);
			copy.swap(*this);
			return *this;
		}

		constexpr pair& operator=(pair&& other)
		{
			pair copy(std::move(other));
			copy.swap(*this);
			return *this;
		}

		/**
		 * @brief Swaps current pair instance with another.
		 * @param other another pair instance.
		 */
		constexpr void swap(pair& other)
		{
			std::swap(other.first, first);
			std::swap(other.second, second);
		}

		first_type first;
		second_type second;
	};

	template <typename Tx, typename Ty>
	constexpr bool operator==(const pair<Tx, Ty>& l, const pair<Tx, Ty>& r)
	{
		return (l.first == r.first && l.second == r.second);
	}

	template <typename Tx, typename Ty>
	constexpr bool operator!=(const pair<Tx, Ty>& l, const pair<Tx, Ty>& r)
	{
		return !(l == r);
	}

	template <typename Tx, typename Ty>
	constexpr bool operator<(const pair<Tx, Ty>& l, const pair<Tx, Ty>& r)
	{
		return (l.first < r.first || l.second < r.second);
	}

	template <typename Tx, typename Ty>
	constexpr bool operator>(const pair<Tx, Ty>& l, const pair<Tx, Ty>& r)
	{
		return !(l < r);
	}

	template <typename Tx, typename Ty>
	constexpr bool operator<=(const pair<Tx, Ty>& l, const pair<Tx, Ty>& r)
	{
		return (l.first <= r.first || l.second <= r.second);
	}

	template <typename Tx, typename Ty>
	constexpr bool operator>=(const pair<Tx, Ty>& l, const pair<Tx, Ty>& r)
	{
		return !(l <= r);
	}

	template <typename Tx, typename Ty>
	constexpr void swap(pair<Tx, Ty>& l, pair<Tx, Ty>& r)
	{
		l.swap(r);
	}

	template <typename Tx, typename Ty>
	constexpr void swap(pair<Tx, Ty>&& l, pair<Tx, Ty>& r)
	{
		l.swap(r);
	}

	template <typename Tx, typename Ty>
	constexpr void swap(pair<Tx, Ty>& l, pair<Tx, Ty>&& r)
	{
		l.swap(r);
	}

	template <typename Tx, typename Ty>
	constexpr pair<Tx, Ty> make_pair(Tx f, Ty s)
	{
		return pair<Tx, Ty>(f, s);
	}

	template <std::size_t I, typename Tx, typename Ty>
	constexpr auto& get(pair<Tx, Ty>& p)
	{
		if constexpr (I < 2) {
			if constexpr (I == 0) return p.first;
			if constexpr (I == 1) return p.second;
		}
	}

	template <std::size_t I, typename Tx, typename Ty>
	constexpr const auto& get(const pair<Tx, Ty>& p)
	{
		if constexpr (I < 2) {
			if constexpr (I == 0) return p.first;
			if constexpr (I == 1) return p.second;
		}
	}

	template <std::size_t I, typename Tx, typename Ty>
	constexpr auto get(pair<Tx, Ty>&& p)
	{
		if constexpr (I < 2) {
			if constexpr (I == 0) return p.first;
			if constexpr (I == 1) return p.second;
		}
	}

	/**
	 * @brief Checks if a pointer of any type is equal to nullptr.
	 * @tparam Ptr pointer type. Can be deduced at compile time.
	 * @param ptr effective pointer.
	 * @return true if the pointer is null, false otherwise.
	*/
	template <class Ptr>
	constexpr bool is_null(Ptr ptr) { return nullptr == ptr; }

	constexpr bool is_null(std::nullptr_t) { return true; }
}

#endif

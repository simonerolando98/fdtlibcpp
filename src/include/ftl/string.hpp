#ifndef FTL_STRING
#define FTL_STRING

#include <ftl/iterator>
#include <algorithm>
#include <exception>
#include <stdexcept>

namespace ftl {
	template <
		typename CharT,
		class Allocator = std::allocator<CharT>
	>
	class basic_string {
	public:
		using value_type = CharT;
		using allocator_type = Allocator;
		using size_type = allocator_traits::size_type;
		using difference_type = allocator_traits::difference_type;
		using reference = CharT&;
		using const_reference = const CharT&;
		using pointer = CharT*;
		using const_pointer = const CharT*;
		class iterator;
		class const_iterator;
		using reverse_iterator = ftl::reverse_iterator<iterator>;
		using const_reverse_iterator = ftl::const_reverse_iterator<iterator>;

		static const size_type npos = -1;

		constexpr explicit basic_string(const Allocator& alloc) noexcept
		: b_(empty_str_), s_(0), c_(0), a_(alloc)
		{}

		constexpr basic_string() noexcept : basic_string(Allocator()) {}

		constexpr basic_string(size_type count,
			CharT ch, const Allocator& alloc = Allocator())
		: s_(count), c_(count), a_(alloc)
		{
			b_ = s_ < sbsize_ ? sb_ : allocator_traits::allocate(a_, c_);
			std::fill_n(b_, s_, ch);
		}

		constexpr basic_string(const basic_string& other, size_type pos,
			const Allocator& alloc = Allocator())
		: a_(alloc)
		{
			c_ = s_ = other.size() - pos;
			b_ = s_ < sbsize_ ? sb_ : allocator_traits::allocate(a_, c_);

			if (s_ > sbsize_)
				for (size_t i = pos; i < s_; ++i)
					allocator_traits::construct(a_, b_ + i, *(other.b_ + i));
			else
				std::copy(other.b_ + pos, other.b_ + other.size() - 1, b_);
		}

		constexpr basic_string(const basic_string& other, size_type pos,
			size_type count,
			const Allocator& alloc = Allocator())
		: a_(alloc)
		{
			c_ = s_ = other.size() - pos - count;
			b_ = s_ < sbsize_ ? sb_ : allocator_traits::allocate(a_, c_);

			if (s_ > sbsize_)
				for (size_t i = 0; i < count; ++i)
					allocator_traits::construct(a_, b_ + i);
			std::copy(other.b_ + pos, other.b_ + count - 1, b_);
		}

		~basic_string()
		{
			if (s_ > sbsize_) allocator_traits::deallocate(a_, b_, c_);
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return (c_ == 0 || s_ == 0 || b_ == empty_str_
					|| begin() == end());
		}

		constexpr size_type size() const noexcept
		{
			return s_;
		}

		constexpr size_type length() const noexcept
		{
			return s_;
		}

		constexpr size_type max_size() const noexcept
		{
			return std::numeric_limits<std::size_t>::max() / sizeof(CharT);
		}

		constexpr size_type capacity() const noexcept
		{
			return c_;
		}

		constexpr void reserve(size_type new_cap)
		{
			if (new_cap > max_size())
				throw std::length_error(
					"error: string capacity exceeds system limits"
			);
			if (new_cap <= c_) return;

			c_ = new_cap;
			auto tmp = allocator_traits::allocate(a_, c_);
			for (size_t i = 0; i < s_; ++i)
				allocator_traits::construct(a_, tmp  + i, *(b_ + i));
			b_ = tmp;
			*(b_ + size() + 1) = 0;
			
			allocator_traits::deallocate(a_, tmp, c_);
		}

	private:
		using allocator_traits = std::allocator_traits<Allocator>;
		static constexpr size_t sbsize_ = 30;
		static const CharT* empty_str_ = "\0";
		CharT b_;
		CharT sb_[sbsize_];
		size_type s_;
		size_type c_;
		Allocator a_;
	};
}

#endif

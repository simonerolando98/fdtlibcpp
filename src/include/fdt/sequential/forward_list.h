#ifndef FDT_SEQUENTIAL_SINGLY_LINKED_LIST_H
#define FDT_SEQUENTIAL_SINGLY_LINKED_LIST_H

#include <cstddef>
#include <memory>
#include <utility>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <fdt/utility.h>
#include <fdt/iterator.h>

namespace fdt {
	template <typename Tx>
	struct fwd_list_node {
	public:
		using value_type = Tx;

		constexpr fwd_list_node() : next_(nullptr) {}

		constexpr fwd_list_node(const Tx& data, fwd_list_node<Tx>* next = nullptr)
			: data_(data), next_(next) {}

		template <typename... Args>
		constexpr fwd_list_node(Args&&... args, fwd_list_node<Tx>* next = nullptr)
			: data_(std::forward<Args>(args)...), next_(next) {}

		Tx data_;
		fwd_list_node<Tx>* next_;
	};

	template <typename Ty, 
		typename Allocator = std::allocator<fwd_list_node<Ty>>>
	class forward_list {
	public:
		using value_type = Ty;
		using allocator_type = Allocator;
		using reference = Ty&;
		using const_reference = const Ty&;
		using pointer = Ty*;
		using const_pointer = const Ty*;
		using iterator = forward_list_iterator<fwd_list_node<Ty>>;
		using const_iterator = const forward_list_iterator<fwd_list_node<Ty>>;

		constexpr forward_list()
		{
			before_start_->next_ = start_;
		}
		
		constexpr explicit forward_list(size_t n)
		{
			for (size_t i = 0; i < n; ++i) emplace_front();
			before_start_->next_ = start_;
		}

		constexpr explicit forward_list(size_t n, const Ty& val)
		{
			for (size_t i = 0; i < n; ++i) push_front(val);
			before_start_->next_ = start_;
		}

		constexpr forward_list(const forward_list& fwdlist)
		{
			for (auto it = fwdlist.begin(); it != fwdlist.end(); ++it)
				emplace_back(*it);
			before_start_->next_ = start_;
		}

		constexpr forward_list(forward_list&& fwdlist)
			: start_(std::move(fwdlist.start_))
		{
			fwdlist.start_ = nullptr;
			fwdlist.before_start_->next_ = nullptr;
			before_start_->next_ = start_;
		}

		constexpr forward_list(std::initializer_list<Ty> ilist)
		{
			for (auto it = std::rbegin(ilist); it != std::rend(ilist); ++it)
				emplace_front(*it);
			before_start_->next_ = start_;
		}

		constexpr forward_list& operator=(const forward_list& fwdlist)
		{
			forward_list copy(fwdlist);
			copy.swap(*this);
			return *this;
		}

		constexpr forward_list& operator=(forward_list&& fwdlist)
		{
			forward_list copy(std::move(fwdlist));
			copy.swap(*this);
			return *this;
		}

		constexpr forward_list& operator=(std::initializer_list<Ty> ilist)
		{
			forward_list copy(ilist);
			copy.swap(*this);
			return *this;
		}

		~forward_list()
		{
			clear();
			allocator_traits::deallocate(alloc_, before_start_, 1);
		}

		[[nodiscard]]
		constexpr bool empty() const noexcept { return is_null(start_); }

		constexpr reference front() noexcept
		{
			return start_->data_;
		}

		constexpr const_reference front() const noexcept
		{
			return start_->data_;
		}

		constexpr void push_front(const Ty& val)
		{
			if (is_null(start_)) {
				start_ = allocator_traits::allocate(alloc_, 1);
				allocator_traits::construct(alloc_, start_, val);
				before_start_->next_ = start_;
			} else {
				auto n = allocator_traits::allocate(alloc_, 1);
				allocator_traits::construct(alloc_, n, val, start_);
				start_ = n;
				before_start_->next_ = start_;
			}
		}

		constexpr void push_front(Ty&& val)
		{
			if (is_null(start_)) {
				start_ = allocator_traits::allocate(alloc_, 1);
				allocator_traits::construct(alloc_, start_, std::move(val));
				before_start_->next_ = start_;
			} else {
				auto n = allocator_traits::allocate(alloc_, 1);
				allocator_traits::construct(alloc_, n, std::move(val), start_);
				start_ = n;
				before_start_->next_ = start_;
			}
		}

		template <typename... Args>
		constexpr void emplace_front(Args&&... args)
		{
			if (is_null(start_)) {
				start_ = allocator_traits::allocate(alloc_, 1);
				allocator_traits::construct(alloc_, start_,
					std::forward<Args>(args)...);
				before_start_->next_ = start_;
			} else {
				auto n = allocator_traits::allocate(alloc_, 1);
				allocator_traits::construct(alloc_, n,
					std::forward<Args>(args)..., start_);
				start_ = n;
				before_start_->next_ = start_;
			}
		}

		constexpr void pop_front()
		{
			if (is_null(start_)) return;

			auto del = start_;
			start_ = start_->next_;
			allocator_traits::deallocate(alloc_, del, 1);
			before_start_->next_ = start_;
		}

		constexpr iterator insert_after(const_iterator pos, const Ty& val)
		{
			auto ins_pos = pos.node_->next_;
			auto n = allocator_traits::allocate(alloc_, 1);
			allocator_traits::construct(alloc_, n, val, ins_pos);
			pos.node_->next_ = n;
			before_start_->next_ = start_;
			return iterator(n);
		}

		constexpr iterator insert_after(const_iterator pos, Ty&& val)
		{
			auto ins_pos = pos.node_->next_;
			auto n = allocator_traits::allocate(alloc_, 1);
			allocator_traits::construct(alloc_, n, std::move(val), ins_pos);
			pos.node_->next_ = n;
			before_start_->next_ = start_;
			return iterator(n);
		}

		constexpr iterator
		insert_after(const_iterator pos, size_t count, const Ty& val)
		{
			if (count == 0) return pos;
			iterator it;
			for (size_t i = 0; i < count; ++i) it = insert_after(pos + i, val);
			before_start_->next_ = start_;
			return it;
		}

		template <typename InIterator>
		constexpr iterator
		insert_after(const_iterator pos, InIterator first, InIterator last)
		{
			if (first == last) return pos;
			iterator it = pos;
			iterator ret = nullptr;
			for (auto iit = first; iit != last; ++iit) {
				ret = insert_after(it, *iit);
				++it;
			}
			before_start_->next_ = start_;
			return ret;
		}

		constexpr iterator
		insert_after(const_iterator pos, std::initializer_list<Ty> ilist)
		{
			if (ilist.begin() == ilist.end()) return pos;
			size_t i = 0;
			iterator ret = nullptr;
			for (const auto& x : ilist) {
				ret = insert_after(pos + i, x);
				++i;
			}
			before_start_->next_ = start_;
			return ret;
		}

		template <typename... Args>
		constexpr iterator emplace_after(const_iterator pos, Args&&... args)
		{
			auto ins_pos = pos.node_->next_;
			auto n = allocator_traits::allocate(alloc_, 1);
			allocator_traits::construct(alloc_, n,
				std::forward<Args>(args)..., ins_pos);
			pos.node_->next_ = n;
			before_start_->next_ = start_;
			return iterator(n);
		}

		constexpr iterator erase_after(const_iterator pos)
		{
			auto del = pos.node_->next_;
			auto node = pos.node_;
			node->next_ = del->next_;
			allocator_traits::deallocate(alloc_, del, 1);
			before_start_->next_ = start_;
			return iterator(node->next_);
		}

		constexpr iterator
		erase_after(const_iterator first, const_iterator last)
		{
			auto dist = distance(first, last);
			iterator it = nullptr;
			for (ptrdiff_t i = 0; i < dist; ++i)
				it = erase_after(first);
			return it;
		}

		constexpr void clear() noexcept
		{
			if (is_null(start_)) return;
			auto cp = start_;
			auto del = start_;

			while (!is_null(cp->next_)) {
				del = cp;
				cp = cp->next_;
				allocator_traits::deallocate(alloc_, del, 1);
			}
		}

		constexpr iterator begin() noexcept
		{
			return iterator(start_);
		}

		constexpr const_iterator begin() const noexcept
		{
			return iterator(start_);
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return iterator(start_);
		}

		constexpr iterator end() noexcept
		{
			return iterator(nullptr);
		}

		constexpr const_iterator end() const noexcept
		{
			return iterator(nullptr);
		}

		constexpr const_iterator cend() const noexcept
		{
			return iterator(nullptr);
		}

		constexpr iterator before_begin() noexcept
		{
			return iterator(before_start_);
		}

		constexpr const_iterator before_begin() const noexcept
		{
			return iterator(before_start_);
		}

		constexpr const_iterator cbefore_begin() const noexcept
		{
			return iterator(before_start_);
		}

	private:
		template <typename... Args>
		constexpr void emplace_back(Args&&... args)
		{
			if (is_null(start_))
				return emplace_front(std::forward<Args>(args)...);
			auto cp = start_;
			while (!is_null(cp->next_)) cp = cp->next_;
			cp->next_ = allocator_traits::allocate(alloc_, 1);
			allocator_traits::construct(alloc_, cp->next_,
				std::forward<Args>(args)...);
		}

		using allocator_traits = std::allocator_traits<Allocator>;
		using list_type = fwd_list_node<Ty>*;

		list_type start_ = nullptr;
		list_type before_start_ = allocator_traits::allocate(alloc_, 1);
		allocator_type alloc_;
	};
}

#endif

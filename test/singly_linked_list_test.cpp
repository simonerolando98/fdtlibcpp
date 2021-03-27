#include "gtest/gtest.h"
#include "fdt/sequential/singly_linked_list.h"
#include <array>

TEST(singly_linked_list, construct_default)
{
	fdt::singly_linked_list<int> list;
	ASSERT_TRUE(list.empty());
	ASSERT_EQ(0, list.size());
}

TEST(singly_linked_list, size)
{
	fdt::singly_linked_list<int> list;
	list.push_front(3);
	list.push_front(4);
	ASSERT_EQ(2, list.size());
}

TEST(singly_linked_list, empty)
{
	fdt::singly_linked_list<int> empty;
	fdt::singly_linked_list<int> nonempty;

	nonempty.push_front(5);

	ASSERT_TRUE(empty.empty());
	ASSERT_FALSE(nonempty.empty());
}

TEST(singly_linked_list, clear)
{
	fdt::singly_linked_list<int> list;
	list.push_front(5);
	list.push_front(10);
	list.push_front(25);

	ASSERT_EQ(3, list.size());
	list.clear();
	ASSERT_EQ(0, list.size());
	ASSERT_TRUE(list.empty());
}

TEST(singly_linked_list, begin)
{
	fdt::singly_linked_list<int> list;
	list.push_front(2);
	list.push_front(3);
	ASSERT_EQ(3, *list.begin());
}

TEST(singly_linked_list, end)
{
	fdt::singly_linked_list<int> list;
	list.push_front(2);
	list.push_front(3);
	ASSERT_EQ(list.end(), nullptr);
}

TEST(singly_linked_list, iterator_traverse)
{
	fdt::singly_linked_list<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	std::array<int, 3> xa = { 3, 2, 1 };

	size_t i = 0;
	for (auto x : list) {
		ASSERT_EQ(xa[i], x);
		++i;
	}
}

TEST(singly_linked_list, front)
{
	fdt::singly_linked_list<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	ASSERT_EQ(3, list.front());
}

TEST(singly_linked_list, back)
{
	fdt::singly_linked_list<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	ASSERT_EQ(1, list.back());
}

TEST(singly_linked_list, const_front)
{
	fdt::singly_linked_list<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	const auto clist = list;
	ASSERT_EQ(3, static_cast<const fdt::singly_linked_list<int>>(list).front());
}

TEST(singly_linked_list, const_back)
{
	fdt::singly_linked_list<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	const auto clist = list;
	ASSERT_EQ(1, clist.back());
}

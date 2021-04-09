#include "gtest/gtest.h"
#include <fdt/sequential/list.h>
#include <array>

TEST(linked_list, construct_default)
{
    fdt::list<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQ(0, list.size());
}

TEST(linked_list, push_front)
{
    fdt::list<int> list;
    list.push_front(5);
    list.push_front(9);
    ASSERT_EQ(9, list.front());
}

TEST(linked_list, push_back)
{
    fdt::list<int> list;
    list.push_back(5);
    list.push_back(9);
    ASSERT_EQ(9, list.back());
}

TEST(linked_list, emplace_front)
{
    fdt::list<std::string> list;
    list.emplace_front("test1");
    list.emplace_front("test2");
    ASSERT_EQ("test2", list.front());
}

TEST(linked_list, pop_front)
{
	fdt::list<int> list;
	list.push_back(5);
	list.push_back(9);
	ASSERT_EQ(5, list.front());
	list.pop_front();
	ASSERT_EQ(9, list.front());
}

TEST(linked_list, pop_back)
{
    fdt::list<int> list;
    list.push_back(5);
    list.push_back(9);
    ASSERT_EQ(9, list.back());
    list.pop_back();
    ASSERT_EQ(5, list.back());
}

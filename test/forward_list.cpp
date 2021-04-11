#include "gtest/gtest.h"
#include <ftl/sequential/forward_list>
#include <array>
#include <iostream>

using namespace ftl;

TEST(forward_list, construct_default)
{
	forward_list<int> l;
    (void)l;
}

TEST(forward_list, construct_ilist)
{
    forward_list<int> l { 1, 2, 3, 4 };
    auto size = distance(l.begin(), l.end());
    ASSERT_EQ(4, size);
    (void)l;
}

TEST(forward_list, construct_copy)
{
    forward_list<int> l { 1, 2, 3, 4 };
    forward_list<int> c(l);
    ASSERT_EQ(distance(l.begin(), l.end()), distance(c.begin(), c.end()));
    (void)l;
    (void)c;
}

TEST(forward_list, construct_move)
{
    forward_list<int> x(std::move(forward_list<int>{1, 3, 4, 5}));
    ASSERT_EQ(4, distance(x.begin(), x.end()));
    (void)x;
}

TEST(forward_list, assignment_copy)
{
    forward_list<int> x { 1, 2, 3, 4, 5 };
    forward_list<int> y = x;
    auto it = y.begin();
    for (const auto& v : x) {
        ASSERT_EQ(*it, v);
        ++it;
    }
    (void)x;
    (void)y;
}

TEST(forward_list, assignment_move)
{
    forward_list<int> x = std::move(forward_list<int> { 1, 2, 3, 4, 5 });
    forward_list<int> y { 1, 2, 3, 4, 5 };

    auto it = y.begin();
    for (const auto& v : x) {
        ASSERT_EQ(*it, v);
        ++it;
    }

    (void)x;
    (void)y;
}

TEST(forward_list, assignment_ilist)
{
    forward_list<int> x = { 1, 2, 3, 4, 5 };
    ASSERT_EQ(5, distance(x.begin(), x.end()));
    (void)x;
}

TEST(forward_list, empty)
{
    forward_list<int> e;
    ASSERT_TRUE(e.empty());
    forward_list<int> x { 1, 2, 3, 4 };
    ASSERT_FALSE(x.empty());
    (void)e;
    (void)x;
}

TEST(forward_list, push_front)
{
    forward_list<int> x;
    x.push_front(1);
    x.push_front(2);
    x.push_front(3);
    x.push_front(4);
    forward_list<int> cmp { 4, 3, 2, 1 };

    auto it = cmp.begin();
    for (const auto& v : x) {
        ASSERT_EQ(*it, v);
        ++it;
    }

    (void)x;
    (void)cmp;
}

TEST(forward_list, push_front_move)
{
    forward_list<int> x;
    x.push_front(std::move(5));
    x.push_front(std::move(3));
    x.push_front(std::move(2));
    x.push_front(std::move(1));
    forward_list<int> cmp { 1, 2, 3, 5 };

    auto it = cmp.begin();
    for (const auto& v : x) {
        ASSERT_EQ(*it, v);
        ++it;
    }

    (void)x;
    (void)cmp;
}

TEST(forward_list, emplace_front)
{
    forward_list<std::string> x { "World" };
    x.emplace_front("Hello");
    ASSERT_EQ("Hello", x.front());
    (void)x;
}

TEST(forward_list, insert_after_pos_1e)
{
    forward_list<int> x { 1, 2, 3, 4, 5 };
    x.insert_after(x.begin() + 2, 9);

    auto y = {1, 2, 3, 9, 4, 5 };
    auto it = x.begin();

    for (const auto& v : y) {
        ASSERT_EQ(*it, v);
        ++it;
    }
    (void)x;
}

TEST(forward_list, insert_after_pos_2e_ilist)
{
    forward_list<int> x {1, 2, 3, 4, 5 };
    x.insert_after(x.begin() + 2, { 1, 2 });

    auto it = x.begin();

    for (const auto& v : x) {
        ASSERT_EQ(*it, v);
        ++it;
    }

    (void)x;
}

TEST(forward_list, insert_after_pos_iterable)
{
    forward_list<int> x { 1, 2, 3, 4 , 5 };
    std::array<int, 4> y { 9, 3, 6, 2 };

    x.insert_after(x.begin() + 2, y.begin(), y.end());

    std::array<int, 9> cmp = { 1, 2, 3, 9, 3, 6, 2, 4, 5 };
    auto it = x.begin();

    for (auto ait = cmp.begin(); ait != cmp.end(); ++ait) {
        ASSERT_EQ(*it, *ait);
        ++it;   
    }

    (void)x;
}

TEST(forward_list, emplace_after_pos)
{
    forward_list<std::string> x { "Hello, ", " Simone" };
    x.emplace_after(x.begin(), "my name is");
    auto y = { "Hello, ", "my name is", " Simone" };

    auto it = x.begin();
    for (const auto& v : y) {
        ASSERT_EQ(*it, v);
        ++it;
    }

    (void)x;
}

TEST(forward_list, erase_after_1e)
{
    forward_list<int> x { 1, 2, 3, 4, 5 };
    x.erase_after(x.begin() + 2);
    auto y = { 1, 2, 3, 5 };

    auto it = y.begin();
    for (const auto& v : x) {
        ASSERT_EQ(*it, v);
        ++it;
    }

    (void)x;
}

TEST(forward_list, erase_after_4e)
{
    forward_list<int> x { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    x.erase_after(x.begin() + 2, x.begin() + 7);
    auto cmp = { 1, 2, 3, 9 };

    auto it = cmp.begin();
    for (const auto& v : x) {
        ASSERT_EQ(*it, v);
        ++it;
    }

    (void)x;
}

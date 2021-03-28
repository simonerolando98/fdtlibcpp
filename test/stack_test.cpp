#include "gtest/gtest.h"
#include "sequential/stack.h"
#include <string>

TEST(stack, construct_default)
{
    fdt::stack<int> s;
    (void)s;
}

TEST(stack, empty)
{
    fdt::stack<int> s;
    ASSERT_TRUE(s.empty());
    (void)s;
}

TEST(stack, size)
{
    fdt::stack<int> s;
    ASSERT_EQ(0, s.size());
    s.push(1);
    s.push(9);
    ASSERT_EQ(2, s.size());
    (void)s;
}

TEST(stack, top)
{
    fdt::stack<int> s;
    s.push(5);
    s.push(10);
    s.push(25);
    s.push(255);
    ASSERT_EQ(255, s.top());
    (void)s;
}

TEST(stack, pop)
{
    fdt::stack<int> s;
    s.push(43);
    s.push(255);
    s.push(1024);
    ASSERT_EQ(1024, s.top());
    s.pop();
    ASSERT_EQ(255, s.top());
    s.pop();
    ASSERT_EQ(43, s.top());
    s.pop();
    ASSERT_TRUE(s.empty());
    (void)s;
}

TEST(stack, push)
{
    fdt::stack<int> s;
    ASSERT_TRUE(s.empty() && s.size() == 0);
    s.push(5);
    ASSERT_FALSE(s.empty());
    ASSERT_EQ(1, s.size());
    (void)s;
}

TEST(stack, emplace)
{
    fdt::stack<std::string> s;
    s.emplace("Hello");
    s.emplace("World");
    ASSERT_EQ("World", s.top());
    s.pop();
    ASSERT_EQ("Hello", s.top());
    (void)s;
}

#include "gtest/gtest.h"
#include <ftl/stack>
#include <string>

using namespace ftl;

TEST(stack, construct_default)
{
    stack<int> s;
    (void)s;
}

TEST(stack, empty)
{
    stack<int> s;
    ASSERT_TRUE(s.empty());
    (void)s;
}

TEST(stack, size)
{
    stack<int> s;
    ASSERT_EQ(0, s.size());
    s.push(1);
    s.push(9);
    ASSERT_EQ(2, s.size());
    (void)s;
}

TEST(stack, top)
{
    stack<int> s;
    s.push(5);
    s.push(10);
    s.push(25);
    s.push(255);
    ASSERT_EQ(255, s.top());
    (void)s;
}

TEST(stack, pop)
{
    stack<int> s;
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
    stack<int> s;
    ASSERT_TRUE(s.empty() && s.size() == 0);
    s.push(5);
    ASSERT_FALSE(s.empty());
    ASSERT_EQ(1, s.size());
    (void)s;
}

TEST(stack, emplace)
{
    stack<std::string> s;
    s.emplace("Hello");
    s.emplace("World");
    ASSERT_EQ("World", s.top());
    s.pop();
    ASSERT_EQ("Hello", s.top());
    (void)s;
}

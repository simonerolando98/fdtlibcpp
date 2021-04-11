#include <gtest/gtest.h>
#include <ftl/queue>

using namespace ftl;

TEST(queue, default_construct)
{
    queue<int> q;
    (void)q;
}

TEST(queue, construct_with_list)
{
    list<int> l;
    l.push_front(5);
    l.push_front(4);
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);

    queue<int> q(l);
    ASSERT_EQ(q.front(), 1);
    ASSERT_EQ(q.back(), 5);
}

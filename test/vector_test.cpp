#include "gtest/gtest.h"
#include "fdt/rand_struct/vector.h"

TEST(vector, construct_default)
{
    fdt::vector<int> x;
    (void)x;
}

TEST(vector, construct_with_size)
{
    const auto defalloc = 8;
    const auto size = 50;
    fdt::vector<int> x(size);

    ASSERT_EQ(size, x.size());
    ASSERT_EQ(size + defalloc, x.capacity());
    (void)x;
}

TEST(vector, construct_with_ilist)
{
    const auto defalloc = 8;
    fdt::vector<int> x{ 1, 2, 3, 4, 5 };
    ASSERT_EQ(5, x.size());
    ASSERT_EQ(5 + defalloc, x.capacity());
    ASSERT_EQ(1, x[0]);
    (void)x;
}

TEST(vector, empty)
{
    const auto defalloc = 8;
    fdt::vector<int> x;
    ASSERT_TRUE(x.empty());
    ASSERT_EQ(defalloc, x.capacity());
    (void)x;
}

TEST(vector, size)
{
    const auto defalloc = 8;
    fdt::vector<int> x{ 1, 2, 3, 4 };
    ASSERT_EQ(4, x.size());
    ASSERT_EQ(4 + defalloc, x.capacity());
    (void)x;
}

TEST(vector, capacity)
{
    const auto defalloc = 8;
    fdt::vector<int> x;
    ASSERT_EQ(defalloc, x.capacity());
    (void)x;
}

TEST(vector, front_back)
{
    const fdt::vector<int> x{ 1, 2, 3, 4 };
    ASSERT_EQ(1, x.front());
    ASSERT_EQ(4, x.back());
    (void)x;
}

TEST(vector, data)
{
    const fdt::vector<int> x{ 1, 2, 3, 4 };
    ASSERT_NE(nullptr, x.data());
    const auto x_data = x.data();
    ASSERT_EQ(x[0], x_data[0]);
    (void)x;
}

TEST(vector, at)
{
    const fdt::vector<int> x{ 1, 2, 3, 4, 5, 6 };
    ASSERT_THROW(auto y = x.at(6), fdt::array_out_of_range);
    ASSERT_NO_THROW(auto y = x.at(2));
    auto y = x.at(2);
    ASSERT_EQ(3, y);
    (void)x;
}

TEST(vector, begin_end)
{
    fdt::vector<int> x{ 1, 2, 3, 4, 5 };
    auto begin = x.begin();
    auto end = x.end();
    ASSERT_NE(begin, end);
    auto begin_val = *begin;
    --end;
    auto end_val = *end;
    ASSERT_EQ(begin_val, x.front());
    ASSERT_EQ(end_val, x.back());
    (void)x;
}

TEST(vector, iter_traversal)
{
    fdt::vector<int> x{ 1, 1, 1, 1, 1 };
    for (const auto& y : x) ASSERT_EQ(1, y);
    (void)x;
}

TEST(vector, push_back)
{
    fdt::vector<int> x;
    x.push_back(1);
    x.push_back(2);
    ASSERT_EQ(1, x.front());
    ASSERT_EQ(2, x.back());
    (void)x;
}

TEST(vector, emplace_back)
{
    fdt::vector<std::string> strs;
    strs.emplace_back("Hello");
    strs.emplace_back("World");
    ASSERT_EQ("Hello", strs[0]);
    ASSERT_EQ("World", strs[1]);
    (void)strs;
}

TEST(vector, resize)
{
    fdt::vector<std::string> strs({
        "Barbara",
        "Maurizio",
        "Andrea",
        "Simone"
    });
    const auto init_capacity = strs.capacity();
    strs.emplace_back("Elisabetta");
    ASSERT_EQ(5, strs.size());
    strs.resize(2);
    ASSERT_EQ(2, strs.size());
    ASSERT_EQ(init_capacity, strs.capacity());
    (void)strs;
}

TEST(vector, operator_equality)
{
    fdt::vector<std::string> strs {
        "Hello",
        "World"
    };
    auto strs1 = strs;
    ASSERT_EQ(strs, strs1);
    (void)strs;
    (void)strs1;
}

TEST(vector, operator_nequality)
{
    fdt::vector<std::string> strs {
        "Hello",
        "World"
    };
    auto strs1 = strs;
    strs1.push_back("World2");
    ASSERT_NE(strs, strs1);
    (void)strs;
    (void)strs1;
}

TEST(vector, operator_add)
{
    fdt::vector<int> v { 1, 2, 3 };
    fdt::vector<int> u { 2, 3, 4 };
    auto sum = v + u;
    ASSERT_EQ(3, sum[0]);
    ASSERT_EQ(5, sum[1]);
    ASSERT_EQ(7, sum[2]);
    u.push_back(2);
    ASSERT_THROW(sum = u + v, fdt::vector_size_mismatch);
    (void)sum;
    (void)u;
    (void)v;
}

TEST(vector, operator_sub)
{
    fdt::vector<int> v { 1, 2, 3 };
    fdt::vector<int> u { 2, 3, 4 };
    auto sub = v - u;
    ASSERT_EQ(-1, sub[0]);
    ASSERT_EQ(-1, sub[1]);
    ASSERT_EQ(-1, sub[2]);
    u.push_back(2);
    ASSERT_THROW(sub = u - v, fdt::vector_size_mismatch);
    (void)sub;
    (void)u;
    (void)v;
}

TEST(vector, reverse_iterator_traversal)
{
    fdt::vector<int> v { 1, 2, 3, 4 };
    fdt::vector<int> u { 4, 3, 2, 1 };

    size_t i = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        ASSERT_EQ(*it, u[i]);
        ++i;
    }
    (void)v;
    (void)u;
}

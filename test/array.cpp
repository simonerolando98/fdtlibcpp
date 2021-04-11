#include "gtest/gtest.h"
#include <ftl/random/array>
#include <numeric>

using namespace ftl;

TEST(array, construct_default)
{
	array<int, 4> arr;
	(void)arr;
}

TEST(array, construct_copy)
{
	array<int, 2> arr;
	arr[0] = 1;
	arr[1] = 0;

	array<int, 2> copy(arr);
	ASSERT_EQ(arr[0], copy[0]);
	ASSERT_EQ(arr[1], copy[1]);

	(void)arr;
	(void)copy;
}

TEST(array, construct_init_list)
{
	array<int, 3> arr { 1, 2, 3 };
	ASSERT_EQ(1, arr[0]);
	ASSERT_EQ(2, arr[1]);
	ASSERT_EQ(3, arr[2]);
	(void)arr;
}

TEST(array, size)
{
	array<int, 3> arr;
	ASSERT_EQ(3, arr.size());
	(void)arr;
}

TEST(array, empty)
{
	array<int, 0> arr;
	ASSERT_TRUE(arr.empty());
	array<int, 5> e_arr;
	ASSERT_FALSE(e_arr.empty());
}

TEST(array, front_back)
{
	array<int, 2> arr;
	arr[0] = 1;
	arr[1] = 5;
	ASSERT_EQ(1, arr.front());
	ASSERT_EQ(5, arr.back());
	(void)arr;
}

TEST(array, data)
{
	array<int, 2> arr;
	ASSERT_TRUE(arr.data() != nullptr);
	(void)arr;
}

TEST(array, begin)
{
	array<int, 3> arr { 1, 2, 3 };
	auto begin = arr.begin();

	ASSERT_EQ(*begin, arr[0]);
	(void)arr;
}

TEST(array, end)
{
	array<int, 3> arr { 1, 2, 3 };
	ASSERT_NE(arr.begin(), arr.end());
	(void)arr;
}

TEST(array, at)
{
	array<int, 3> arr { 1, 2, 3 };
	ASSERT_NO_THROW(arr.at(0));
	ASSERT_THROW(arr.at(3), array_out_of_range);
	ASSERT_EQ(2, arr.at(1));
	(void)arr;
}

TEST(array, iterator_test)
{
	array<int, 5> arr { 1, 6, 2, 9, 5 };
	auto sum = std::accumulate(std::begin(arr), std::end(arr), 0);
	ASSERT_EQ(23, sum);
	(void)arr;
}

TEST(array, reverse_iterator_test)
{
	const array<int, 5> arr{ 1, 2, 3, 4, 5 };
	const array<int, 5> rev{ 5, 4, 3, 2, 1 };
	size_t i = 0;
	for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
		ASSERT_EQ(rev[i], *it);
		++i;
	}
	(void)arr;
	(void)rev;
}

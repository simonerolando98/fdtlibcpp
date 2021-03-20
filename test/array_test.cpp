#include "gtest/gtest.h"
#include "fdt/rand_struct/array.h"
#include <numeric>

TEST(array, construct_default)
{
	fdt::array<int, 4> arr;
	(void)arr;
}

TEST(array, construct_copy)
{
	fdt::array<int, 2> arr;
	arr[0] = 1;
	arr[1] = 0;

	fdt::array<int, 2> copy(arr);
	ASSERT_EQ(arr[0], copy[0]);
	ASSERT_EQ(arr[1], copy[1]);

	(void)arr;
	(void)copy;
}

TEST(array, construct_init_list)
{
	fdt::array<int, 3> arr { 1, 2, 3 };
	ASSERT_EQ(1, arr[0]);
	ASSERT_EQ(2, arr[1]);
	ASSERT_EQ(3, arr[2]);
	(void)arr;
}

TEST(array, size)
{
	fdt::array<int, 3> arr;
	ASSERT_EQ(3, arr.size());
	(void)arr;
}

TEST(array, empty)
{
	fdt::array<int, 0> arr;
	ASSERT_TRUE(arr.empty());
	fdt::array<int, 5> e_arr;
	ASSERT_FALSE(e_arr.empty());
}

TEST(array, front_back)
{
	fdt::array<int, 2> arr;
	arr[0] = 1;
	arr[1] = 5;
	ASSERT_EQ(1, arr.front());
	ASSERT_EQ(5, arr.back());
	(void)arr;
}

TEST(array, data)
{
	fdt::array<int, 2> arr;
	ASSERT_TRUE(arr.data() != nullptr);
	(void)arr;
}

TEST(array, begin)
{
	fdt::array<int, 3> arr { 1, 2, 3 };
	auto begin = arr.begin();

	ASSERT_EQ(*begin, arr[0]);
	(void)arr;
}

TEST(array, end)
{
	fdt::array<int, 3> arr { 1, 2, 3 };
	auto end = arr.end();
	
	ASSERT_NE(arr.begin(), arr.end());
	(void)arr;
}

TEST(array, at)
{
	fdt::array<int, 3> arr { 1, 2, 3 };
	ASSERT_NO_THROW(arr.at(0));
	ASSERT_THROW(arr.at(3), fdt::array_out_of_range);
	ASSERT_EQ(2, arr.at(1));
	(void)arr;
}

TEST(array, iterator_test)
{
	fdt::array<int, 5> arr { 1, 6, 2, 9, 5 };
	auto sum = std::accumulate(std::begin(arr), std::end(arr), 0);
	ASSERT_EQ(23, sum);
	(void)arr;
}

#include <string>
#include "gtest/gtest.h"
#include "utility.h"

TEST(pair, make)
{
	auto p = fdt::make_pair<int, std::string>(1, "Hello");
	ASSERT_EQ(1, p.first);
	ASSERT_EQ("Hello", p.second);
}

TEST(pair, swap)
{
	auto p = fdt::make_pair<int, std::string>(1, "Hello");
	auto p1 = fdt::make_pair<int, std::string>(2, "World");

	ASSERT_EQ(1, p.first);
	ASSERT_EQ("Hello", p.second);
	ASSERT_EQ(2, p1.first);
	ASSERT_EQ("World", p1.second);
	fdt::swap(p, p1);
	ASSERT_EQ(1, p1.first);
	ASSERT_EQ("Hello", p1.second);
	ASSERT_EQ(2, p.first);
	ASSERT_EQ("World", p.second);
}

TEST(pair, get)
{
	const auto p = fdt::make_pair<int, std::string>(1, "Test");
	auto f = fdt::get<0>(p);
	auto s = fdt::get<1>(p);
	// auto fail = fdt::get<2>(p);
	ASSERT_EQ(f, p.first);
	ASSERT_EQ(s, p.second);
}

TEST(utility, is_null)
{
	int* ptr = reinterpret_cast<int*>(566432);
	int* null_ptr = nullptr;

	ASSERT_FALSE(fdt::is_null(ptr));
	ASSERT_TRUE(fdt::is_null(null_ptr));
	ASSERT_TRUE(fdt::is_null(nullptr));
}

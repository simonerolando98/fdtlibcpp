#include <gtest/gtest.h>
#include <ftl/string>

using namespace ftl;

TEST(string, default_construct)
{
	string str;
	(void)str;
}

TEST(string, charstar_construct)
{
	string str = "Hello";
	ASSERT_EQ(5, str.length());
	string long_str = "This is a long string used to test heap allocation";
	ASSERT_EQ(50, long_str.length());
	(void)long_str;
	(void)str;
}

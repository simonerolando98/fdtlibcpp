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

TEST(string, copyother)
{
	string str = "Hello";
	string newstr = str;
	ASSERT_EQ(str, newstr);
	(void)str;
	(void)newstr;
}

TEST(string, construct_from_temporary)
{
	string&& temp = string("Hello");
	string str(std::move(temp));
	ASSERT_EQ(temp, str);
	(void)str;
}

TEST(string, length_distance)
{
	string str = "Hello how are you Dennis? That";
	str.push_back('H');
	ASSERT_EQ(str.length(), ftl::distance(str.begin(), str.end()));
	(void)str;
}

TEST(string, insert_nchars)
{
	string str = "Hello, World";
	str.insert(6, 2, 'x');
	const string comp = "Hello,xx World";
	ASSERT_EQ(str, comp);
	(void)str;
}

TEST(string, insert_charptr)
{
	string str = "Hello, World";
	str.insert(6, "test");
	const string comp = "Hello,test World";
	ASSERT_EQ(str, comp);
	(void)str;
}

TEST(string, insert_basic_string)
{
	string str = "Hello, World";
	string ins = "test";
	str.insert(6, ins);
	const string comp = "Hello,test World";
	ASSERT_EQ(str, comp);
	(void)str;
	(void)ins;
}

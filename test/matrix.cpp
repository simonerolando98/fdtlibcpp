#include "gtest/gtest.h"
#include <ftl/random/matrix>

using namespace ftl;

TEST(matrix, construct_destruct_default)
{
    matrix<int, 3, 3> mat;
    (void)mat;
}

TEST(matrix, construct_initializer_list)
{
    matrix<int, 2, 2> mat {
        1, 0,
        0, 0
    };
    ASSERT_EQ(1, mat(0, 0));
    ASSERT_EQ(0, mat(0, 1));
    ASSERT_EQ(0, mat(1, 0));
    ASSERT_EQ(0, mat(1, 1));
    (void)mat;
}

TEST(matrix, fill)
{
    matrix<int, 3, 3> mat;
    mat.fill(4);
    for (auto x : mat) { ASSERT_EQ(4, x); }
    (void)mat;
}

TEST(matrix, size)
{
    matrix<int, 3, 3> mat;
    const auto size = std::make_pair<size_t, size_t>(3, 3);
    ASSERT_EQ(size, mat.size());
    (void)mat;
}

TEST(matrix, rows_cols)
{
    matrix<int, 3, 3> mat;
    ASSERT_EQ(3, mat.rows());
    ASSERT_EQ(3, mat.cols());
    (void)mat;
}

TEST(matrix, empty)
{
    matrix<int, 1, 0> emat;
    matrix<int, 3, 2> mat;
    ASSERT_TRUE(emat.empty());
    ASSERT_FALSE(mat.empty());
    (void)emat;
    (void)mat;
}

TEST(matrix, operator_paren)
{
    matrix<int, 2, 2> mat;
    mat.fill(2);
    ASSERT_EQ(2, mat(1, 0));
    ASSERT_EQ(2, mat(1, 1));
    (void)mat;
}

TEST(matrix, at)
{
    matrix<int, 2, 2> mat;
    mat.fill(3);
    ASSERT_EQ(3, mat.at(0, 1));
    ASSERT_EQ(3, mat.at(1, 0));
    ASSERT_THROW(mat.at(2, 0), matrix_out_of_range);
    ASSERT_NO_THROW(mat.at(0, 1));
    (void)mat;
}

TEST(matrix, determinant)
{
    matrix<int, 3, 3> mat;
    mat.fill(4);
    ASSERT_EQ(0.0, mat.determinant());
    (void)mat;
}

TEST(matrix, transpose)
{
    matrix<int, 2, 3> mat {
        1, -2, 2,
        0,  5, 4
    };
    ASSERT_EQ(mat(0, 0), mat.transpose()(0, 0));
    ASSERT_EQ(mat(0, 1), mat.transpose()(1, 0));
    ASSERT_EQ(mat(0, 2), mat.transpose()(2, 0));
    ASSERT_EQ(mat(1, 0), mat.transpose()(0, 1));
    ASSERT_EQ(mat(1, 1), mat.transpose()(1, 1));
    ASSERT_EQ(mat(1, 2), mat.transpose()(2, 1));
}

TEST(matrix, operator_plus)
{
    matrix<int, 2, 2> mat {
        1, 1,
        1, 1
    };
    auto sum = mat + matrix<int, 2, 2>{
        1, 1,
        1, 1
    };

    ASSERT_EQ(2, sum(0, 0));
    ASSERT_EQ(2, sum(0, 1));
    ASSERT_EQ(2, sum(1, 0));
    ASSERT_EQ(2, sum(1, 1));
    (void)mat;
    (void)sum;
}

TEST(matrix, operator_minus)
{
    matrix<int, 2, 2> mat {
        3, 3,
        3, 3
    };
    auto diff = mat - matrix<int, 2, 2> {
        1, 1,
        1, 1
    };
    ASSERT_EQ(2, diff(0, 0));
    ASSERT_EQ(2, diff(0, 1));
    ASSERT_EQ(2, diff(1, 0));
    ASSERT_EQ(2, diff(1, 0));
    (void)mat;
    (void)diff;
}

TEST(matrix, operator_inplace_plus)
{
    matrix<int, 2, 2> mat;
    mat.fill(2);
    mat += matrix<int, 2, 2> {
        1, 1,
        1, 1
    };

    ASSERT_EQ(3, mat(0, 0));
    ASSERT_EQ(3, mat(0, 1));
    ASSERT_EQ(3, mat(1, 0));
    ASSERT_EQ(3, mat(1, 1));
    (void)mat;
}

TEST(matrix, operator_inplace_minus)
{
    matrix<int, 2, 2> mat;
    mat.fill(3);
    mat -= matrix<int, 2, 2> {
        1, 1,
        1, 1
    };

    ASSERT_EQ(2, mat(0, 0));
    ASSERT_EQ(2, mat(0, 1));
    ASSERT_EQ(2, mat(1, 0));
    ASSERT_EQ(2, mat(1, 1));
    (void)mat;
}

TEST(matrix, operator_equality)
{
    matrix<int, 3, 3> mat {
        1, 1, 1,
        2, 1, 2,
        1, 5, 6
    };
    matrix<int, 3, 3> mat2 {
        1, 1, 1,
        2, 1, 2,
        1, 5, 6
    };
    ASSERT_TRUE(mat == mat2);
    (void)mat;
    (void)mat2;
}

TEST(matrix, operator_nequality)
{
    matrix<int, 3, 3> mat {
        1, 2, 4,
        5, 2, 0,
        6, 6, 8
    };
    matrix<int, 3, 3> mat2 {
        1, 2, 4,
        5, 2, 0,
        7, 6, 8
    };

    ASSERT_TRUE(mat != mat2);
}

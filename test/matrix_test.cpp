#include "gtest/gtest.h"
#include "fdt/matrix/matrix.h"

TEST(matrix, construct_destruct_default)
{
    fdt::matrix<int, 3, 3> mat;
    (void)mat;
}

TEST(matrix, construct_initializer_list)
{
    fdt::matrix<int, 2, 2> mat {
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
    fdt::matrix<int, 3, 3> mat;
    mat.fill(4);
    for (auto x : mat) { ASSERT_EQ(4, x); }
    (void)mat;
}

TEST(matrix, size)
{
    fdt::matrix<int, 3, 3> mat;
    const auto size = std::make_pair<size_t, size_t>(3, 3);
    ASSERT_EQ(size, mat.size());
    (void)mat;
}

TEST(matrix, rows_cols)
{
    fdt::matrix<int, 3, 3> mat;
    ASSERT_EQ(3, mat.rows());
    ASSERT_EQ(3, mat.cols());
    (void)mat;
}

TEST(matrix, empty)
{
    fdt::matrix<int, 1, 0> emat;
    fdt::matrix<int, 3, 2> mat;
    ASSERT_TRUE(emat.empty());
    ASSERT_FALSE(mat.empty());
    (void)emat;
    (void)mat;
}

TEST(matrix, operator_paren)
{
    fdt::matrix<int, 2, 2> mat;
    mat.fill(2);
    ASSERT_EQ(2, mat(1, 0));
    ASSERT_EQ(2, mat(1, 1));
    (void)mat;
}

TEST(matrix, at)
{
    fdt::matrix<int, 2, 2> mat;
    mat.fill(3);
    ASSERT_EQ(3, mat.at(0, 1));
    ASSERT_EQ(3, mat.at(1, 0));
    ASSERT_THROW(mat.at(2, 0), fdt::matrix_out_of_range);
    ASSERT_NO_THROW(mat.at(0, 1));
    (void)mat;
}

TEST(matrix, determinant)
{
    fdt::matrix<int, 3, 3> mat;
    mat.fill(4);
    ASSERT_EQ(0.0, mat.determinant());
    (void)mat;
}

TEST(matrix, transpose)
{
    fdt::matrix<int, 2, 3> mat {
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
    fdt::matrix<int, 2, 2> mat {
        1, 1,
        1, 1
    };
    auto sum = mat + fdt::matrix<int, 2, 2>{
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
    fdt::matrix<int, 2, 2> mat {
        3, 3,
        3, 3
    };
    auto diff = mat - fdt::matrix<int, 2, 2> {
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
    fdt::matrix<int, 2, 2> mat;
    mat.fill(2);
    mat += fdt::matrix<int, 2, 2> {
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
    fdt::matrix<int, 2, 2> mat;
    mat.fill(3);
    mat -= fdt::matrix<int, 2, 2> {
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
    fdt::matrix<int, 3, 3> mat {
        1, 1, 1,
        2, 1, 2,
        1, 5, 6
    };
    fdt::matrix<int, 3, 3> mat2 {
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
    fdt::matrix<int, 3, 3> mat {
        1, 2, 4,
        5, 2, 0,
        6, 6, 8
    };
    fdt::matrix<int, 3, 3> mat2 {
        1, 2, 4,
        5, 2, 0,
        7, 6, 8
    };

    ASSERT_TRUE(mat != mat2);
}

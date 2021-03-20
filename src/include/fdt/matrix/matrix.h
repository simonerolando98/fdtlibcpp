#ifndef FDT_MATRIX_STATIC_MATRIX_H
#define FDT_MATRIX_STATIC_MATRIX_H

#include <cmath>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <algorithm>
#include <functional>
#include "fdt/exception.h"
#include "fdt/iterator.h"

namespace fdt {
    template <typename Ty,
            std::size_t Rows, std::size_t Cols,
            class Allocator = std::allocator<Ty>>
    class matrix {
    public:
        using value_type = Ty;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = Ty&;
        using const_reference = const Ty&;
        using pointer = Ty*;
        using const_pointer = const Ty*;
        using iterator = fdt::rand_iterator<Ty>;
        using const_iterator = const fdt::rand_iterator<Ty>;

        /**
         * Default constructor. Constructs an empty matrix object.
         */
        constexpr matrix() { _data = _alloc.allocate(Rows * Cols); }

        /**
         * Initializing constructor. Constructs a new matrix object
         * using the initializer list to initialize its values.
         * @param init std::initializer_list<Ty> containing matrix
         * values.
         */
        constexpr matrix(const std::initializer_list<Ty> init)
        {
            _data = _alloc.allocate(Rows * Cols);
            if (init.size() == Rows * Cols) {
                size_t i = 0;
                for (auto& x : init) {
                    _data[i] = x;
                    ++i;
                }
            }
            else throw matrix_out_of_range();
        }

        /**
         * Copy constructor. Copies another matrix object of the same
         * type into the current instance, preserving the content.
         * @param other matrix object with same type and same
         * size.
         */
        constexpr matrix(const matrix& other)
        {
            _data = _alloc.allocate(Rows * Cols);
            std::copy(other._data, other._data + (Rows * Cols - 1), _data);
        }

        /**
         * Move constructor. Moves data from another matrix object,
         * provided that references to the other object are expired.
         * @param other matrix object with same type and same
         * size.
         */
        constexpr matrix(matrix&& other) noexcept
            : _data(std::move(other._data)) { other._data = nullptr; }

        ~matrix() { _alloc.deallocate(_data, Rows * Cols); }

        /**
         * Fills the matrix with a given value.
         * @param val a value of type matrix::value_type.
         */
        constexpr void fill(const Ty& val)
        {
            std::fill_n(_data, Rows * Cols, val);
        }

        /**
         * Returns the size of the matrix.
         * @return pair containing the size of the matrix.
         */
        constexpr auto size() const
        {
            return std::make_pair<size_t, size_t>(Rows, Cols);
        }

        /**
         * Returns the number of rows.
         * @return size_t containing the number of rows.
         */
        constexpr auto rows() const { return Rows; }

        /**
         * Returns the number of columns.
         * @return size_t containing the number of columns.
         */
        constexpr auto cols() const { return Cols; }

        /**
         * Returns a boolean indicating the current state of the matrix.
         * @return true if the size of the matrix computes to 0, false
         * otherwise.
         */
        [[nodiscard]]
        constexpr bool empty() const { return (Rows * Cols) == 0; }

        /**
         * Returns an iterator to the beginning of the matrix.
         * @return fdt::rand_iterator to the beginning of the matrix.
         */
        [[nodiscard]]
        constexpr iterator begin() { return rand_iterator(_data); }
        [[nodiscard]]
        constexpr const_iterator begin() const { return rand_iterator(_data); }

        /**
         * Returns an iterator to the end of the matrix.
         * @return fdt::rand_iterator to the end of the matrix.
         */
        [[nodiscard]]
        constexpr iterator end() { return rand_iterator(_data + Rows * Cols); }
        [[nodiscard]]
        constexpr const_iterator end() const { return rand_iterator(_data + Rows * Cols); }

        /**
         * Returns the underlying data structure containing matrix
         * data.
         * @return pointer to the underlying data structure. Data is
         * linearized for easier memory access, which needs notational
         * conversion of indices if access through the underlying data
         * structure is needed.
         */
        [[nodiscard]]
        constexpr auto data() { return _data; }
        [[nodiscard]]
        constexpr auto data() const { return _data; }

        /**
         * Returns a reference to the element of the matrix indexed
         * by row and column.
         * @param row current row.
         * @param col current column.
         * @return value_type reference to the indexed object.
         */
        constexpr reference
        operator()(size_t row, size_t col) noexcept
        {
            return _data[Cols * row + col];
        }

        constexpr const_reference
        operator()(size_t row, size_t col) const noexcept
        {
            return _data[Cols * row + col];
        }

        /**
         * Returns a reference to the element of the matrix indexed
         * by row and col. Every access is bounds-checked and may throw
         * matrix_out_of_range if any of the immediate values pertaining
         * to row or col is out of bounds.
         * @param row current row.
         * @param col current column.
         * @return value_type reference to the indexed element.
         */
        constexpr reference at(size_t row, size_t col)
        {
            if (row >= Rows || col >= Cols)
                throw matrix_out_of_range("matrix indices out of range");
            return _data[Cols * row + col];
        }
        constexpr const_reference at(size_t row, size_t col) const
        {
            if (row >= Rows || col >= Cols)
                throw matrix_out_of_range("matrix indices out of range");
            return _data[Cols * row + col];
        }

        /**
         * Calculates the determinant of an arithmetic compliant matrix
         * by using the iterative method.
         * @return double determinant value.
         */
        [[nodiscard]] double determinant() const noexcept
        {
            if (Rows != Cols)
                throw matrix_non_square("determinant is not defined"
                                        "for non square matrices.");

            // new allocator
            std::allocator<double> local_allocator;
            const size_t N = Rows;

            const double SMALL = 1.0E-30;
            double* mat = local_allocator.allocate(N * N);

            // copying matrix with cast
            std::transform(_data, _data + Rows * Cols, mat,
                           [](Ty x) { return static_cast<double>(x); });
            auto det = 1.0;

            // Row operations for i = 0, ..., n - 2
            for (size_t i = 0; i < N - 1; ++i) {
                // Partial pivot: find row r below with largest element in column i
                size_t r = i;
                double max = std::abs(mat[N * i + i]);
                for (size_t k = i + 1; k < N; ++k) {
                    double val = std::abs(mat[N * k + i]);
                    if (val > max) {
                        max = val;
                        r = k;
                    }
                }
                if (r != i) {
                    for (size_t j = i; j < N; ++j)
                        std::swap(mat[N * i + j], mat[N * r + j]);
                    det = -det;
                }

                // Row operations to calculate upper-triangular
                const double pivot = mat[N * i + i];
                // Singular matrix
                if (std::abs(pivot) < SMALL) return 0.0;

                // On lower rows
                for (size_t s = i + 1; s < N; ++s) {
                    // Multiple of row i to clear element in i-th column
                    const double multiple = mat[N * s + i] / pivot;
                    for (size_t j = i; j < N; ++j)
                        mat[N * s + j] -= multiple * mat[N * i + j];
                }
                det *= pivot;
            }
            det *= mat[N * (N - 1) + (N - 1)];

            local_allocator.deallocate(mat, N * N);
            return det;
        }

        /**
         * Generates the transpose of the current matrix object.
         * @return new matrix object containing the transpose of the
         * original matrix.
         */
        [[nodiscard]]
        constexpr auto transpose() const
        {
            matrix<Ty, Cols, Rows> mat;
            for (size_t i = 0; i < Rows; ++i)
                for (size_t j = 0; j < Cols; ++j)
                    mat(j, i) = this->operator()(i, j);
            return mat;
        }

        [[nodiscard]]
        constexpr auto operator+(const matrix& other) const
        {
            matrix<Ty, Rows, Cols> sum;
            for (size_t i = 0; i < Rows * Cols; ++i)
                *(sum.data() + i) = *(_data + i) + *(other.data() + i);
            return sum;
        }

        [[nodiscard]]
        constexpr auto operator-(const matrix& other) const
        {
            matrix<Ty, Rows, Cols> diff;
            for (size_t i = 0; i < Rows * Cols; ++i)
                *(diff.data() + i) = *(_data + i) - *(other.data() + i);
            return diff;
        }

        constexpr auto operator+=(const matrix& other)
        {
            for (size_t i = 0; i < Rows * Cols; ++i)
                *(_data + i) += *(other.data() + i);
            return *this;
        }

        constexpr auto operator-=(const matrix& other)
        {
            for (size_t i = 0; i < Rows * Cols; ++i)
                *(_data + i) -= *(other.data() + i);
            return *this;
        }

        constexpr bool operator==(const matrix& other) const
        {
            for (size_t i = 0; i < Rows * Cols; ++i)
                if (_data[i] != other.data()[i]) return false;
            return true;
        }

        constexpr bool operator!=(const matrix& other) const
        {
            return !(this->operator==(other));
        }
    private:
        Ty* _data;
        Allocator _alloc;
    };
}

#endif

#include "fdt/exception.h"

namespace fdt {
    matrix_out_of_range::matrix_out_of_range()
                : std::out_of_range("matrix indices out of range") {}

    matrix_out_of_range::matrix_out_of_range(const std::string& message)
                : out_of_range(message) {}

    matrix_out_of_range::matrix_out_of_range(const char* message)
                : std::out_of_range(message) {}

    matrix_non_square::matrix_non_square()
                : std::length_error("matrix is non-square") {}

    matrix_non_square::matrix_non_square(const std::string& message)
                : std::length_error(message) {}

    matrix_non_square::matrix_non_square(const char* message)
                : std::length_error(message) {}
}
//
// Created by Simone Rolando on 19/03/21.
//

#ifndef FDTLIBCPP_EXCEPTION_H
#define FDTLIBCPP_EXCEPTION_H

#include <stdexcept>

namespace fdt {
    /**
     * @brief Matrix out of range index exception.
    */
    class matrix_out_of_range : public std::out_of_range {
    public:
        matrix_out_of_range();

        explicit matrix_out_of_range(const std::string& message);

        explicit matrix_out_of_range(const char* message);
    };

    /**
     * @brief Matrix non square check exception.
    */
    class matrix_non_square : public std::length_error {
    public:
        matrix_non_square();

        explicit matrix_non_square(const std::string& message);

        explicit matrix_non_square(const char* message);
    };
}

#endif //FDTLIBCPP_EXCEPTION_H

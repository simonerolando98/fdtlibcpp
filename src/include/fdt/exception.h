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
	
	/**
	 * @brief Matrix size mismatch exception.
	*/
    class matrix_size_mismatch : public std::length_error {
    public:
        matrix_size_mismatch();

        explicit matrix_size_mismatch(const std::string& message);

        explicit matrix_size_mismatch(const char* message);
    };

	/**
	 * @brief Array out of range exception.
	*/
	class array_out_of_range : public std::out_of_range {
	public:
		array_out_of_range();

		explicit array_out_of_range(const std::string& message);

		explicit array_out_of_range(const char* message);
	};
}

#endif //FDTLIBCPP_EXCEPTION_H

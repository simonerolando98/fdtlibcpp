#ifndef FDTLIBCPP_EXCEPTION_H
#define FDTLIBCPP_EXCEPTION_H

#include <stdexcept>

namespace fdt {
    /**
     * @brief Matrix out of range index exception.
    */
    class matrix_out_of_range : public std::out_of_range {
    public:
        matrix_out_of_range()
			: std::out_of_range("matrix index out of range") {}

        explicit matrix_out_of_range(const std::string& message)
			: std::out_of_range(message) {}

        explicit matrix_out_of_range(const char* message)
			: std::out_of_range(message) {}
    };

    /**
     * @brief Matrix non square check exception.
    */
    class matrix_non_square : public std::length_error {
    public:
        matrix_non_square()
			: std::length_error("matrix non square") {}

        explicit matrix_non_square(const std::string& message)
			: std::length_error(message) {}

        explicit matrix_non_square(const char* message)
			: std::length_error(message) {}
    };
	
	/**
	 * @brief Matrix size mismatch exception.
	*/
    class matrix_size_mismatch : public std::length_error {
    public:
        matrix_size_mismatch()
			: std::length_error("matrix size mismatch") {}

        explicit matrix_size_mismatch(const std::string& message)
			: std::length_error(message) {}

        explicit matrix_size_mismatch(const char* message)
			: std::length_error(message) {}
    };

	/**
	 * @brief Array out of range exception.
	*/
	class array_out_of_range : public std::out_of_range {
	public:
		array_out_of_range()
			: std::out_of_range("array index out of range") {}

		explicit array_out_of_range(const std::string& message)
			: std::out_of_range(message) {}

		explicit array_out_of_range(const char* message)
			: std::out_of_range(message) {}
	};

    /**
     * @brief Vector size mismatch exception
    */
    class vector_size_mismatch : public std::length_error {
    public:
        vector_size_mismatch()
			: std::length_error("vector size mismatch") {}

        explicit vector_size_mismatch(const std::string& message)
			: std::length_error(message) {}

        explicit vector_size_mismatch(const char* message)
			: std::length_error(message) {}
    };
}

#endif //FDTLIBCPP_EXCEPTION_H

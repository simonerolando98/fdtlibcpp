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

    matrix_size_mismatch::matrix_size_mismatch()
        	: std::length_error("matrix size mismatch") {}

    matrix_size_mismatch::matrix_size_mismatch(const std::string& message)
        	: std::length_error(message) {}

    matrix_size_mismatch::matrix_size_mismatch(const char* message)
    		: std::length_error(message) {}

    array_out_of_range::array_out_of_range()
		: std::out_of_range("array index out of range") {}

    array_out_of_range::array_out_of_range(const std::string& message)
	    	: std::out_of_range(message) {}

    array_out_of_range::array_out_of_range(const char* message)
	    	: std::out_of_range(message) {}
    
    vector_size_mismatch::vector_size_mismatch()
        : std::length_error("vector size mismatch") {}

    vector_size_mismatch::vector_size_mismatch(const std::string& message)
        : std::length_error(message) {}

    vector_size_mismatch::vector_size_mismatch(const char* message)
        : std::length_error(message) {}
}

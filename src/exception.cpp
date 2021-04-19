#include <ftl/exception>

namespace ftl {

	matrix_out_of_range::matrix_out_of_range()
	: std::out_of_range("matrix index out of range")
	{}

	matrix_out_of_range::matrix_out_of_range(const std::string& message)
	: std::out_of_range(message)
	{}

	matrix_out_of_range::matrix_out_of_range(const char* message)
	: std::out_of_range(message)
	{}
	
	// Square matrix check
	matrix_non_square::matrix_non_square()
	: std::length_error("matrix non square")
	{}

	matrix_non_square::matrix_non_square(const std::string& message)
	: std::length_error(message)
	{}

	matrix_non_square::matrix_non_square(const char* message)
	: std::length_error(message)
	{}

	// Array out of range
	array_out_of_range::array_out_of_range()
	: std::out_of_range("array index out of range")
	{}

	array_out_of_range::array_out_of_range(const std::string& message)
	: std::out_of_range(message)
	{}

	array_out_of_range::array_out_of_range(const char* message)
	: std::out_of_range(message)
	{}

}

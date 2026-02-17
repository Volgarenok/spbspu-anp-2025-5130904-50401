#include <iostream>
#include <fstream>
#include <memory>
#include "array_functions.hpp"
#include "variants.hpp"



int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  if (!std::isdigit(argv[1][0])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t rows = 0, cols = 0;
  std::ifstream input(argv[2]);
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Bad read (rows and cols)\n";
    return 2;
  }
  constexpr size_t MAX_MATRIX_SIZE = 10000;
  int matrix_static[MAX_MATRIX_SIZE] = {};
  int * matrix = nullptr;
  int * matrix_dynamic = nullptr;
  if (argv[1][0] == '1') {
    matrix = matrix_static;
  } else {
    matrix_dynamic = reinterpret_cast< int * >(malloc(sizeof(int) * rows * cols));
    if (matrix_dynamic == nullptr) {
      std::cerr << "Bad alloc\n";
      return 2;
    }
    matrix = matrix_dynamic;
  }
  zharov::processMatrix(input, matrix, rows, cols, argv[3]);

  free(matrix_dynamic);

  if (input.eof()) {
    std::cerr << "Not enough numbers\n";
    return 2;
  } else if (input.bad()) {
    std::cerr << "Bad read (wrong value)\n";
    return 2;
  }

}

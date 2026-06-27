#include <fstream>
#include <iostream>
#include "array_funcs.hpp"
#include "variants.hpp"

int main(int argc, char ** argv)
{
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (!std::isdigit(argv[1][0])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0')) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Incorrect input\n";
    return 2;
  }

  if (argv[1][0] == '1') {
    constexpr size_t MAX_STATIC_MATRIX_SIZE = 10000;
    int matrix[MAX_STATIC_MATRIX_SIZE] = {};
    return chernov::processMatrix(input, output, matrix, rows, cols);
  }

  int * matrix = new int[rows * cols];
  int result = chernov::processMatrix(input, output, matrix, rows, cols);
  delete [] matrix;
  return result;
}

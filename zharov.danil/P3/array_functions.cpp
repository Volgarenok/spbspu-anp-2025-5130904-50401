#include "array_functions.hpp"
#include <fstream>
#include "variants.hpp"

std::istream & zharov::inputMatrix(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; input && i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}

void zharov::processMatrix(std::ifstream & input, int * matrix, size_t rows, size_t cols, const char * output_file)
{
  zharov::inputMatrix(input, matrix, rows, cols);
  if (input.fail()) {
    return;
  }
  std::ofstream output(output_file);
  output << zharov::isUppTriMtx(matrix, rows, cols) << "\n";
  output << zharov::getCntColNsm(matrix, rows, cols) << "\n";
}

#include "array_funcs.hpp"
#include <iostream>
#include "variants.hpp"

std::istream & chernov::matrixInput(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}

int chernov::getSumAntiDiagonal(const int * mtx, size_t x, size_t y, size_t rows, size_t cols)
{
  int sum = 0;
  do {
    sum += mtx[y * cols + x];
  } while (x-- > 0 && ++y < rows);
  return sum;
}

int chernov::processMatrix(std::istream & input, std::ostream & output, int * matrix, size_t rows, size_t cols)
{
  if (!chernov::matrixInput(input, matrix, rows, cols)) {
    std::cerr << "Incorrect input\n";
    return 2;
  }

  output << chernov::minSumMdg(matrix, rows, cols) << "\n";

  chernov::fllIncWav(matrix, rows, cols);
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i) {
    output << " " << matrix[i];
  }
  output << "\n";

  return 0;
}

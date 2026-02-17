#include "arr_func.hpp"
#include <limits>
int zubarev::getMaxInt()
{
  using namespace std;
  using int_limit = numeric_limits< int >;
  return int_limit::max();
}

int zubarev::getMinInt()
{
  using namespace std;
  using int_limit = numeric_limits< int >;
  return int_limit::min();
}

std::ostream&zubarev::outputMatrix(std::ostream& out, const int* const matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (j != 0) {
        out << ' ';
      }
      out << matrix[i * cols + j];
    }
    out << '\n';
  }
  return out;
}

int* zubarev::convertToSquare(int* matrix, size_t& rows, size_t& cols)
{
  size_t sizeOfMatrix = std::min(rows, cols);
  int* square = reinterpret_cast< int* >(malloc(sizeOfMatrix * sizeOfMatrix * sizeof(int)));
  if (!square) {
    return nullptr;
  }
  if (rows == cols) {
    for (size_t i = 0; i < rows * cols; ++i) {
      square[i] = matrix[i];
    }
  } else {
    for (size_t i = 0; i < sizeOfMatrix; ++i) {
      for (size_t j = 0; j < sizeOfMatrix; ++j) {
        square[i * sizeOfMatrix + j] = matrix[i * cols + j];
      }
    }
    rows = cols = sizeOfMatrix;
  }

  return square;
}

int* zubarev::readMatrix(std::istream& in, size_t& rows, size_t& cols, int* matrix)
{
  for (size_t i = 0; i < rows * cols; ++i) {
    if (!(in >> matrix[i])) {
      break;
    }
  }
  return matrix;
}

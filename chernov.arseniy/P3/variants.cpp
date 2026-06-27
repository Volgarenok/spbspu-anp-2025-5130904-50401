#include "variants.hpp"
#include <limits>
#include "array_funcs.hpp"

void chernov::fllIncWav(int * mtx, size_t rows, size_t cols)
{
  int add = 1;
  size_t x = 0, y = 0, count = 0, border = 0;
  while (count++ < rows * cols) {
    mtx[cols * y + x] += add;
    if (y == border && x != cols - border - 1) {
      ++x;
    } else if (x == cols - border - 1 && y != rows - border - 1) {
      ++y;
    } else if (y == rows - border - 1 && x != border) {
      --x;
    } else if (x == border) {
      if (y == border - 1) {
        ++add;
        ++border;
        ++x;
      } else {
        --y;
      }
    }
  }
}

int chernov::minSumMdg(const int * mtx, size_t rows, size_t cols)
{
  if (rows * cols == 0) {
    return 0;
  }
  int min_sum = std::numeric_limits< int >::max(), sum = 0;

  for (size_t x = 0; x < cols; ++x) {
    sum = getSumAntiDiagonal(mtx, x, 0, rows, cols);
    if (sum < min_sum) {
      min_sum = sum;
    }
  }
  for (size_t y = 1; y < rows; ++y) {
    sum = getSumAntiDiagonal(mtx, cols - 1, y, rows, cols);
    if (sum < min_sum) {
      min_sum = sum;
    }
  }
  return min_sum;
}


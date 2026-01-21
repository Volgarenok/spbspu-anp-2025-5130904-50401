#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>

namespace chernov {
  std::istream & matrixInput(std::istream & input, int * mtx, size_t rows, size_t cols);
  void fllIncWav(int * mtx, size_t rows, size_t cols);
  int minSumMdg(const int * mtx, size_t rows, size_t cols);
  int getSumAntiDiagonal(const int * mtx, size_t x, size_t y, size_t rows, size_t cols);
  int processMatrix(std::istream & input, std::ostream & output, int * matrix, size_t rows, size_t cols);
}

std::istream & chernov::matrixInput(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}

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

int chernov::getSumAntiDiagonal(const int * mtx, size_t x, size_t y, size_t rows, size_t cols)
{
  int sum = 0;
  do {
    sum += mtx[y * cols + x];
  } while (x-- > 0 && ++y < rows);
  return sum;
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

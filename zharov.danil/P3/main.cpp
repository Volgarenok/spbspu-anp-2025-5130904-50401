#include <iostream>
#include <fstream>
#include <memory>
#include <cctype>

namespace zharov
{
  std::istream & inputMatrix(std::istream & input, int * mtx, size_t rows, size_t cols);
  bool isUppTriMtx(const int * mtx, size_t rows, size_t cols);
  size_t getCntColNsm(const int * mtx, size_t rows, size_t cols);
  void processMatrix(std::ifstream & input, int * matrix, size_t rows, size_t cols, const char * output_file);
}

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

std::istream & zharov::inputMatrix(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; input && i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}

bool zharov::isUppTriMtx(const int * mtx, size_t rows, size_t cols)
{
  if (rows != cols) {
    rows = std::min(rows, cols);
    cols = rows;
  }

  if (rows == 0) {
    return false;
  }

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (mtx[cols * i + j] != 0) {
        return false;
      }
    }
  }
  return true;
}

size_t zharov::getCntColNsm(const int * mtx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0) {
    return 0;
  }

  size_t res = cols;
  for (size_t i = 0; i < cols; ++i) {
    for (size_t j = 1; j < rows; ++j) {
      if (mtx[j * cols + i] == mtx[(j - 1) * cols + i]) {
        --res;
        break;
      }
    }
  }
  return res;
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

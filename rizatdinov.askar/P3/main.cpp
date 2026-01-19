#include <iostream>
#include <fstream>
#include <memory>

namespace rizatdinov
{
  bool initial(int * array, size_t len, std::ifstream & file);
  bool isLocalMax(const int * array, size_t cols, size_t position);
  unsigned long countLocalMax(const int * array, size_t rows, size_t cols);
  bool isLowerTriangular(const int * array, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc < 4 || argc > 4) {
    std::cerr << "fatal: invalid parameters\n";
    return 1;
  }

  char number = argv[1][0];
  if (number < '1' || number > '2' || argv[1][1] != '\0') {
    std::cerr << "fatal: invalid parameters\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "fatal: file not found\n";
    return 2;
  }

  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "fatal: could not read file\n";
    return 2;
  }

  int * array = nullptr;
  int fixlen_array[10000] = {};
  if (number == '1') {
    array = fixlen_array;
  } else {
    array = reinterpret_cast< int * >(malloc(sizeof(int) * rows * cols));
  }

  if (array == nullptr) {
    std::cerr << "fatal: memory allocation failed\n";
    return 3;
  }

  if (rizatdinov::initial(array, rows * cols, input)) {
    if (number == '2') {
      free(array);
    }
    std::cerr << "fatal: could not read file\n";
    return 2;
  }

  input.close();

  std::ofstream output(argv[3]);

  size_t count_local_max = rizatdinov::countLocalMax(array, rows, cols);
  bool is_lower_triangular = rizatdinov::isLowerTriangular(array, rows, cols);

  output << count_local_max << ' ' << is_lower_triangular << '\n';

  if (number == '2') {
    free(array);
  }

  return 0;
}

bool rizatdinov::initial(int * array, size_t len, std::ifstream & file)
{
  for (size_t i = 0; i < len; ++i) {
    file >> array[i];
    if (!file) {
      return 1;
    }
  }
  return 0;
}

bool rizatdinov::isLocalMax(const int * array, size_t cols, size_t position)
{
  bool result = array[position] > array[position + 1];
  result = result && array[position] > array[position - 1];
  result = result && array[position] > array[position + cols];
  result = result && array[position] > array[position - cols];

  return result;
}

unsigned long rizatdinov::countLocalMax(const int * array, size_t rows, size_t cols)
{
  size_t count = 0;
  for (size_t i = 1; i + 1 < rows; ++i) {
    for (size_t j = 1; j + 1 < cols; ++j) {
      size_t position = i * cols + j;
      count += rizatdinov::isLocalMax(array, cols, position);
    }
  }
  return count;
}

bool rizatdinov::isLowerTriangular(const int * array, size_t rows, size_t cols)
{
  if (!(rows && cols)) {
    return false;
  }

  bool result = true;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = i + 1; j < cols; ++j) {
      if (array[i * cols + j] != 0) {
        return false;
      }
    }
  }
  return result;
}

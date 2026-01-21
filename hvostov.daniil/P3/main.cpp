#include <iostream>
#include <fstream>

namespace hvostov {
  std::ifstream & inputMatrix(std::ifstream & input, int * matrix, size_t rows, size_t cols);
  size_t countLocalMax(const int * matrix, size_t rows, size_t cols);
  void modifyMatrix(int * matrix, size_t rows, size_t cols);
  void outputMatrix(std::ofstream & output, const int * matrix, size_t rows, size_t cols);
  void taskExecution(std::ofstream & output, int * matrix, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc > 4) {
    std::cerr << "Too many arguments!\n";
    return 1;
  } else if (argc < 4) {
    std::cerr << "Not enough arguments!\n";
    return 1;
  } else if (!std::isdigit(argv[1][0]) || argv[1][1] != '\0') {
    std::cerr << "First parameter is not a number!\n";
    return 1;
  } else if (argv[1][0] < '1' || argv[1][0] > '2') {
    std::cerr << "First parameter is out of range!\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Problems with input_matrix!\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    output << 0 << "\n" << 0 << " " << 0 << "\n";
    return 0;
  }
  constexpr size_t MATRIX_SIZE = 10000;
  int * matrix = nullptr;
  int primary_matrix[MATRIX_SIZE] = {};
  int * dynamic_primary_matrix = nullptr;
  if (argv[1][0] == '1') {
    matrix = primary_matrix;
  } else {
    dynamic_primary_matrix = reinterpret_cast< int * >(malloc(sizeof(int) * rows * cols));
    if (dynamic_primary_matrix == nullptr) {
      std::cerr << "Bad alloc!\n";
      return 3;
    }
    matrix = dynamic_primary_matrix;
  }
  if (!hvostov::inputMatrix(input, matrix, rows, cols)) {
    std::cerr << "Bad input!\n";
    free(dynamic_primary_matrix);
    return 2;
  }
  hvostov::taskExecution(output, matrix, rows, cols);
  free(dynamic_primary_matrix);
  return 0;
}

void hvostov::taskExecution(std::ofstream & output, int * matrix, size_t rows, size_t cols)
{
  size_t counter = hvostov::countLocalMax(matrix, rows, cols);
  output << counter << "\n";
  hvostov::modifyMatrix(matrix, rows, cols);
  hvostov::outputMatrix(output, matrix, rows, cols);
}

std::ifstream & hvostov::inputMatrix(std::ifstream & input, int * matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; i++) {
    input >> matrix[i];
  }
  return input;
}

size_t hvostov::countLocalMax(const int * matrix, size_t rows, size_t cols)
{
  if (rows < 3 || cols < 3) {
    return 0;
  }
  size_t counter = 0;
  for (size_t i = 1; i < rows - 1; i++) {
    for (size_t j = 1; j < cols - 1; j++) {
      bool is_local_max = matrix[i * cols + j] > matrix[i * cols + j - 1];
      is_local_max = is_local_max && matrix[i * cols + j] > matrix[i * cols + j + 1];
      is_local_max = is_local_max && matrix[i * cols + j] > matrix[(i - 1) * cols + j];
      is_local_max = is_local_max && matrix[i * cols + j] > matrix[(i + 1) * cols + j];
      if (is_local_max) {
        counter++;
      }
    }
  }
  return counter;
}

void hvostov::outputMatrix(std::ofstream & output, const int * matrix, size_t rows, size_t cols)
{
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; i++) {
    output << " " << matrix[i];
  }
  output << "\n";
}

void hvostov::modifyMatrix(int * matrix, size_t rows, size_t cols)
{
  size_t top = 0, right = cols - 1, bot = rows - 1, left = 0, decrease_by = 1;
  while (top <= bot && left <= right) {
    for (size_t i = bot; i > top; i--) {
      matrix[i * cols + left] -= decrease_by;
      decrease_by++;
    }
    for (size_t j = left; j < right; j++) {
      matrix[j + top * cols] -= decrease_by;
      decrease_by++;
    }
    for (size_t i = top; i < bot; i++) {
      matrix[i * cols + right] -= decrease_by;
      decrease_by++;
    }
    for (size_t j = right; j > left; j--) {
      matrix[bot * cols + j] -= decrease_by;
      decrease_by++;
    }
    top++;
    right--;
    bot--;
    left++;
  }
}

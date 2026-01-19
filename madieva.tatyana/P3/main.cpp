#include <iostream>
#include <fstream>
#include <cctype>
namespace madieva
{
  int * createArray(char number, size_t rows, size_t cols) {
    if (number == '2') {
      return new int[rows * cols];
    }
    return nullptr;
  }
  std::ifstream & readMatrix(std::ifstream & input, size_t rows, size_t cols, int * array)
  {
    for (size_t i = 0; i < rows * cols; i++) {
      input >> array[i];
      if (!input) {
        return input;
      }
    }
    return input;
  }
  void changeInSpiral(int * matrix, size_t rows, size_t cols)
  {
    size_t top = 0;
    size_t left = 0;
    size_t bottom = rows - 1;
    size_t right = cols - 1;
    int subtraction = 1;
    matrix[bottom * cols + left] -= subtraction;
    while (left <= right && top <= bottom) {
      for (size_t i =  bottom; i > top; --i) {
        matrix[i * cols + left] -= subtraction;
        subtraction++;
      }
      if (left == right) {
        break;
      }
      for (size_t i =  left; i < right; ++i) {
        matrix[top * cols + i] -= subtraction;
        subtraction++;
      }
      if (bottom == top) {
        break;
      }
      for (size_t i =  top + 1; i <=  bottom; ++i) {
        matrix[i * cols + right] -= subtraction;
        subtraction++;
      }
      if (left + 1 == right) {
        break;
      }
      for (size_t i =  right; i > left; --i) {
        matrix[bottom * cols + i] -= subtraction;
        subtraction++;
      }
      right--;
      left++;
      top++;
      bottom--;
    }
  }
  void writeMatrix(std::ofstream & output, size_t rows, size_t cols, const int * array)
  {
    output << rows << " " << cols;
    for (size_t i = 0; i < rows * cols; ++i) {
      output << " " << array[i];
    }
    output << "\n";
  }
  int differentElementInCols(const int * array, size_t rows, size_t cols)
  {
    size_t counter = 0;
    size_t repeat = 0;
    for(size_t i = 0; i < cols; i++) {
      for (size_t j = 0; j < rows - 1; j++) {
        if (array[j * cols + i] == array[(j + 1) * cols + i]) {
          repeat++;
        }
      }
      if (repeat == 0) {
        counter++;
      }
      repeat = 0;
    }
    return counter;
  }
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
  if (!isdigit(argv[1][0])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2')) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  const char * arg = argv[1];
  const char * inputFile = argv[2];
  const char * outputFile = argv[3];
  std::ifstream input(inputFile);
  if (!input.is_open()) {
    std::cerr << "Error when opening input file\n";
    return 2;
  }
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input) {
    std::cerr << "Irregular matrix size\n";
    return 2;
  }
  if ((rows == 0 && cols != 0) || (rows != 0 && cols == 0)) {
    std::cerr << "Irregular matrix size\n";
    return 2;
  }
  if (rows == 0 && cols == 0) {
    std::ofstream output(outputFile);
    output << 0 << " " << 0 << "\n";
    return 0;
  }
  int * matrix = nullptr;
  const int max_size = 10000;
  int array[max_size] = {};
  try {
    if (arg[0] == '1' && rows * cols < max_size) {
      matrix = array;
    } else {
      matrix = madieva::createArray(arg[0], rows, cols);
    }
  } catch (const std::bad_alloc & e) {
    std::cerr << "Out of memory\n";
    return 2;
  }
  if (!madieva::readMatrix(input, rows, cols, matrix)) {
    std::cerr << "Error reading matrix\n";
    if (arg[0] == '2') {
      delete[] matrix;
    }
    return 2;
  }
  input.close();
  size_t quantity = madieva::differentElementInCols(matrix, rows, cols);
  madieva::changeInSpiral(matrix, rows, cols);
  std::ofstream output(outputFile);
  if (!output.is_open()) {
    std::cerr << "Error opening output file\n";
    if (arg[0] == '2') {
      delete[] matrix;
    }
    return 2;
  }
  madieva::writeMatrix(output, rows, cols, matrix);
  output << quantity << "\n";
  if (arg[0] == '2') {
    delete[] matrix;
  }
  return 0;
}

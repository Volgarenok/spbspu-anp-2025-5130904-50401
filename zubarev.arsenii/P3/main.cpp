
#include <fstream>
#include <memory>

#include "arr_func.hpp"
#include "variant_func.hpp"

int main(int argc, char const** argv)
{
  namespace zub = zubarev;
  size_t rows = 0, cols = 0;

  if (argc > 4) {
    std::cerr << "Too many arguments" << "\n";
    return 1;
  } else if (argc < 4) {
    std::cerr << "Not enough arguments" << "\n";
    return 1;
  } else if (std::stoi(argv[1]) > 2) {
    std::cerr << "First is out of range" << "\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input) {
    std::cerr << "Cannot open input file\n";
    return 1;
  }
  input >> rows >> cols;
  if (!(input)) {
    std::cerr << "Can't read the file\n";
    return 1;
  }
  int* mtx = nullptr;
  if (std::stoi(argv[1]) == 1) {
    int statMatrix[10000];
    if (rows * cols > 10000) {
      std::cerr << "Matrix too big for static allocation\n";
      return 1;
    }
    mtx = statMatrix;
    mtx = zub::readMatrix(input, rows, cols, mtx);
    if (input.fail()) {
      std::cerr << "Can't read the file\n";
      return 1;
    }

  } else if (std::stoi(argv[1]) == 2) {
    mtx = reinterpret_cast<int*>(std::malloc(rows * cols * sizeof(int)));
    if (!mtx) {
      std::cerr << "Memory allocation failed\n";
      return 1;
    }

    mtx = zub::readMatrix(input, rows, cols, mtx);
    if (input.fail()) {
      std::cerr << "Can't read the file\n";
      free(mtx);
      return 1;
    }
  }

  if (!mtx) {
    return 2;
  }
  int* square = zubarev::convertToSquare(mtx, rows, cols);

  std::ofstream output(argv[3]);
  output << zub::getCouOfColNoIden(square, rows, cols) << "\n";
  output << zub::getMaxSumInDia(square, rows, cols) << "\n";
  if (std::stoi(argv[1]) == 2) {
    free(mtx);
  }
  free(square);
}

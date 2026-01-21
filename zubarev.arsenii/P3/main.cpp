#include <iostream>
#include <fstream>
#include <memory>
#include <limits>

namespace zubarev
{
  int getMaxInt();
  int getMinInt();
  std::ostream& outputMatrix(std::ostream& out, const int* matrix, size_t rows, size_t cols);
  int* convertToSquare(int* matrix, size_t& rows, size_t& cols);
  int* readMatrix(std::istream& in, size_t& rows, size_t& cols, int* matrix);
  int getCouOfColNoIden(const int* matrix, size_t rows, size_t cols);
  int getMaxSumInDia(const int* matrix, size_t rows, size_t cols);
}

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
    for (size_t i = 0; i < rows*cols; ++i) {
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

int zubarev::getCouOfColNoIden(const int* matrix, size_t rows, size_t cols)
{
  size_t count = 0;
  bool equalFlag = false;

  for (size_t j = 0; j < cols; ++j) {
    for (size_t i = 0; i < rows - 1; ++i) {
      if (matrix[cols * i + j] == matrix[cols * (i + 1) + j]) {
        equalFlag = true;
        break;
      }
    }
    if (!equalFlag) {
      count++;
    } else {
      equalFlag = false;
    }
  }

  return count;
}

int zubarev::getMaxSumInDia(const int* matrix, size_t rows, size_t cols)
{
  int maxSum = getMinInt();
  int tempSum = 0;
  for (size_t s = 1; s <= (cols / 2); ++s) {
    for (size_t i = 0; i < rows - s; i++) {
      tempSum += matrix[i * cols + (i + s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }

  for (size_t s = 1; s <= (cols / 2); ++s) {
    for (size_t i = s; i < rows; i++) {
      tempSum += matrix[i * cols + (i - s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }

  return maxSum;
}


#include <iostream>
#include <fstream>
#include <memory>
#include <cctype>

namespace kuznetsov {
  const size_t MAX_SIZE = 10'000;

  int getCntColNsm(const int* mtx, size_t rows, size_t cols);
  int getCntLocMax(const int* mtx, size_t rows, size_t cols);

  std::istream& initMatr(std::istream& input, int* mtx, size_t rows, size_t cols);

  int processMatrix(std::istream& input, int* mtx, size_t rows, size_t cols, const char* out);
}

int main(int argc, char** argv)
{
  namespace kuz = kuznetsov;
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too many arguments\n";
    return 1;
  } else if (!std::isdigit(argv[1][0])) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0') {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t rows = 0, cols = 0;
  std::ifstream input(argv[2]);

  if (!input.is_open()) {
    std::cerr << "Can't open file\n";
    return 2;
  }

  input >> rows >> cols;
  if (!input) {
    std::cerr << "Bad reading size\n";
    return 2;
  }
  int mtx[kuz::MAX_SIZE] {};
  int* mtrx = nullptr;
  int* mt = nullptr;
  if (argv[1][0] == '1') {
    mtrx = mtx;
  } else {
    mt = reinterpret_cast< int* >(malloc(sizeof(int) * rows * cols));
    if (mt == nullptr) {
      std::cerr << "Bad alloc\n";
      return 3;
    }
    mtrx = mt;
  }
  int statusExit = kuz::processMatrix(input, mtrx, rows, cols, argv[3]);
  free(mt);
  return statusExit;
}

int kuznetsov::getCntColNsm(const int* mtx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0) {
    return 0;
  }
  int res = 0;
  for (size_t j = 0; j < cols; ++j) {
    bool repeats = false;
    for (size_t i = 0; i < rows - 1; ++i) {
      if (mtx[i * cols + j] == mtx[(i + 1) * cols + j]) {
        repeats = true;
        break;
      }
    }
    res += !repeats;
  }
  return res;
}

int kuznetsov::getCntLocMax(const int* mtx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0) {
    return 0;
  }
  int res = 0;
  for (size_t j = 1; j < cols - 1; ++j) {
    for (size_t i = 1; i < rows - 1; ++i) {
      int center = mtx[i * cols + j];
      bool isLocMax = true;
      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if (!(di == 0 && dj == 0)) {
            isLocMax = isLocMax && (center > mtx[(i + di) * cols + j + dj]);
          }
        }
      }
      res += isLocMax;
    }
  }
  return res;
}

std::istream& kuznetsov::initMatr(std::istream& input, int* mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; input && i < rows * cols; ++i) {
    input >> mtx[i];
  }
  return input;
}

int kuznetsov::processMatrix(std::istream& input, int* mtx, size_t rows, size_t cols, const char* out)
{
  initMatr(input, mtx, rows, cols);
  if (input.eof()) {
    std::cerr << "Not enough elements for matrix\n";
    return 1;
  } else if (input.fail()) {
    std::cerr << "Bad read\n";
    return 2;
  }

  int res1 = getCntColNsm(mtx, rows, cols);
  int res2 = getCntLocMax(mtx, rows, cols);

  std::ofstream output(out);
  output << res1 << '\n';
  output << res2 << '\n';

  return 0;
}

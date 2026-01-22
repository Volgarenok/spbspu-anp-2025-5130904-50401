#include "variants.hpp"

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

